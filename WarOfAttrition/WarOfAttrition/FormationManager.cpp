#include "FormationManager.h"

void Formation::update(sf::Time t_deltaTime)
{

}

void Formation::setLeaderPosAndTarget(sf::Vector2f t_leaderPos, sf::Vector2f t_targetPos)
{
	leaderPosition = t_leaderPos;
	targetPosition = t_targetPos;
}

sf::Vector2f Formation::getCurrentLeaderPos()
{


	return leaderPosition;
}

int Formation::getPositionInFormation()
{


	return 0;
}

sf::Vector2f Formation::getFormationPosition(int t_posInFormation)
{


	return sf::Vector2f();
}

void Formation::generatePath()
{

}
