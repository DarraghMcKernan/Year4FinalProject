#pragma once
#include "globals.h"

class Enemy
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	int getStrength();
	sf::CircleShape getEnemyShape();
	void setTargetPos(int t_cellNum);
	void takeDamage(int t_damage);

private:
	sf::CircleShape enemyShape;
	sf::Text strengthText;
	sf::Font font;
	sf::Vector2f targetPosition;

	int strength = 75;
};