#include "TileGrid.h"

void TileGrid::init()
{
	Tile newTile;
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		tiles.push_back(newTile);
		tiles[index].init({ (index % TILE_COLUMNS) * TILE_SIZE,(index / TILE_COLUMNS) * TILE_SIZE } , index);
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
		tiles[currentTile].setTarget(false);//unset previous target

		int column = mousePosViewPort.x / TILE_SIZE;
		int row = mousePosViewPort.y / TILE_SIZE;

		int temp = row * TILE_COLUMNS + column;

		if (temp > 0 || temp < (TILE_ROWS * TILE_COLUMNS))
		{
			currentTile = temp;
		}
		tiles[currentTile].setTarget(true);

		clickCooldown = 10;
	}

}

void TileGrid::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);
	mousePosViewPort = t_window.mapPixelToCoords(mousePos);//get coords relative to the viewport

	for (int index = 0; index < TILE_ROWS * TILE_COLUMNS; index++)
	{
		tiles[index].render(t_window);
	}
}

int TileGrid::currentPlayerTarget()
{
	return currentTile;
}
