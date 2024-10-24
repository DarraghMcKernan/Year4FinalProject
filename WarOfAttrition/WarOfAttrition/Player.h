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
	bool playerActive = false;
	bool arrivedAtTarget = false;

private:
	sf::CircleShape tempPlayer;
	sf::Vector2f mousePos;
	sf::Vector2f targetPosition;
	sf::Text strengthValueText;
	sf::Font font;

	int strength = 100;
	int activeTimer = 0;
};