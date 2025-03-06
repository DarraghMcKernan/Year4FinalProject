#pragma once
#include "globals.h"

class Formation
{
public:
	void update(sf::Time t_deltaTime);
	void setLeaderPosAndTarget(sf::Vector2f t_leaderPos, sf::Vector2f t_targetPos);
	sf::Vector2f getCurrentLeaderPos();//will get the position the leader is currently at
	int getPositionInFormation();//will assign the smallest free number in the formation
	sf::Vector2f getFormationPosition(int t_posInFormation);//returns the position the unit should be going to
	void setLeaderInfo(sf::Sprite t_leaderSprite);
	bool leaderTargetReached = false;
	bool formationMovingActive = false;
private:
	void generatePath();
	sf::Vector2f leaderPosition = { 0,0 };
	sf::Vector2f formationFront = { 0,0 };
	sf::Vector2f targetPosition = { 0,0 };
	sf::Vector2f standardOffset = { 50,50 };
	sf::Sprite leaderCopy;
	float cappedRotationSpeed = 5.0f; 
	float maxFormationSpeed = 5.0f;
	float formationXSpread = 1.0f;//used to modify the width and height of the formation to allow it to better navigate obstacles
	float formationYSpread = 1.0f;
	float formationMoveSpeed = 20.0f;
	std::vector<int> pathToTarget;//the path that the formation will roughly follow
	int placeOnPath = 0;
	bool goalReached = false;
	

	const static int MAX_FORMATION_SIZE = 4;

	int formationPositions[MAX_FORMATION_SIZE]{-1,-1,-1,-1};//used to know which positions are occupied and by which unit
};