#pragma once
#include "WorldTile.h"

class TileGrid
{
public:
	void init();
	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void findTargetedTile();
	void deactiveateTile();
	int currentPlayerTarget();
	sf::Vector2f tileHoveredOver();
	void resetTiles();

	bool positionUpdated = false;
	bool targetMoving = false;
	int tilesSelected[MAX_MOVES_PER_TURN];
private:
	std::vector<Tile> tiles;
	sf::Vector2i mousePos;
	sf::Vector2f mousePosViewPort;

	int currentTile = 0;
	int clickCooldown = 0;
};