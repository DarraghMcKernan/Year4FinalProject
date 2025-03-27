#pragma once
#include "WorldTile.h"
#include "globals.h"
#include <queue>
#include <fstream>
class TileGrid
{
public:
	void init();
	void update(sf::Time& t_deltaTime);
	void hightlightTiles(bool t_valid);
	void render(sf::RenderWindow& t_window);
	void findTargetedTile();
	void deactiveateTile();
	void deactiveateAllTiles();
	int currentPlayerTarget(int t_turnNum);
	sf::Vector2f mousePosViewport();
	sf::Vector2f tileHoveredOverPos();
	sf::Vector2f normaliseToTilePosition(sf::Vector2f t_position);
	int tileHoveredOverNum();
	void resetTiles();
	bool checkIfWall(int t_tileNum);
	void updateTileType(int t_type);

	void setupTextures();
	void updateTileTexture(int t_tileNum,int t_depth);

	int checkSurroundingTiles(int t_tileNum);

	bool positionUpdated = false;
	bool targetMoving = false;
	int tilesSelected[MAX_MOVES_PER_TURN];
	//std::vector<int> allInvalidTiles;
	std::vector<int> getPathToTarget(sf::Vector2f StartPos, sf::Vector2f targetPos);
	std::vector<int> getInvalidTiles();
private:
	std::vector<Tile> tiles;
	std::vector<int> allInvalidTiles;
	std::vector<sf::Sprite> worldTileTemp;
	std::vector<int> tileSetAsWalls;
	std::vector<int> tilesToBeChecked;

	sf::Vector2i mousePos;
	sf::Vector2f mousePosViewPort;

	int currentTile = 0;
	int clickCooldown = 0;
	int lastCellHovered = 0;

	sf::Texture defaultTileTexture;

	sf::Texture waterN;
	sf::Texture waterNW;
	sf::Texture waterW;
	sf::Texture waterSW;
	sf::Texture waterS;
	sf::Texture waterSE;
	sf::Texture waterE;
	sf::Texture waterNE;

	sf::Texture waterNA;//north nothing on sides
	sf::Texture waterWA;
	sf::Texture waterSA;
	sf::Texture waterEA;

	sf::Texture waterC;//surrounded by water 9 tiles
	sf::Texture waterA;//by itself
	sf::Texture waterCI;//Surrounded N E S W only

	sf::Texture waterNWI;//northwest interior
	sf::Texture waterNEI;
	sf::Texture waterSWI;
	sf::Texture waterSEI;

	sf::Texture waterSEINW;//diagonal corners
	sf::Texture waterSWINE;

	sf::Texture waterSEF;//1 corner filled
	sf::Texture waterSWF;
	sf::Texture waterNEF;
	sf::Texture waterNWF;

	sf::Texture waterNEC;//NE turn corner cutout 
	sf::Texture waterNWC;
	sf::Texture waterSWC;
	sf::Texture waterSEC;
};