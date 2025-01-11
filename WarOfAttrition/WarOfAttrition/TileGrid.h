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

	bool positionUpdated = false;
	bool targetMoving = false;
	int tilesSelected[MAX_MOVES_PER_TURN];
private:
	std::vector<Tile> tiles;
	std::vector<int> tileSetAsWalls;
	sf::Vector2i mousePos;
	sf::Vector2f mousePosViewPort;

	int currentTile = 0;
	int clickCooldown = 0;
	int lastCellHovered = 0;
};