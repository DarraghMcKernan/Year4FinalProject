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
	void setPlayerTurnColour();//set the text to the correct colour

	static const int MAX_PLAYERS = 4;//maximum players in a game

	Player player[MAX_PLAYERS];//create as many instances of player as is needed
	TileGrid worldTiles;//create an instance of the world tiles

	sf::Time timePerFrame;
	sf::Time timeSinceLastUpdate;
	sf::Time timeSinceLastFixedUpdate;
	sf::Clock clock;

	sf::RectangleShape hudBacking;//a temporary square to hold basic UI
	sf::RectangleShape endTurnButton;//button to allow player to end their turn
	sf::RectangleShape openUnitMenuButton;//button that brings up the menu to create units
	sf::RectangleShape unitMenuBacking;//just a background ui for the buttons to create units
	sf::RectangleShape createDefaultUnit;//placeholder button to create the default unit type
	sf::RectangleShape menuBackground;
	sf::RectangleShape menuStartButton;

	sf::CircleShape unitPlacementHighlight;//a circular highlight to show where your placed unit will go

	sf::Vector2i mousePos;
	sf::Font font;//default font
	sf::Text playerTurnDisplay;//text to shows whos turn it is
	sf::Text endTurnText;//text to shows whos turn it is
	sf::Text createUnitText;//text to shows whos turn it is
	sf::Text menuStartButtonText;
	sf::Text framerateText;

	int whosTurn = 1;//used to keep track of which player currently gets to play
	int currentTileSelected = 0;
	int clickTimer = 0;

	bool openCreateUnitMenu = false;//toggles the create unit menu
	bool createUnitActive = false;//allows a unit to be created after a type is selected
	bool menuOpen = true;
};