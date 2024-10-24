#pragma once
#include "globals.h"

class Player
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void takeDamage(int t_damage);
	void setPosition(int t_cellNum);

private:
	sf::CircleShape tempPlayer;

	sf::Text strengthValueText;
	sf::Font font;

	int strength = 100;
};