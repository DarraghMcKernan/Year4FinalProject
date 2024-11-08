#pragma once
#include "globals.h"
#include "Squad.h"

class Player
{
public:
	void init(int t_teamNum);
	void update();
	void render(sf::RenderWindow& t_window);
	void setTargetPosition(int t_cellNum);//assign the cell set in worldTile to the squad currently being assigned
	int collisionChecker(sf::CircleShape targetToCheck,int t_strength);//return damage dealt if any

	bool targetNeeded = false;
	bool arrivedAtTarget = false;

private:
	std::vector<Squad> playersSquads;
	std::vector<sf::Text> playersSquadsStrenghts;
	sf::CircleShape tempPlayer;
	sf::Vector2f mousePos;
	sf::Vector2f targetPosition;
	//sf::Text strengthValueText;
	sf::Font font;

	int playerSquadsCount = 4;
	int strength = 100;
	int activeTargetTimer = 0;
};