#pragma once
#include "WorldTile.h"

class TileGrid
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void findTargetedTile();
	void deactiveateTile();
	int currentPlayerTarget();

	bool positionUpdated = false;
	bool targetMoving = false;

private:
	std::vector<Tile> tiles;
	sf::Vector2i mousePos;
	sf::Vector2f mousePosViewPort;

	int currentTile = 0;
	int clickCooldown = 0;
};