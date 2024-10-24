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
	myPlayer.init();

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

			window.clear(sf::Color(50,50,50));

			window.setView(viewport);

			myTileGrid.update();
			if (myTileGrid.positionUpdated == true)
			{
				myPlayer.setPosition(myTileGrid.currentPlayerTarget());
				myTileGrid.positionUpdated = false;
			}
			myPlayer.update();
			
			myTileGrid.render(window);
			myPlayer.render(window);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}