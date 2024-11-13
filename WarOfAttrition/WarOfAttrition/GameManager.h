#pragma once
#include "globals.h"
#include "Player.h"
#include "TileGrid.h"
#include "Enemy.h"

class GameManager
{
public:
	void startGame();

private:
	void updateLoop();//the loop that manages the game, should always be running
	void updatePlayers(sf::Time& t_deltaTime);//update all players
	void userControls(sf::View& t_viewport,sf::Time& t_deltaTime);//handle all user inputs
	void displayClean(sf::RenderWindow& t_window,sf::View& t_viewport);//reset the display
	void display(sf::RenderWindow& t_window);//reneder all game elements
	void displayHUD(sf::RenderWindow& t_window,sf::View& t_fixedWindow);//render all HUD elements
	void handleCollisions();//work out all collisions between any hitboxes
	void menuInteractions();//handle all menu interactions

	static const int MAX_PLAYERS = 4;//maximum players in a game

	Player player[MAX_PLAYERS];//create as many instances of player as is needed
	TileGrid worldTiles;//create an instance of the world tiles

	sf::Time timePerFrame;
	sf::Time timeSinceLastUpdate;
	sf::Time timeSinceLastFixedUpdate;
	sf::Clock clock;

	sf::RectangleShape hudBacking;//a temporary square to hold basic UI
	sf::Font font;//default font
	sf::Text playerTurnDisplay;//text to shows whos turn it is

	int whosTurn = 1;//used to keep track of which player currently gets to play
};