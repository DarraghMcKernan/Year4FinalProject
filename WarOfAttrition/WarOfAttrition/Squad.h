#pragma once
#include "globals.h"

class Squad 
{
public:
	void init(int t_squadStrength,sf::Vector2f t_startingPos);
	void update();
	void render(sf::RenderWindow& t_window);
	void unlockMovement(bool t_allowed);
	sf::CircleShape getTroopContainter();
	void setTargetPosition(sf::Vector2f t_targetPos);
	bool movingAllowed();
	bool targetReached = false;
private:
	sf::CircleShape troopContainer;
	sf::Vector2f targetPosition;

	bool movementAllowed = false;
	
	int squadStrength = 100;
	sf::Text debugStrengthDisplay;
	sf::Font font;
};