#include "TileGrid.h"

void TileGrid::init()
{
	Tile newTile;
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		tiles.push_back(newTile);//add new tile to list
		tiles[index].init({ (index % TILE_COLUMNS) * TILE_SIZE,(index / TILE_COLUMNS) * TILE_SIZE } , index);//place new tile in position relative to its number
	}
}

void TileGrid::update()
{
	
}

void TileGrid::findTargetedTile()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0 && targetMoving == false)
	{
		targetMoving = true;
		tiles[currentTile].setTarget(false);//unset previous target

		int column = mousePosViewPort.x / TILE_SIZE;
		int row = mousePosViewPort.y / TILE_SIZE;

		int temp = row * TILE_COLUMNS + column;

		if (temp > 0 || temp < (TILE_ROWS * TILE_COLUMNS))//ensure new tile is within the list
		{
			currentTile = temp;
		}
		tiles[currentTile].setTarget(true);//update target

		positionUpdated = true;//allow new position to be given to player

		clickCooldown = 10;
	}
}

void TileGrid::deactiveateTile()
{
	targetMoving = false;
	tiles[currentTile].setTarget(false);//unset previous target
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
	//std::cout << "mouse X: " + std::to_string(mousePosViewPort.x) + "    mouse Y:" + std::to_string(mousePosViewPort.y) + "\n";
	return currentTile;
}
