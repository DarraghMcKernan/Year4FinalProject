#pragma once
#include "globals.h"
#include "Squad.h"

class Player
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void setTargetPosition(int t_cellNum);

	bool targetNeeded = false;
	bool arrivedAtTarget = false;

private:
	std::vector<Squad> playersSquads;
	sf::CircleShape tempPlayer;
	sf::Vector2f mousePos;
	sf::Vector2f targetPosition;
	sf::Text strengthValueText;
	sf::Font font;

	int playerSquadsCount = 4;
	int strength = 100;
	int activeTargetTimer = 0;
};