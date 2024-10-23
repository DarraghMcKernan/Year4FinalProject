#pragma once
#include "WorldTile.h"

class TileGrid
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);

private:
	std::vector<Tile> tiles;
	sf::Vector2i mousePos;

	int clickCooldown = 0;
};