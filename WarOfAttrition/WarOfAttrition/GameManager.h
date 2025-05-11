#pragma once
#include "Player.h"
#include "TileGrid.h"
#include "UI.h"


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
	void checkGameOver();
	void addUnit(int t_playerNum);
	void removeUnit(int t_playerNum);
	void updateUnitDataDisplay();

	static const int MAX_PLAYERS = 2;//maximum players in a game

	Player player[MAX_PLAYERS];//create as many instances of player as is needed
	TileGrid worldTiles;//create an instance of the world tiles
	SquadData squadData;//stores the data of the most recent squad that was hovered over
	UI gameUI;

	sf::Time timePerFrame;
	sf::Time timeSinceLastUpdate;
	sf::Time timeSinceLastFixedUpdate;
	sf::Clock clock;

	sf::CircleShape unitPlacementHighlight;//a circular highlight to show where your placed unit will go

	sf::Vector2i mousePos;
	sf::Vector2f mousePosFloat;
	

	int whosTurn = 1;//used to keep track of which player currently gets to play
	int currentTileSelected = 0;
	int clickTimer = 0;
	int winner = 0;
	int editingTerrainType = 0;//0 = normal ground, 1 = wall, 2 = water
	int unitTypeToCreate = 0;

	bool openCreateUnitMenu = false;//toggles the create unit menu
	bool openCreateTowerMenu = false;//toggles the create unit menu
	bool createUnitActive = false;//allows a unit to be created after a type is selected
	bool createTowerActive = false;//allows a unit to be created after a type is selected
	bool menuOpen = true;
	bool gameOver = false;
	bool worldEditingEnabled = false;
	bool allowSquadDataDisplay = false;
	bool worldTilesModified = true;
	bool worldTilesDataUpdated = false;
	bool upgradeUnitMenuOpen = false;
	bool customUnitModified = false;

	float currentZoom = 1.0f;
	float minZoom = 0.75f;
	float maxZoom = 1.25f;
};