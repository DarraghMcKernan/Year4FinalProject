#pragma once
#include "globals.h"

class Tile
{
public:
	void init(sf::Vector2f t_position, int t_cellNum);
	void render(sf::RenderWindow& t_window);
	void setTarget(bool t_active);
	void setType(int t_type);//0 default, 1 wall
	int getType();//0 default, 1 wall
	bool tileSetAsTarget = false;
	void clearTile();
	void setHighlight(bool t_valid);

	sf::RectangleShape getTileShape();
private:
	int tileNumber = 0;
	sf::RectangleShape tileShape;
	int tileType = 0;
};