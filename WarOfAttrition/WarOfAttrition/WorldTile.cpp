#include "WorldTile.h"

void Tile::init(sf::Vector2f t_position, int t_cellNum)
{
	cellNumber = t_cellNum;

	cellShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	cellShape.setFillColor(sf::Color(0, (cellNumber % TILE_COLUMNS) * 5, (cellNumber % TILE_COLUMNS) * 5, 200));
	cellShape.setOutlineColor(sf::Color::White);
	cellShape.setOutlineThickness(0.5f);
	cellShape.setPosition(t_position);
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(cellShape);
}

void Tile::setTarget(bool t_active)
{
	if (t_active == true)
	{
		cellShape.setFillColor(sf::Color(0, 255, 0, 100));//highlight target green
	}
	else {
		cellShape.setFillColor(sf::Color(0, (cellNumber % TILE_COLUMNS) * 5, (cellNumber % TILE_COLUMNS) * 5, 200));
	}
}
