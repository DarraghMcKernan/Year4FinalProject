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

	endTurnText.setFont(font);
	endTurnText.setString("End Turn");
	endTurnText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	endTurnText.setFillColor(sf::Color(0, 0, 0));
	endTurnText.setScale(0.75, 0.75);
	endTurnText.setOrigin({ (endTurnText.getGlobalBounds().getSize().x / 2) + 15,(endTurnText.getGlobalBounds().getSize().y / 2) + 15 });
	endTurnText.setPosition(endTurnButton.getPosition());

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

		userControls(viewport,deltaTime);

		updatePlayers(deltaTime);

		worldTiles.update(deltaTime);

		display(window);
		displayHUD(window, fixedWindow);

		while (timeSinceLastFixedUpdate >= timePerFrame)//60fps cap for timers and collisions
		{
			for (int index = 0; index < MAX_PLAYERS; index++)
			{
				player[index].fixedUpdate();
			}
			handleCollisions();
			menuInteractions();
			timeSinceLastFixedUpdate -= timePerFrame;
		}
	}
}

void GameManager::updatePlayers(sf::Time& t_deltaTime)
{
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		if ((whosTurn - 1) == index)
		{
			worldTiles.hightlightTiles(player[index].squadDistanceValid(worldTiles.tileHoveredOver()));
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
			if (player[index].arrivedAtTarget == true)
			{
				worldTiles.resetTiles();
				player[index].arrivedAtTarget = false;
				whosTurn++;
				if (whosTurn > MAX_PLAYERS)
				{
					whosTurn = 1;
				}
				setPlayerTurnColour();
				playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
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
}

void GameManager::displayClean(sf::RenderWindow& t_window, sf::View& t_viewport)
{
	t_window.clear(sf::Color(50, 50, 50));
	t_window.setView(t_viewport);
}

void GameManager::display(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);
	worldTiles.render(t_window);
	for (int index = 0; index < MAX_PLAYERS; index++)
	{
		player[index].render(t_window);
	}
}

void GameManager::displayHUD(sf::RenderWindow& t_window,sf::View& t_fixedWindow)
{
	t_window.setView(t_fixedWindow);

	t_window.draw(hudBacking);
	t_window.draw(endTurnButton);
	t_window.draw(playerTurnDisplay);
	t_window.draw(endTurnText);
	t_window.draw(framerateText);

	t_window.display();
}

void GameManager::handleCollisions()
{

}

void GameManager::menuInteractions()
{
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && endTurnButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		endTurnButton.setFillColor(sf::Color(100, 150, 100));
		clickTimer = 30;
		player[whosTurn-1].attemptEndTurn();
	}
	clickTimer--;
	if (clickTimer < 0)
	{
		clickTimer = 0;
	}
	if (clickTimer == 10)
	{
		endTurnButton.setFillColor(sf::Color(100, 200, 100));
	}
}

void GameManager::setPlayerTurnColour()
{
	if (whosTurn == 1)
	{
		playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
	}
	else if (whosTurn == 2)
	{
		playerTurnDisplay.setFillColor(sf::Color(255, 0, 0));
	}
	else if (whosTurn == 3)
	{
		playerTurnDisplay.setFillColor(sf::Color(0, 255, 255));
	}
	else if (whosTurn == 4)
	{
		playerTurnDisplay.setFillColor(sf::Color(255, 0, 255));
	}
}