#pragma once
#include "globals.h"

class Tile
{
public:
	void init(sf::Vector2f t_position, int t_cellNum);
	void render(sf::RenderWindow& t_window);
	void setTarget(bool t_active);
	bool tileSetAsTarget = false;
private:
	int cellNumber = 0;
	sf::RectangleShape cellShape;

};