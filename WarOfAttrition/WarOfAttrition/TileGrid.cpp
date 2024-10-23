#include "TileGrid.h"

void TileGrid::init()
{
	Tile newTile;
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		tiles.push_back(newTile);
		tiles[index].init({ (index % TILE_ROWS) * TILE_SIZE,(index / TILE_ROWS) * TILE_SIZE } , index);
	}
}

void TileGrid::update()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0)
	{

	}

}

void TileGrid::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);

	for (int index = 0; index < TILE_ROWS * TILE_COLUMNS; index++)
	{
		tiles[index].render(t_window);
	}
}