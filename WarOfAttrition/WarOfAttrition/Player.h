#pragma once
#include "globals.h"

class Player
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void takeDamage(int t_damage);
	void setTargetPosition(int t_cellNum);
	int getStrength();
	sf::CircleShape getPlayerShape();

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