#pragma once
#include "globals.h"

class Squad 
{
public:
	void init(int t_squadStrength,sf::Vector2f t_startingPos,int t_teamNum);
	void update();
	void render(sf::RenderWindow& t_window);
	void unlockMovement(bool t_allowed);
	sf::CircleShape getTroopContainter();
	void setTargetPosition(sf::Vector2f t_targetPos);
	bool movingAllowed();
	bool targetReached = false;
	void resetColour();
	int getStrength();
	void setStrength(int t_strength);
private:
	sf::CircleShape troopContainer;
	sf::Vector2f targetPosition;

	bool movementAllowed = false;
	
	int teamNum=0;
	int squadStrength = 100;
	sf::Text debugStrengthDisplay;
	sf::Font font;
};