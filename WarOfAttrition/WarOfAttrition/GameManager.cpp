#include "GameManager.h"

void GameManager::startGame()//setup variables needed before the game starts
{
	timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = sf::Time::Zero;
	timeSinceLastFixedUpdate = sf::Time::Zero;
	clock.restart();

	worldTiles.init();
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		player[index].init(index, 0);
	}

	hudBacking.setSize({ SCREEN_WIDTH,SCREEN_HEIGHT / 5 });//the HUD element that shows player turn
	hudBacking.setOrigin({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 5) });
	hudBacking.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT + (SCREEN_HEIGHT / 5) / 2 });
	hudBacking.setFillColor(sf::Color(200, 200, 200));
	hudBacking.setOutlineColor(sf::Color::Black);
	hudBacking.setOutlineThickness(5);

	endTurnButton.setSize({ hudBacking.getSize().x / 6, hudBacking.getSize().y / 3 });
	endTurnButton.setOrigin({ endTurnButton.getSize().x / 2 ,endTurnButton.getSize().y / 2 });
	endTurnButton.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) /2 });
	endTurnButton.setFillColor(sf::Color(100, 200, 100));
	endTurnButton.setOutlineColor(sf::Color::Black);
	endTurnButton.setOutlineThickness(3);

	openUnitMenuButton.setSize({ hudBacking.getSize().x / 6, hudBacking.getSize().y / 3 });
	openUnitMenuButton.setOrigin({ openUnitMenuButton.getSize().x / 2 ,openUnitMenuButton.getSize().y / 2 });
	openUnitMenuButton.setPosition({ SCREEN_WIDTH - (SCREEN_WIDTH / 10),SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) / 2 });
	openUnitMenuButton.setFillColor(sf::Color(100, 200, 150));
	openUnitMenuButton.setOutlineColor(sf::Color::Black);
	openUnitMenuButton.setOutlineThickness(3);

	openTowerMenuButton.setSize({ hudBacking.getSize().x / 5.5f, hudBacking.getSize().y / 3 });
	openTowerMenuButton.setOrigin({ openTowerMenuButton.getSize().x / 2 ,openTowerMenuButton.getSize().y / 2 });
	openTowerMenuButton.setPosition({ SCREEN_WIDTH - (SCREEN_WIDTH / 3.5),SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) / 2 });
	openTowerMenuButton.setFillColor(sf::Color(100, 150, 200));
	openTowerMenuButton.setOutlineColor(sf::Color::Black);
	openTowerMenuButton.setOutlineThickness(3);

	unitMenuBacking.setSize({ SCREEN_WIDTH/ 4, SCREEN_HEIGHT / 2 });
	unitMenuBacking.setOrigin({ unitMenuBacking.getSize().x / 2 ,unitMenuBacking.getSize().y / 2 });
	unitMenuBacking.setPosition({ SCREEN_WIDTH - (SCREEN_WIDTH / 7),SCREEN_HEIGHT - (SCREEN_HEIGHT / 2.65) });
	unitMenuBacking.setFillColor(sf::Color(125, 125, 125));
	unitMenuBacking.setOutlineColor(sf::Color::Black);
	unitMenuBacking.setOutlineThickness(3);

	createTankUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createTankUnit.setOrigin({ createTankUnit.getSize().x / 2 ,createTankUnit.getSize().y / 2 });
	createTankUnit.setPosition({ unitMenuBacking.getPosition().x - unitMenuBacking.getSize().x/4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createTankUnit.setFillColor(sf::Color(200, 200, 100));
	createTankUnit.setOutlineColor(sf::Color::Black);
	createTankUnit.setOutlineThickness(3);

	createPistolUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createPistolUnit.setOrigin({ createPistolUnit.getSize().x / 2 ,createPistolUnit.getSize().y / 2 });
	createPistolUnit.setPosition({ unitMenuBacking.getPosition().x + unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createPistolUnit.setFillColor(sf::Color(100, 200, 200));
	createPistolUnit.setOutlineColor(sf::Color::Black);
	createPistolUnit.setOutlineThickness(3);

	createHeavyTankUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createHeavyTankUnit.setOrigin({ createHeavyTankUnit.getSize().x / 2 ,createHeavyTankUnit.getSize().y / 2 });
	createHeavyTankUnit.setPosition({ unitMenuBacking.getPosition().x - unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y});
	createHeavyTankUnit.setFillColor(sf::Color(200, 100, 200));
	createHeavyTankUnit.setOutlineColor(sf::Color::Black);
	createHeavyTankUnit.setOutlineThickness(3);

	createGoldMineTower.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createGoldMineTower.setOrigin({ createGoldMineTower.getSize().x / 2 ,createGoldMineTower.getSize().y / 2 });
	createGoldMineTower.setPosition({ unitMenuBacking.getPosition().x + unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createGoldMineTower.setFillColor(sf::Color(200, 200, 100));
	createGoldMineTower.setOutlineColor(sf::Color::Black);
	createGoldMineTower.setOutlineThickness(3);

	menuBackground.setFillColor(sf::Color::Black);
	menuBackground.setSize({ SCREEN_WIDTH-10,SCREEN_HEIGHT-10 });
	menuBackground.setOrigin({ menuBackground.getSize().x / 2,menuBackground.getSize().y / 2 });
	menuBackground.setPosition({ (menuBackground.getSize().x / 2) + 5,(menuBackground.getSize().y / 2) + 5});
	menuBackground.setOutlineColor(sf::Color(200, 200, 100));
	menuBackground.setOutlineThickness(10);

	menuStartButton.setFillColor(sf::Color(200, 200, 200));
	menuStartButton.setSize({ SCREEN_WIDTH / 4,SCREEN_HEIGHT / 10 });
	menuStartButton.setOrigin({ menuStartButton.getSize().x / 2,menuStartButton.getSize().y / 2 });
	menuStartButton.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2});
	menuStartButton.setOutlineColor(sf::Color(100, 250, 200));
	menuStartButton.setOutlineThickness(3);

	unitPlacementHighlight.setRadius(20);
	unitPlacementHighlight.setOutlineColor(sf::Color::Green);
	unitPlacementHighlight.setOutlineThickness(2);
	unitPlacementHighlight.setOrigin(unitPlacementHighlight.getRadius(), unitPlacementHighlight.getRadius());
	unitPlacementHighlight.setFillColor(sf::Color::Transparent);
	
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	playerTurnDisplay.setFont(font);
	playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
	playerTurnDisplay.setCharacterSize(60);//increase size and then downscale to prevent blurred text
	playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
	playerTurnDisplay.setOutlineThickness(2);
	playerTurnDisplay.setScale(0.75, 0.75);
	playerTurnDisplay.setOrigin(0, 10);
	playerTurnDisplay.setPosition(SCREEN_WIDTH/50, SCREEN_HEIGHT - (SCREEN_HEIGHT / 6.5) / 2);
	
	winScreenMessage.setFont(font);
	winScreenMessage.setString("Player " + std::to_string(whosTurn) + "'s Wins!");
	winScreenMessage.setCharacterSize(60);//increase size and then downscale to prevent blurred text
	winScreenMessage.setFillColor(sf::Color(0, 0, 255));
	winScreenMessage.setOutlineThickness(2);
	winScreenMessage.setScale(0.75, 0.75);
	winScreenMessage.setOrigin(winScreenMessage.getGlobalBounds().width/2, winScreenMessage.getGlobalBounds().height / 2);
	winScreenMessage.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT /2);

	endTurnText.setFont(font);
	endTurnText.setString("End Turn");
	endTurnText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	endTurnText.setFillColor(sf::Color(0, 0, 0));
	endTurnText.setScale(0.75, 0.75);
	endTurnText.setOrigin({ (endTurnText.getGlobalBounds().getSize().x / 2) + 15,(endTurnText.getGlobalBounds().getSize().y / 2) + 15 });
	endTurnText.setPosition(endTurnButton.getPosition());

	createUnitText.setFont(font);
	createUnitText.setString("Create Unit");
	createUnitText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	createUnitText.setFillColor(sf::Color(0, 0, 0));
	createUnitText.setScale(0.75, 0.75);
	createUnitText.setOrigin({ (endTurnText.getGlobalBounds().getSize().x / 2) +40,(endTurnText.getGlobalBounds().getSize().y / 2) + 15 });
	createUnitText.setPosition(openUnitMenuButton.getPosition());

	createTowerText.setFont(font);
	createTowerText.setString("Create Tower");
	createTowerText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	createTowerText.setFillColor(sf::Color(0, 0, 0));
	createTowerText.setScale(0.75, 0.75);
	createTowerText.setOrigin({ (createTowerText.getGlobalBounds().getSize().x / 2) + 29,(createTowerText.getGlobalBounds().getSize().y / 2) + 15 });
	createTowerText.setPosition(openTowerMenuButton.getPosition());

	menuStartButtonText.setFont(font);
	menuStartButtonText.setString("Start Game");
	menuStartButtonText.setCharacterSize(70);//increase size and then downscale to prevent blurred text
	menuStartButtonText.setFillColor(sf::Color::Black);
	menuStartButtonText.setScale(0.75, 0.75);
	menuStartButtonText.setOrigin({ (menuStartButtonText.getGlobalBounds().getSize().x / 2)+30,(menuStartButtonText.getGlobalBounds().getSize().y / 2)+22});
	menuStartButtonText.setPosition(menuStartButton.getPosition());

	squadSpeedDisplay.setFont(font);
	squadSpeedDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadSpeedDisplay.setFillColor(sf::Color::Black);
	squadSpeedDisplay.setScale(0.75, 0.75);
	squadSpeedDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadSpeedDisplay.setPosition(50,90);

	squadStrengthDisplay.setFont(font);
	squadStrengthDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadStrengthDisplay.setFillColor(sf::Color::Black);
	squadStrengthDisplay.setScale(0.75, 0.75);
	squadStrengthDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadStrengthDisplay.setPosition(50, 110);

	squadTeamDisplay.setFont(font);
	squadTeamDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadTeamDisplay.setFillColor(sf::Color::Black);
	squadTeamDisplay.setScale(0.75, 0.75);
	squadTeamDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadTeamDisplay.setPosition(50, 130);

	squadTypeDisplay.setFont(font);
	squadTypeDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadTypeDisplay.setFillColor(sf::Color::Black);
	squadTypeDisplay.setScale(0.75, 0.75);
	squadTypeDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadTypeDisplay.setPosition(50, 150);

	unitDataDisplayBacking.setSize({ SCREEN_WIDTH / 3,SCREEN_HEIGHT / 5 });
	unitDataDisplayBacking.setOrigin({ unitDataDisplayBacking.getSize().x / 2 ,unitDataDisplayBacking.getSize().y / 2 });
	unitDataDisplayBacking.setPosition({SCREEN_WIDTH / 5,SCREEN_HEIGHT / 5 });
	unitDataDisplayBacking.setFillColor(sf::Color(200, 200, 200));
	unitDataDisplayBacking.setOutlineThickness(6);
	unitDataDisplayBacking.setOutlineColor(sf::Color::Black);

	moneyDisplay.setFont(font);
	moneyDisplay.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	moneyDisplay.setFillColor(sf::Color::Black);
	moneyDisplay.setScale(0.75, 0.75);
	moneyDisplay.setOrigin({ (moneyDisplay.getGlobalBounds().getSize().x / 2),(moneyDisplay.getGlobalBounds().getSize().y / 2) });
	moneyDisplay.setPosition((SCREEN_WIDTH / 2) - SCREEN_WIDTH/5, SCREEN_HEIGHT - (SCREEN_HEIGHT / 12.5));
	moneyDisplay.setString(std::to_string(1000));

	if (!moneyIconTexture.loadFromFile("ASSETS/MoneyIcon.png"))
	{
		std::cout << "Error loading moneyIcon from file\n";
	}
	moneyIcon.setTexture(moneyIconTexture);
	moneyIcon.setOrigin(moneyIcon.getGlobalBounds().width / 2, moneyIcon.getGlobalBounds().height / 2);
	moneyIcon.setPosition((SCREEN_WIDTH / 2) - SCREEN_WIDTH / 4.5, SCREEN_HEIGHT - (SCREEN_HEIGHT / 20));
	moneyIcon.setScale(3, 3);

	framerateText.setFont(font);

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
			framerateText.setString(std::to_string(frameCount));
			frameCount = 0;//reset the frames passed
			elapsedTime = 0.0f;//reset time since last check
		}
		

		displayClean(window, viewport);

		//worldTiles.update(deltaTime);

		if (menuOpen == false && worldEditingEnabled == false)
		{
			userControls(viewport, deltaTime);

			updatePlayers(deltaTime);

			worldTiles.update(deltaTime);
		}

		display(window);
		displayHUD(window, fixedWindow);

		while (timeSinceLastFixedUpdate >= timePerFrame)//60fps cap for timers and collisions
		{
			for (int index = 0; index < MAX_PLAYERS; index++)
			{
				if (player[whosTurn - 1].playerEliminated == false)
				{
					player[index].fixedUpdate();
				}				
			}
			handleCollisions();
			menuInteractions();
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
		if (player[index].getSquadNumHovered(mousePosFloat) != -1)
		{
			squadData = player[index].getSquadData(player[index].getSquadNumHovered(worldTiles.tileHoveredOverPos()));
			unitDataDisplayBacking.setPosition({mousePos.x - (SCREEN_WIDTH / 5), mousePos.y - (SCREEN_HEIGHT / 7)});
			squadTeamDisplay.setPosition(mousePos.x - 350,mousePos.y - 180);
			squadTypeDisplay.setPosition(mousePos.x - 350,mousePos.y - 160);
			squadStrengthDisplay.setPosition(mousePos.x - 350,mousePos.y - 140);
			squadSpeedDisplay.setPosition(mousePos.x - 350,mousePos.y - 120);
			allowSquadDataDisplay = true;

			squadSpeedDisplay.setString("Speed: " + std::to_string(squadData.moveSpeed));
			squadStrengthDisplay.setString("Strength: " + std::to_string(squadData.squadStrength));
			squadTypeDisplay.setString("Type: " + std::to_string(squadData.unitType));
			squadTeamDisplay.setString("Team: " + std::to_string(squadData.teamNum + 1));

			updateUnitDataDisplay();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
			{
				std::cout << "eliminate unit " << std::to_string(player[index].getSquadNumHovered(worldTiles.tileHoveredOverPos()));
				player[index].eliminateUnit(player[index].getSquadNumHovered(worldTiles.tileHoveredOverPos()));
				continue;
			}
		}

		if ((whosTurn - 1) == index && openCreateUnitMenu == false)
		{
			moneyDisplay.setString(std::to_string(player[index].getMoney()));			
			if (player[whosTurn - 1].playerEliminated == true)
			{
				whosTurn++;
				setPlayerTurnColour();
				playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
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
			if (player[index].arrivedAtTarget == true)//if the players turn is over as all units have moved
			{
				for (int playersIndex = 0; playersIndex < MAX_PLAYERS; playersIndex++)
				{
					if (playersIndex != whosTurn - 1 && player[playersIndex].playerEliminated == false)
					{
						std::vector<int> damageTaken = player[playersIndex].collisionCheckerDamage(player[whosTurn - 1].returnMovedSquads(), 400);//only hurts defending squad currently
						
						player[whosTurn-1].dealDamage(damageTaken);//this player needs to also take damage
						//player[playersIndex]//go through each player and assign damage;
						//should be significantly more efficient to store all moved squads here then get all squads from enemies and compare them here before doing damage to each other
						//trying to keep it self contained might have made this the most inefficient part of the game though it does only run between turns where performance drops would be negligable
					}
				}


				worldTiles.resetTiles();
				player[index].arrivedAtTarget = false;
				bool playerValid = false;
				while (playerValid == false)
				{
					player[index].addIncomeFromTurn();
					whosTurn++;
					if (whosTurn > MAX_PLAYERS)
					{
						whosTurn = 1;
					}
					if (player[whosTurn - 1].playerEliminated == false)
					{
						playerValid = true;
					}
				}
				
				checkGameOver();

				setPlayerTurnColour();
				playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
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
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		t_viewport.move(0, 400 * t_deltaTime.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		t_viewport.move(-400 * t_deltaTime.asSeconds(), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		t_viewport.move(400 * t_deltaTime.asSeconds(), 0);
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && clickTimer == 0)//debug
	{
		clickTimer = 30;
		player[0].eliminateUnit(0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && clickTimer == 0)//debug
	{
		clickTimer = 30;
		player[1].eliminateUnit(0);
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && clickTimer == 0)//debug
	//{
	//	clickTimer = 30;
	//	player[2].eliminateUnit(0);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && clickTimer == 0)//debug
	//{
	//	clickTimer = 30;
	//	player[3].eliminateUnit(0);
	//}

	if (createUnitActive == true)
	{
		unitPlacementHighlight.setPosition(worldTiles.tileHoveredOverPos());
	}
}

void GameManager::displayClean(sf::RenderWindow& t_window, sf::View& t_viewport)
{
	t_window.clear(sf::Color(50, 50, 50));
	t_window.setView(t_viewport);
}

void GameManager::display(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);
	mousePosFloat = t_window.mapPixelToCoords(mousePos);

	worldTiles.render(t_window);
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		if (player[whosTurn - 1].playerEliminated == false && worldEditingEnabled == false)
		{
			player[index].render(t_window);
		}
	}

	if (createUnitActive == true)
	{
		t_window.draw(unitPlacementHighlight);
	}
}

void GameManager::displayHUD(sf::RenderWindow& t_window,sf::View& t_fixedWindow)
{
	t_window.setView(t_fixedWindow);

	t_window.draw(hudBacking);
	t_window.draw(endTurnButton);
	t_window.draw(openUnitMenuButton);
	t_window.draw(openTowerMenuButton);
	t_window.draw(playerTurnDisplay);
	t_window.draw(endTurnText);
	t_window.draw(createUnitText);
	t_window.draw(createTowerText);
	t_window.draw(moneyDisplay);
	t_window.draw(moneyIcon);
	t_window.draw(framerateText);

	if (allowSquadDataDisplay == true)
	{
		t_window.draw(unitDataDisplayBacking);
		t_window.draw(squadSpeedDisplay);
		t_window.draw(squadStrengthDisplay);
		t_window.draw(squadTypeDisplay);
		t_window.draw(squadTeamDisplay);
	}

	if (openCreateUnitMenu == true)
	{
		t_window.draw(unitMenuBacking);
		t_window.draw(createTankUnit);
		t_window.draw(createPistolUnit);
		t_window.draw(createHeavyTankUnit);
	}
	if (openCreateTowerMenu == true)
	{
		t_window.draw(unitMenuBacking);
		t_window.draw(createGoldMineTower);
	}

	if (menuOpen == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuStartButton.getGlobalBounds().contains({ mousePos.x*1.0f,mousePos.y*1.0f }))
		{
			menuOpen = false;
		}
		t_window.draw(menuBackground);
		t_window.draw(menuStartButton);
		t_window.draw(menuStartButtonText);
	}

	if (gameOver == true)
	{
		t_window.draw(menuBackground);
		t_window.draw(winScreenMessage);
	}
	
	t_window.display();
}

void GameManager::handleCollisions()
{

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
			worldTiles.updateTileType(editingTerrainType);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			worldTiles.updateTileType(editingTerrainType);
		}
	}
	else {
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && endTurnButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickTimer == 0)
		{
			endTurnButton.setFillColor(sf::Color(100, 150, 100));
			clickTimer = 30;
			player[whosTurn - 1].attemptEndTurn();
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openUnitMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == false && clickTimer == 0)
		{
			openUnitMenuButton.setFillColor(sf::Color(100, 150, 100));
			clickTimer = 30;
			openCreateUnitMenu = true;
			openCreateTowerMenu = false;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openUnitMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
		{
			openUnitMenuButton.setFillColor(sf::Color(100, 150, 100));
			clickTimer = 30;
			openCreateUnitMenu = false;
			createUnitActive = false;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openTowerMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == false && clickTimer == 0)
		{
			openTowerMenuButton.setFillColor(sf::Color(100, 100, 150));
			clickTimer = 30;
			openCreateTowerMenu = true;
			openCreateUnitMenu = false;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openTowerMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == true && clickTimer == 0)
		{
			openTowerMenuButton.setFillColor(sf::Color(100, 100, 150));
			clickTimer = 30;
			openCreateTowerMenu = false;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createTankUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
		{
			clickTimer = 30;
			createTankUnit.setFillColor(sf::Color(150, 150, 100));
			createUnitActive = true;
			unitTypeToCreate = 0;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createPistolUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
		{
			clickTimer = 30;
			createPistolUnit.setFillColor(sf::Color(150, 150, 100));
			createUnitActive = true;
			unitTypeToCreate = 1;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createHeavyTankUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
		{
			clickTimer = 30;
			createHeavyTankUnit.setFillColor(sf::Color(150, 150, 100));
			createUnitActive = true;
			unitTypeToCreate = 2;
		}
		else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createGoldMineTower.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == true && clickTimer == 0)
		{
			player[whosTurn - 1].spendMoney(750);
			moneyDisplay.setString(std::to_string(player[whosTurn - 1].getMoney()));
			clickTimer = 30;
			createGoldMineTower.setFillColor(sf::Color(150, 150, 100));
			player[whosTurn - 1].generateNewTower(0, whosTurn - 1, sf::Vector2f(200, 200));
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && createUnitActive == true && clickTimer == 0 && player[whosTurn - 1].playerEliminated == false)
		{
			if (player[whosTurn - 1].getMoney() > 100)
			{
				player[whosTurn - 1].spendMoney(100);
				moneyDisplay.setString(std::to_string(player[whosTurn - 1].getMoney()));
				player[whosTurn - 1].generateNewUnit(whosTurn - 1, unitTypeToCreate, unitPlacementHighlight.getPosition());
				addUnit(whosTurn - 1);//add the new unit to the counter in globals
				createUnitActive = false;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && clickTimer == 0)
		{
			clickTimer = 30;
			worldEditingEnabled = !worldEditingEnabled;
			std::cout << worldEditingEnabled;
		}
	}


	clickTimer--;
	if (clickTimer < 0)
	{
		clickTimer = 0;
	}
	if (clickTimer == 10)
	{
		endTurnButton.setFillColor(sf::Color(100, 200, 100));
		openUnitMenuButton.setFillColor(sf::Color(100, 200, 150));
		openTowerMenuButton.setFillColor(sf::Color(100, 150, 200));
		createTankUnit.setFillColor(sf::Color(200, 200, 100));
		createHeavyTankUnit.setFillColor(sf::Color(200, 100, 200));
		createGoldMineTower.setFillColor(sf::Color(200, 200, 100));
	}
}

void GameManager::setPlayerTurnColour()
{
	if (whosTurn == 1)
	{
		playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
		winScreenMessage.setFillColor(sf::Color(0, 0, 255));
	}
	else if (whosTurn == 2)
	{
		playerTurnDisplay.setFillColor(sf::Color(255, 0, 0));
		winScreenMessage.setFillColor(sf::Color(255, 0, 0));
	}
	else if (whosTurn == 3)
	{
		playerTurnDisplay.setFillColor(sf::Color(0, 255, 255));
		winScreenMessage.setFillColor(sf::Color(0, 255, 255));
	}
	else if (whosTurn == 4)
	{
		playerTurnDisplay.setFillColor(sf::Color(255, 0, 255));
		winScreenMessage.setFillColor(sf::Color(255, 0, 255));
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
		winScreenMessage.setString("Player " + std::to_string(winner+1) + " Wins!");
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
	unitDataDisplayBacking.setPosition({ mousePos.x - (SCREEN_WIDTH / 5), mousePos.y - (SCREEN_HEIGHT / 7) });

	if(unitDataDisplayBacking.getPosition().x < unitDataDisplayBacking.getGlobalBounds().getSize().x/2)
	{
		unitDataDisplayBacking.setPosition(unitDataDisplayBacking.getGlobalBounds().getSize().x / 2, unitDataDisplayBacking.getPosition().y);
	}
	if (unitDataDisplayBacking.getPosition().y < unitDataDisplayBacking.getGlobalBounds().getSize().y / 2)
	{
		unitDataDisplayBacking.setPosition(unitDataDisplayBacking.getPosition().x, unitDataDisplayBacking.getGlobalBounds().getSize().y / 2);
	}

	float xSize = unitDataDisplayBacking.getGlobalBounds().getSize().x;
	float ySize = unitDataDisplayBacking.getGlobalBounds().getSize().y;

	squadTeamDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25));
	squadTypeDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25) + ySize/8);
	squadStrengthDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25)+ ySize / 8*2);
	squadSpeedDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25)+ ySize / 8*3);

	//squadTeamDisplay.setPosition(mousePos.x - 350, mousePos.y - 180);
	//squadTypeDisplay.setPosition(mousePos.x - 350, mousePos.y - 160);
	//squadStrengthDisplay.setPosition(mousePos.x - 350, mousePos.y - 140);
	//squadSpeedDisplay.setPosition(mousePos.x - 350, mousePos.y - 120);

	allowSquadDataDisplay = true;

	squadSpeedDisplay.setString("Speed: " + std::to_string(squadData.moveSpeed));
	squadStrengthDisplay.setString("Strength: " + std::to_string(squadData.squadStrength));
	squadTypeDisplay.setString("Type: " + std::to_string(squadData.unitType));
	squadTeamDisplay.setString("Team: " + std::to_string(squadData.teamNum + 1));
}