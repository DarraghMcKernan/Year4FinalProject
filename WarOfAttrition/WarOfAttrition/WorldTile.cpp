#include "WorldTile.h"

void Tile::init(sf::Vector2f t_position, int t_cellNum)
{
	tileNumber = t_cellNum;

	tileShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	tileShape.setOrigin(sf::Vector2f(TILE_SIZE/2, TILE_SIZE/2));
	//cellShape.setFillColor(sf::Color(0, (cellNumber % TILE_COLUMNS) * 5, (cellNumber % TILE_COLUMNS) * 5, 200));
	tileShape.setFillColor(sf::Color(255, 255, 255, 0));
	tileShape.setOutlineColor(sf::Color::White);
	tileShape.setOutlineThickness(1.5f);
	tileShape.setPosition({ t_position.x + (TILE_SIZE / 2),t_position.y + (TILE_SIZE / 2) });
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(tileShape);
}

void Tile::setTarget(bool t_active)
{
	if (t_active == true)
	{
		tileShape.setFillColor(sf::Color(0, 255, 0, 50));//highlight target green
	}
	else {
		//cellShape.setFillColor(sf::Color(0, (cellNumber % TILE_COLUMNS) * 5, (cellNumber % TILE_COLUMNS) * 5, 200));
		tileShape.setFillColor(sf::Color(255, 255, 255, 0));
	}

	if (tileSetAsTarget == true)
	{
		tileShape.setFillColor(sf::Color(255, 0, 0, 50));
	}
}

void Tile::setType(int t_type)
{
	tileType = t_type;
	if (t_type == 0)//default ground
	{
		tileShape.setFillColor(sf::Color(255, 255, 255, 0));
	}
	else if (t_type == 1)//wall
	{
		tileShape.setFillColor(sf::Color(0, 0, 0));
	}
	else if (t_type == 2)//water
	{
		tileShape.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

int Tile::getType()
{
	return tileType;
}

void Tile::clearTile()
{
	if (tileType == 0 && tileSetAsTarget == false)
	{
		tileShape.setFillColor(sf::Color(255, 255, 255, 0));
	}
}

void Tile::setHighlight(bool t_valid)
{
	if (tileType == 0 && tileSetAsTarget == false && t_valid == true)
	{
		tileShape.setFillColor(sf::Color(150, 150, 255, 50));
	}
	if (tileType == 0 && tileSetAsTarget == false && t_valid == false)
	{
		tileShape.setFillColor(sf::Color(255, 150, 150, 50));
	}
}

sf::RectangleShape Tile::getTileShape()
{
	return tileShape;
}