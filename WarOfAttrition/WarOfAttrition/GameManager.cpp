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
		player[index].init(index);
	}

	hudBacking.setSize({ SCREEN_WIDTH,SCREEN_HEIGHT / 5 });//the HUD element that shows player turn
	hudBacking.setOrigin({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 5) });
	hudBacking.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT + (SCREEN_HEIGHT / 5) / 2 });
	hudBacking.setFillColor(sf::Color(200, 200, 200));
	hudBacking.setOutlineColor(sf::Color::Black);
	hudBacking.setOutlineThickness(5);
	
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	playerTurnDisplay.setFont(font);
	playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
	playerTurnDisplay.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
	playerTurnDisplay.setOutlineThickness(2);
	playerTurnDisplay.setScale(0.75, 0.75);
	playerTurnDisplay.setOrigin(0, 10);
	playerTurnDisplay.setPosition(0, SCREEN_HEIGHT - (SCREEN_HEIGHT / 5) / 2);

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

		display(window);
		displayHUD(window, fixedWindow);

		while (timeSinceLastFixedUpdate >= timePerFrame)//60fps cap for timers and collisions
		{
			for (int index = 0; index < MAX_PLAYERS; index++)
			{
				player[index].fixedUpdate();
			}
			handleCollisions();
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
			if (player[index].targetNeeded == true)
			{
				worldTiles.findTargetedTile();
				//std::cout << player[index].checkIfContained(worldTiles.tileHoveredOver()) << "\n";
				if (worldTiles.positionUpdated == true && player[index].checkIfContained(worldTiles.tileHoveredOver()) == false)
				{
					player[index].setTargetPosition(worldTiles.currentPlayerTarget());
					worldTiles.positionUpdated = false;
				}
				else
				{
					worldTiles.deactiveateTile();
					worldTiles.positionUpdated = false;
				}
			}
			player[index].update(t_deltaTime);
			if (player[index].arrivedAtTarget == true)
			{
				worldTiles.deactiveateTile();
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
	t_window.draw(playerTurnDisplay);
	t_window.draw(framerateText);

	t_window.display();
}

void GameManager::handleCollisions()
{

}

void GameManager::menuInteractions()
{

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