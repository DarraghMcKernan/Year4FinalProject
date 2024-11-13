#include "GameManager.h"

void GameManager::startGame()//setup variables needed before the game starts
{
	timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = sf::Time::Zero;
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

	updateLoop();
}

void GameManager::updateLoop()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "War of Attrition");
	sf::View viewport(sf::FloatRect((SCREEN_WIDTH / 2) - VIEWPORT_WIDTH / 2, (SCREEN_HEIGHT / 2) - VIEWPORT_HEIGHT / 2, VIEWPORT_WIDTH, VIEWPORT_HEIGHT));//center the viewport on the map
	sf::View fixedWindow;
	fixedWindow = window.getView();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			displayClean(window, viewport);

			worldTiles.update();

			userControls(viewport);

			updatePlayers();

			display(window);
			displayHUD(window, fixedWindow);

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}

void GameManager::updatePlayers()
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
			player[index].update();
			if (player[index].arrivedAtTarget == true)
			{
				worldTiles.deactiveateTile();
				player[index].arrivedAtTarget = false;
				whosTurn++;
				if (whosTurn > MAX_PLAYERS)
				{
					whosTurn = 1;
				}
				playerTurnDisplay.setFillColor(sf::Color(255, 0, 0));
				playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
			}
		}
	}
}

void GameManager::userControls(sf::View& t_viewport)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//move viewport around the screen
	{
		t_viewport.move(0, -4);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		t_viewport.move(0, 4);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		t_viewport.move(-4, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		t_viewport.move(4, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		t_viewport.zoom(0.99);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		t_viewport.zoom(1.01);
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

	t_window.display();
}

void GameManager::handleCollisions()
{

}

void GameManager::menuInteractions()
{

}
