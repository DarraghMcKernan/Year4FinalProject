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


private:
	void generatePath();
	sf::Vector2f leaderPosition = { 0,0 };
	sf::Vector2f targetPosition = { 0,0 };
	sf::Vector2f standardOffset = { 50,50 };
	float cappedRotationSpeed = 5.0f;
	float maxFormationSpeed = 5.0f;
	float formationXSpread = 1.0f;//used to modify the width and height of the formation to allow it to better navigate obstacles
	float formationYSpread = 1.0f;
	std::vector<int> pathToTarget;//the path that the formation will roughly follow
	int placeOnPath = 0;
	bool goalReached = false;

	int formationPositions[10];
};