#include "GameManager.h"
void GameManager::startGame()//setup variables needed before the game starts
{
	timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = sf::Time::Zero;
	timeSinceLastFixedUpdate = sf::Time::Zero;
	clock.restart();

	worldTiles.init();
	gameUI.init();
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		player[index].upgradeCustomUnit(gameUI.customSquadData,0);
		player[index].init(index, 0);
	}

	unitPlacementHighlight.setRadius(20);
	unitPlacementHighlight.setOutlineColor(sf::Color::Green);
	unitPlacementHighlight.setOutlineThickness(2);
	unitPlacementHighlight.setOrigin(unitPlacementHighlight.getRadius(), unitPlacementHighlight.getRadius());
	unitPlacementHighlight.setFillColor(sf::Color::Transparent);
	
	std::vector<int> unitTiles;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		std::vector<int> temp = player[i].returnAllSquadPositions();
		if (temp.empty() == false)
		{
			unitTiles.insert(unitTiles.end(), temp.begin(), temp.end());
		}
		worldTiles.getPlayerTakenTiles(unitTiles);
	}

	updateLoop();
}

void GameManager::updateLoop()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "War of Attrition");
	sf::View viewport(sf::FloatRect((SCREEN_WIDTH / 2) - VIEWPORT_WIDTH / 2, (SCREEN_HEIGHT / 2) - VIEWPORT_HEIGHT / 2, VIEWPORT_WIDTH, VIEWPORT_HEIGHT));//center the viewport on the map
	sf::View fixedWindow;
	fixedWindow = window.getView();

	int framerate = 0;
	int frameCount = 0;
	float elapsedTime = 0.0f;

	srand(time(0));

	while (window.isOpen()) 
	{
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		timeSinceLastFixedUpdate += deltaTime;

		//debugging - will end up as a setting later
		frameCount++;//count how many frames have passed since last second
		elapsedTime += deltaTime.asSeconds();
		if (elapsedTime >= 1.0f)//if 1 second has passed
		{
			gameUI.framerateText.setString(std::to_string(frameCount));
			frameCount = 0;//reset the frames passed
			elapsedTime = 0.0f;//reset time since last check
		}
		

		displayClean(window, viewport);

		userControls(viewport, deltaTime);

		if (menuOpen == false && worldEditingEnabled == false)
		{
			updatePlayers(deltaTime);

			worldTiles.update(deltaTime);
		}

		display(window);
		displayHUD(window, fixedWindow);

		while (timeSinceLastFixedUpdate >= timePerFrame)//60fps cap for timers and collisions
		{
			for (int index = 0; index < MAX_PLAYERS; index++)
			{
				if (worldTilesModified == true)
				{
					worldTilesDataUpdated = true;

					std::vector<int> unitTiles;

					for (int i = 0; i < MAX_PLAYERS; i++)
					{
						if (i != whosTurn - 1)
						{
							std::vector<int> temp = player[i].returnAllSquadPositions();
							if (temp.empty() == false)
							{
								unitTiles.insert(unitTiles.end(), temp.begin(), temp.end());
							}
						}
					}

					if (unitTiles.empty() == true)
					{
						std::cout << "unitTiles was empty\n";
						player[index].passInvalidTiles(worldTiles.getInvalidTiles());
					}
					else {
						std::vector<int> temp = worldTiles.getInvalidTiles();

						unitTiles.insert(unitTiles.end(), temp.begin(), temp.end());
						player[index].passInvalidTiles(unitTiles);
					}
				}
				if (player[whosTurn - 1].playerEliminated == false)
				{
					player[index].fixedUpdate();
				}				
			}
			if (worldTilesDataUpdated == true)
			{
				worldTilesModified = false;
				worldTilesDataUpdated = false;
			}
			if (clickTimer > 0)
			{
				clickTimer--;
			}

			handleCollisions();
			menuInteractions();
			gameUI.fixedUpdate();
			timeSinceLastFixedUpdate -= timePerFrame;
		}
	}
}

void GameManager::updatePlayers(sf::Time& t_deltaTime)
{
	if (allowSquadDataDisplay == true)
	{
		allowSquadDataDisplay = false;
	}
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		player[index].updateMovingTexures(t_deltaTime);
		//player[index].turnFirstCheck();
		if (player[index].getSquadNumHovered(mousePosFloat) != -1)
		{
			squadData = player[index].getSquadData(player[index].getSquadNumHovered(worldTiles.tileOnMouse()));
			allowSquadDataDisplay = true;

			updateUnitDataDisplay();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
			{
				std::cout << "eliminate unit " << std::to_string(player[index].getSquadNumHovered(worldTiles.tileOnMouse()));
				player[index].eliminateUnit(player[index].getSquadNumHovered(worldTiles.tileOnMouse()));
				continue;
			}
		}

		if ((whosTurn - 1) == index && openCreateUnitMenu == false)
		{
			if (player[index].unitThatRequestedPath != -1)
			{
				int squad = player[index].unitThatRequestedPath;
				std::vector<int> newPath = worldTiles.getPathToTarget(player[index].playersSquads[squad].currentPos, player[index].playersSquads[squad].targetPos);
				player[index].givePathToSquad(newPath);
				/*player[index].playersSquads[squad].pathToTarget = newPath;
				player[index].unitThatRequestedPath = -1;
				player[index].playersSquads[squad].currentPos = { 0,0 };
				player[index].playersSquads[squad].targetPos = { 0,0 };
				player[index].playersSquads[squad].requestPath = false;*/
			}
			gameUI.moneyDisplay.setString(std::to_string(player[index].getMoney()));			
			if (player[whosTurn - 1].playerEliminated == true)
			{
				whosTurn++;
				setPlayerTurnColour();
				gameUI.playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
				player[whosTurn - 1].turnActive();
				break;
			}
			worldTiles.hightlightTiles(player[index].squadDistanceValid(worldTiles.tileHoveredOverPos()));
			if (player[index].targetNeeded == true)
			{
				worldTiles.findTargetedTile();
				//std::cout << player[index].checkIfContained(worldTiles.tileHoveredOver()) << "\n";
				if (worldTiles.positionUpdated == true && player[index].checkIfContained(worldTiles.mousePosViewport()) == false && player[index].distanceOK == true)
				{
					player[index].setTargetPosition(worldTiles.currentPlayerTarget(player[index].unitsMoved));
					worldTiles.positionUpdated = false;
				}
				else
				{
					//worldTiles.deactiveateTile();
					worldTiles.positionUpdated = false;
				}
			}
			player[index].update(t_deltaTime);

			if (player[index].searchForPath == true)
			{
				sf::Vector2f playerTarget = player[index].getTargetPosition();
				if (playerTarget != sf::Vector2f(0, 0))
				{
					std::cout << "player " << index << " requested path\n";
					player[index].searchForPath = false;
					player[index].givePathToFormation(worldTiles.getPathToTarget(player[index].getFormationStart(), playerTarget));//player[index].getFormationTarget()));
				}
				//else std::cout << "target not yet set";
			}

			if (player[index].arrivedAtTarget == true)//if the players turn is over as all units have moved
			{
				std::vector<sf::RectangleShape> playerHHitboxes = player[whosTurn - 1].returnSquadHorizontalHitboxes();
				std::vector<sf::RectangleShape> playerVHitboxes = player[whosTurn - 1].returnSquadVerticalHitboxes();

				for (int playerHIndex = 0; playerHIndex < playerHHitboxes.size(); playerHIndex++)
				{
					for (int loopPlayerIndex = 0; loopPlayerIndex < MAX_PLAYERS; loopPlayerIndex++)
					{
						if (loopPlayerIndex != whosTurn - 1 && player[loopPlayerIndex].playerEliminated == false)
						{
							std::vector<sf::RectangleShape> enemyHHitboxes = player[loopPlayerIndex].returnSquadHorizontalHitboxes();
							std::vector<sf::RectangleShape> enemyVHitboxes = player[loopPlayerIndex].returnSquadVerticalHitboxes();

							for (int enemyHIndex = 0; enemyHIndex < enemyHHitboxes.size(); enemyHIndex++)
							{
								if (
									playerHHitboxes[playerHIndex].getGlobalBounds().intersects(enemyHHitboxes[enemyHIndex].getGlobalBounds()) ||
									playerHHitboxes[playerHIndex].getGlobalBounds().intersects(enemyVHitboxes[enemyHIndex].getGlobalBounds()) ||
									playerVHitboxes[playerHIndex].getGlobalBounds().intersects(enemyHHitboxes[enemyHIndex].getGlobalBounds()) ||
									playerVHitboxes[playerHIndex].getGlobalBounds().intersects(enemyVHitboxes[enemyHIndex].getGlobalBounds())
									)
								{
									player[whosTurn - 1].setUnitToFaceEnemy(playerHIndex, player[loopPlayerIndex].getSquadPosition());
									player[loopPlayerIndex].setUnitToFaceEnemy(enemyHIndex, playerHHitboxes[playerHIndex].getPosition());

									player[whosTurn - 1].dealDamageToUnit(playerHIndex, player[loopPlayerIndex].getUnitStrength(enemyHIndex));
									player[loopPlayerIndex].dealDamageToUnit(enemyHIndex, player[whosTurn - 1].getUnitStrength(playerHIndex));
								}
							}
						}
					}
				}

				for (int playersIndex = 0; playersIndex < MAX_PLAYERS; playersIndex++)
				{
					player[playersIndex].checkForDeadSquads();
				}


				worldTiles.resetTiles();
				player[index].arrivedAtTarget = false;
				bool playerValid = false;
				while (playerValid == false)
				{
					player[index].addIncomeFromTurn();
					player[index].playerLateTurnEnd();
					whosTurn++;
					if (whosTurn > MAX_PLAYERS)
					{
						whosTurn = 1;
					}
					if (player[whosTurn - 1].playerEliminated == false)
					{
						playerValid = true;
					}

					std::vector<int> unitTiles;
					for (int i = 0; i < MAX_PLAYERS; i++)
					{
						std::vector<int> temp = player[i].returnAllSquadPositions();
						if (temp.empty() == false)
						{
							unitTiles.insert(unitTiles.end(), temp.begin(), temp.end());
						}
						worldTiles.getPlayerTakenTiles(unitTiles);
					}
				}
				
				checkGameOver();

				setPlayerTurnColour();
				gameUI.playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
				player[whosTurn-1].turnActive();
			}
		}
	}
}

void GameManager::userControls(sf::View& t_viewport,sf::Time& t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//move viewport around the screen
	{
		t_viewport.move(0, -400*t_deltaTime.asSeconds());
		if (t_viewport.getCenter().y < TILE_SIZE * 4.975)
		{
			t_viewport.setCenter(t_viewport.getCenter().x, TILE_SIZE * 4.975);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		t_viewport.move(0, 400 * t_deltaTime.asSeconds());
		if (t_viewport.getCenter().y > (TILE_SIZE * TILE_COLUMNS) - (TILE_SIZE * 7.9))
		{
			t_viewport.setCenter(t_viewport.getCenter().x, (TILE_SIZE * TILE_COLUMNS) - (TILE_SIZE * 7.9));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		t_viewport.move(-400 * t_deltaTime.asSeconds(), 0);
		if (t_viewport.getCenter().x < TILE_SIZE * 5.975)
		{
			t_viewport.setCenter(TILE_SIZE * 5.975, t_viewport.getCenter().y);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		t_viewport.move(400 * t_deltaTime.asSeconds(), 0);
		if (t_viewport.getCenter().x > (TILE_SIZE * TILE_COLUMNS) - (TILE_SIZE * 5.975))
		{
			t_viewport.setCenter((TILE_SIZE * TILE_COLUMNS) - (TILE_SIZE * 5.975), t_viewport.getCenter().y);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))//fast zoom
	{
		t_viewport.zoom(0.99);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//standard zoom
	{
		t_viewport.zoom(0.999);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		t_viewport.zoom(1.01);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		t_viewport.zoom(1.001);
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && clickTimer == 0)//debug
	//{
	//	clickTimer = 30;
	//	player[0].eliminateUnit(0);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && clickTimer == 0)//debug
	//{
	//	clickTimer = 30;
	//	player[1].eliminateUnit(0);
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && clickTimer == 0)
	{
		clickTimer = 30;
		std::cout << "Mouse pos X: " << mousePosFloat.x << " Y: " << mousePosFloat.y << "\n";
	}

	if (createUnitActive == true || createTowerActive == true)
	{
		//if (worldTiles.tileHoveredOverPos() != sf::Vector2f(0, 0))
		{
			unitPlacementHighlight.setPosition(worldTiles.tileHoveredOverPos());
		}
	}
}

void GameManager::displayClean(sf::RenderWindow& t_window, sf::View& t_viewport)
{
	t_window.clear(sf::Color(50, 50, 50));
	t_window.setView(t_viewport);
}

void GameManager::display(sf::RenderWindow& t_window)
{
	sf::Vector2i temp = sf::Mouse::getPosition(t_window);

	if (temp.x >= 0 && temp.y >= 0 && static_cast<unsigned int>(temp.x) < t_window.getSize().x && static_cast<unsigned int>(temp.y) < t_window.getSize().y)
	{
		mousePos = sf::Mouse::getPosition(t_window);
		mousePosFloat = t_window.mapPixelToCoords(mousePos);
	}
	//else std::cout << "(GameManager) mouse out of bounds\n";
	gameUI.setMousePos(mousePos);
	worldTiles.render(t_window);
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		if (player[whosTurn - 1].playerEliminated == false && worldEditingEnabled == false)
		{
			player[index].render(t_window);
		}
	}

	if (createUnitActive == true || createTowerActive == true)
	{
		t_window.draw(unitPlacementHighlight);
	}
}

void GameManager::displayHUD(sf::RenderWindow& t_window,sf::View& t_fixedWindow)
{
	t_window.setView(t_fixedWindow);

	gameUI.render(t_window, allowSquadDataDisplay, openCreateUnitMenu, openCreateTowerMenu, gameUI.upgradeMenuOpen);

	if (menuOpen == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameUI.menuStartButton.getGlobalBounds().contains({ mousePos.x*1.0f,mousePos.y*1.0f }))
		{
			menuOpen = false;
		}
		gameUI.renderMainMenu(t_window);
	}

	if (gameOver == true)
	{
		gameUI.renderGameOver(t_window);
	}
	
	t_window.display();
}

void GameManager::handleCollisions()
{
	if (player[whosTurn-1].getTowerNumHovered(worldTiles.tileOnMouse()) != -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameUI.upgradeMenuOpen == false && gameUI.clickTimer == 0)
	{
		gameUI.upgradeMenuOpen = true;
	}
}

void GameManager::menuInteractions()
{
	if (worldEditingEnabled == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && clickTimer == 0)
		{
			editingTerrainType = 0;
			std::cout << "Ground tile selected\n";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && clickTimer == 0)
		{
			editingTerrainType = 1;
			std::cout << "Wall tile selected\n";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && clickTimer == 0)
		{
			editingTerrainType = 2;
			std::cout << "Water tile selected\n";
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			worldTiles.updateTileType(2);
			worldTilesModified = true;
			//clickTimer = 5;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			worldTiles.updateTileType(0);
			worldTilesModified = true;
			//clickTimer = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			worldTiles.updateTileType(editingTerrainType);
			worldTilesModified = true;
		}
	}
	else {
		gameUI.handleMenuInteractions();
		gameUI.handleButtonInteractions();

		if (gameUI.upgradeMenuOpen == true && customUnitModified == false)
		{
			customUnitModified = true;
		}
		if (customUnitModified == true && gameUI.upgradeMenuOpen == false)
		{
			customUnitModified = false;
			player[whosTurn - 1].upgradeCustomUnit(gameUI.customSquadData, gameUI.customUnitSprite);
		}

		if (gameUI.attemptTurnEnd == true)
		{
			gameUI.attemptTurnEnd = false;
			player[whosTurn - 1].attemptEndTurn();
		}

		openCreateTowerMenu = gameUI.openCreateTowerMenu;
		openCreateUnitMenu = gameUI.openCreateUnitMenu;
		createUnitActive = gameUI.createUnitActive;
		createTowerActive = gameUI.createGoldTower;

		if (openCreateTowerMenu == true || openCreateUnitMenu == true || gameUI.upgradeMenuOpen)
		{
			player[whosTurn - 1].menuOpen = true;
		}
		else player[whosTurn - 1].menuOpen = false;

		if (gameUI.resetPlayerForThisTurn == true)
		{
			gameUI.resetPlayerForThisTurn = false;
			player[whosTurn - 1].resetPlayerForThisTurn();
		}

		unitTypeToCreate = gameUI.unitTypeToCreate;

		if (gameUI.createNewTower == true)
		{
			gameUI.createNewTower = false;
			gameUI.createGoldTower = false;
			if (player[whosTurn - 1].getMoney() >= gameUI.cost && player[whosTurn - 1].playerEliminated == false && unitPlacementHighlight.getPosition() != sf::Vector2f(0,0))
			{
				player[whosTurn - 1].spendMoney(gameUI.cost);
				gameUI.moneyDisplay.setString(std::to_string(player[whosTurn - 1].getMoney()));
				player[whosTurn - 1].generateNewTower(gameUI.towerTypeToCreate, whosTurn - 1, unitPlacementHighlight.getPosition());
				createTowerActive = false;

				std::vector<int> unitTiles;
				for (int i = 0; i < MAX_PLAYERS; i++)
				{
					std::vector<int> temp = player[i].returnAllSquadPositions();
					if (temp.empty() == false)
					{
						unitTiles.insert(unitTiles.end(), temp.begin(), temp.end());
					}
					worldTiles.getPlayerTakenTiles(unitTiles);
				}
			}
		}

		if (gameUI.createNewUnit == true)
		{
			gameUI.createNewUnit = false;
			if (player[whosTurn - 1].getMoney() >= gameUI.cost && player[whosTurn - 1].playerEliminated == false && unitPlacementHighlight.getPosition() != sf::Vector2f(0,0))
			{
				player[whosTurn - 1].spendMoney(gameUI.cost);
				gameUI.moneyDisplay.setString(std::to_string(player[whosTurn - 1].getMoney()));
				player[whosTurn - 1].generateNewUnit(whosTurn - 1, unitTypeToCreate, unitPlacementHighlight.getPosition());
				addUnit(whosTurn - 1);//add the new unit to the counter in globals
				createUnitActive = false;

				std::vector<int> unitTiles;
				for (int i = 0; i < MAX_PLAYERS; i++)
				{
					std::vector<int> temp = player[i].returnAllSquadPositions();
					if (temp.empty() == false)
					{
						unitTiles.insert(unitTiles.end(), temp.begin(), temp.end());
					}
					worldTiles.getPlayerTakenTiles(unitTiles);
				}
			}
		}

		/*
		if (gameUI.attemptTurnEnd == true)
		{
			gameUI.attemptTurnEnd = false;
			player[whosTurn - 1].attemptEndTurn();
		}
		if (gameUI.openCreateTowerMenu == true)
		{
			gameUI.openCreateTowerMenu = false;
			openCreateTowerMenu = true;
		}
		if (gameUI.openCreateUnitMenu == true)
		{
			gameUI.openCreateUnitMenu = false;
			openCreateUnitMenu = true;
		}
		createUnitActive = gameUI.createUnitActive;
		*/
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && clickTimer == 0)
	{
		clickTimer = 60;
		worldEditingEnabled = !worldEditingEnabled;
		std::cout << worldEditingEnabled;
	}
}

void GameManager::setPlayerTurnColour()
{
	if (whosTurn == 1)
	{
		gameUI.playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
		gameUI.winScreenMessage.setFillColor(sf::Color(0, 0, 255));
	}
	else if (whosTurn == 2)
	{
		gameUI.playerTurnDisplay.setFillColor(sf::Color(255, 0, 0));
		gameUI.winScreenMessage.setFillColor(sf::Color(255, 0, 0));
	}
	else if (whosTurn == 3)
	{
		gameUI.playerTurnDisplay.setFillColor(sf::Color(0, 255, 255));
		gameUI.winScreenMessage.setFillColor(sf::Color(0, 255, 255));
	}
	else if (whosTurn == 4)
	{
		gameUI.playerTurnDisplay.setFillColor(sf::Color(255, 0, 255));
		gameUI.winScreenMessage.setFillColor(sf::Color(255, 0, 255));
	}
}

void GameManager::checkGameOver()
{
	int eliminatedPlayers = 0;
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		if (player[index].playerEliminated == true)
		{
			eliminatedPlayers++;
		}
		else winner = index;
	}
	if (eliminatedPlayers == MAX_PLAYERS - 1)
	{
		gameOver = true;
		gameUI.winScreenMessage.setString("Player " + std::to_string(winner+1) + " Wins!");
	}
}

void GameManager::addUnit(int t_playerNum)
{
	if (t_playerNum == 0)
	{
		playerOneUnits++;
	}
	if (t_playerNum == 1)
	{
		playerTwoUnits++;
	}
	if (t_playerNum == 2)
	{
		playerThreeUnits++;
	}
	if (t_playerNum == 3)
	{
		playerFourUnits++;
	}
}

void GameManager::removeUnit(int t_playerNum)
{
	if (t_playerNum == 0)
	{
		playerOneUnits--;
	}
	if (t_playerNum == 1)
	{
		playerTwoUnits--;
	}
	if (t_playerNum == 2)
	{
		playerThreeUnits--;
	}
	if (t_playerNum == 3)
	{
		playerFourUnits--;
	}
}

void GameManager::updateUnitDataDisplay()
{
	gameUI.updateUnitDataDisplay(squadData);
	allowSquadDataDisplay = true;
}