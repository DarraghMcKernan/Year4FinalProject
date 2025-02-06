#pragma once
#include "globals.h"



class Squad 
{
public:
	void init(sf::Vector2f t_startingPos,int t_teamNum,int t_unitType);
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void unlockMovement(bool t_allowed);
	sf::RectangleShape getTroopContainter();
	void setTargetPosition(sf::Vector2f t_targetPos);
	bool movingAllowed();
	bool targetReached = false;
	void resetColour();
	int getStrength();
	void setStrength(int t_strength);
	void setHealth(int t_health);
	bool turnEnded = false;
	bool targetSet = false;
	int maxMoveDistance = 5;

	SquadData getSquadData();
	int getUnitType();
private:
	SquadData squadData;

	void setunitType();
	sf::RectangleShape troopContainer;
	sf::Vector2f targetPosition;

	sf::Sprite UnitSprite;
	sf::Sprite teamOutlineSprite;
	sf::Sprite unitSpriteExtras;

	sf::Sprite goldmineSprite;
	int goldmineCost = 750;
	int goldmineIncome = 100;
	int moveSpeed = 100;

	sf::Vector2f worldTileOffset = sf::Vector2f(23, 23);

	bool movementAllowed = false;
	bool extraSpriteNeeded = false;
	
	/*int moveSpeed = 100;
	int teamNum=0;
	int squadStrength = 100;
	int unitType = 0;*/
};