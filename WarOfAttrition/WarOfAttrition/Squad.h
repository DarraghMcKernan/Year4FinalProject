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
	void setPosition(sf::Vector2f t_debugPosition);
	void moveToFormationPosition(sf::Vector2f t_formationPosition, sf::Time& t_deltaTime);
	void placeOnRecentCell();
	bool movingAllowed();
	bool targetReached = true;
	void resetColour();
	int getStrength();
	void setStrength(int t_strength);
	void setHealth(int t_health);
	bool turnEnded = false;
	bool targetSet = false;
	int maxMoveDistance = 10;

	void setFormationNum(int t_formationPosition);
	int getFormationNum();

	SquadData getSquadData();
	int getUnitType();
	sf::Sprite getSprite();
	void checkIfTargetReached();

	bool formationActive = false;
	bool formationLeader = false;
	bool formationLeaderReachedGoal = false;
	bool formationFrontReachedGoal = false;
	bool attacker = false;
	bool needToMove = false;

	std::vector<int> pathToTarget;
	int positionOnPath = 0;
	sf::Vector2f nextPlaceOnPath;
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
	int posInFormation = -1;
	int mostRecentCell = 0;
	int currentCell = 0;

	sf::Vector2f worldTileOffset = sf::Vector2f(TILE_SIZE/2, TILE_SIZE/2);

	bool movementAllowed = false;
	bool extraSpriteNeeded = false;
	
	/*int moveSpeed = 100;
	int teamNum=0;
	int squadStrength = 100;
	int unitType = 0;*/
};