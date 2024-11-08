#ifdef _DEBUG  
#pragma comment(lib,"sfml-graphics-d.lib")  
#pragma comment(lib,"sfml-audio-d.lib")  
#pragma comment(lib,"sfml-system-d.lib")  
#pragma comment(lib,"sfml-window-d.lib")  
#pragma comment(lib,"sfml-network-d.lib")  
#else  
#pragma comment(lib,"sfml-graphics.lib")  
#pragma comment(lib,"sfml-audio.lib")  
#pragma comment(lib,"sfml-system.lib")  
#pragma comment(lib,"sfml-window.lib")  
#pragma comment(lib,"sfml-network.lib")  
#endif  

#include "globals.h"
#include "TileGrid.h"
#include "Player.h"
#include "Enemy.h"

void main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "War of Attrition");

	sf::View viewport(sf::FloatRect((SCREEN_WIDTH / 2) - VIEWPORT_WIDTH/2, (SCREEN_HEIGHT / 2) - VIEWPORT_HEIGHT/2, VIEWPORT_WIDTH, VIEWPORT_HEIGHT));//center the viewport on the map

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	TileGrid myTileGrid;
	myTileGrid.init();
	Player myPlayer;
	myPlayer.init(0);
	//Enemy myEnemy;
	//myEnemy.init();

	//multiplayer section
	Player myPlayer2;//for multiplayer, player 2 is identical in function to player 1
	myPlayer2.init(1);

	sf::View fixedWindow;
	fixedWindow = window.getView();

	Player myPlayer3;
	myPlayer3.init(2);
	Player myPlayer4;
	myPlayer4.init(3);

	int numOfPlayers = 4;
	int whosTurn = 1;

	sf::RectangleShape hudBacking;
	hudBacking.setSize({ SCREEN_WIDTH,SCREEN_HEIGHT/ 5 });
	hudBacking.setOrigin({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 5) });
	hudBacking.setPosition({ SCREEN_WIDTH/2,SCREEN_HEIGHT + (SCREEN_HEIGHT / 5)/2 });
	hudBacking.setFillColor(sf::Color(200, 200, 200));
	hudBacking.setOutlineColor(sf::Color::Black);
	hudBacking.setOutlineThickness(5);
	sf::Font font;
	sf::Text playerTurnDisplay;

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
	playerTurnDisplay.setPosition(0, SCREEN_HEIGHT - (SCREEN_HEIGHT / 5)/2);

	int enemyRandTimer = 600;

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//move viewport around the screen
			{
				viewport.move(0, -4 );
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
			{
				viewport.move(0, 4);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				viewport.move(-4, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
			{
				viewport.move(4, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				viewport.zoom(0.99);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				viewport.zoom(1.01);
			}
			/*if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					viewport.zoom(1.01);
				}
				if (event.mouseWheelScroll.delta < 0)
				{
					viewport.zoom(0.99);
				}
			}*/

			window.clear(sf::Color(50,50,50));

			window.setView(viewport);

			myTileGrid.update();

			if (whosTurn == 1)
			{
				if (myPlayer.targetNeeded == true)
				{
					myTileGrid.findTargetedTile();
					if (myTileGrid.positionUpdated == true)
					{
						myPlayer.setTargetPosition(myTileGrid.currentPlayerTarget());
						myTileGrid.positionUpdated = false;
					}
				}
				myPlayer.update();
				if (myPlayer.arrivedAtTarget == true)
				{
					myTileGrid.deactiveateTile();
					myPlayer.arrivedAtTarget = false;
					whosTurn++;
					playerTurnDisplay.setFillColor(sf::Color(255, 0, 0));
					playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
				}
			}
			

			if (whosTurn == 2)
			{
				if (myPlayer2.targetNeeded == true)
				{
					myTileGrid.findTargetedTile();
					if (myTileGrid.positionUpdated == true)
					{
						myPlayer2.setTargetPosition(myTileGrid.currentPlayerTarget());
						myTileGrid.positionUpdated = false;
					}
				}
				myPlayer2.update();
				if (myPlayer2.arrivedAtTarget == true)
				{
					myTileGrid.deactiveateTile();
					myPlayer2.arrivedAtTarget = false;
					whosTurn++;
					playerTurnDisplay.setFillColor(sf::Color(0, 255, 255));					
					if (whosTurn > numOfPlayers)
					{
						whosTurn = 1;
					}
					playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
				}
			}
			
			if (whosTurn == 3)
			{
				if (myPlayer3.targetNeeded == true)
				{
					myTileGrid.findTargetedTile();
					if (myTileGrid.positionUpdated == true)
					{
						myPlayer3.setTargetPosition(myTileGrid.currentPlayerTarget());
						myTileGrid.positionUpdated = false;
					}
				}
				myPlayer3.update();
				if (myPlayer3.arrivedAtTarget == true)
				{
					myTileGrid.deactiveateTile();
					myPlayer3.arrivedAtTarget = false;
					whosTurn++;
					playerTurnDisplay.setFillColor(sf::Color(255, 0, 255));			
					if (whosTurn > numOfPlayers)
					{
						whosTurn = 1;
					}
					playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
				}
			}

			if (whosTurn == 4)
			{
				if (myPlayer4.targetNeeded == true)
				{
					myTileGrid.findTargetedTile();
					if (myTileGrid.positionUpdated == true)
					{
						myPlayer4.setTargetPosition(myTileGrid.currentPlayerTarget());
						myTileGrid.positionUpdated = false;
					}
				}
				myPlayer4.update();
				if (myPlayer4.arrivedAtTarget == true)
				{
					myTileGrid.deactiveateTile();
					myPlayer4.arrivedAtTarget = false;
					whosTurn++;
					playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
					if (whosTurn > numOfPlayers)
					{
						whosTurn = 1;
					}
					playerTurnDisplay.setString("Player " + std::to_string(whosTurn) + "'s Turn");
				}
			}
			//myEnemy.update();
			/*enemyRandTimer--;
			if (enemyRandTimer < 0)
			{
				myEnemy.setTargetPos(rand() % (TILE_ROWS * TILE_COLUMNS));
				enemyRandTimer = 600;
			}*/

			/*if (myPlayer.getPlayerShape().getGlobalBounds().intersects(myEnemy.getEnemyShape().getGlobalBounds()))
			{
				int tempDamage = myPlayer.getStrength();
				myPlayer.takeDamage(myEnemy.getStrength());
				myEnemy.takeDamage(tempDamage);
			}*/

			
			myTileGrid.render(window);
			myPlayer.render(window);
			myPlayer2.render(window);

			myPlayer3.render(window);
			myPlayer4.render(window);
			//myEnemy.render(window);

			window.setView(fixedWindow);

			window.draw(hudBacking);
			window.draw(playerTurnDisplay);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}