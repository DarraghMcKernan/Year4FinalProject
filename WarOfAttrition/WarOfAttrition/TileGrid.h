#pragma once
#include "WorldTile.h"

class TileGrid
{
public:
	void init();
	void update(sf::Time& t_deltaTime);
	void hightlightTiles(bool t_valid);
	void render(sf::RenderWindow& t_window);
	void findTargetedTile();
	void deactiveateTile();
	int currentPlayerTarget(int t_turnNum);
	sf::Vector2f mousePosViewport();
	sf::Vector2f tileHoveredOverPos();
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
private:
	std::vector<Tile> tiles;
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
};