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
	for (int index = 0; index < MAX_FORMATION_SIZE; index++)
	{
		if (formationPositions[index] == -1)//if the position has not yet been claimed
		{
			formationPositions[index] = index;
			return index;
		}
	}

	return -1;
}

sf::Vector2f Formation::getFormationPosition(int t_posInFormation)
{
	float radians = leaderCopy.getRotation() * (3.14159f / 180.0f);

	sf::Vector2f offset;
	if (t_posInFormation == 0)
	{
		return leaderPosition;
	}
	if (t_posInFormation == 1)
	{
		offset = sf::Vector2f(standardOffset.x * formationXSpread, -standardOffset.y * formationYSpread);
	}
	else if (t_posInFormation == 2)
	{
		offset = sf::Vector2f(-standardOffset.x * formationXSpread, -standardOffset.y * formationYSpread);
	}
	else if (t_posInFormation == 3)
	{
		offset = sf::Vector2f((standardOffset.x * formationXSpread)*2, (-standardOffset.y * formationYSpread) * 2);
	}
	else if (t_posInFormation == 4)
	{
		offset = sf::Vector2f(standardOffset.x * formationXSpread, -standardOffset.y * formationYSpread);
	}

	sf::Vector2f tempPos = offset;

	float cosTheta = std::cos(radians);
	float sinTheta = std::sin(radians);

	sf::Vector2f actualFormationPoint = sf::Vector2f(tempPos.x * cosTheta - tempPos.y * sinTheta, tempPos.x * sinTheta + tempPos.y * cosTheta);

	actualFormationPoint += leaderPosition;

	PositionNormaliser normaliser;

	actualFormationPoint = normaliser.normalizeToTileCenter(actualFormationPoint);

	return actualFormationPoint;
}



void Formation::setLeaderInfo(sf::Sprite t_leaderSprite)
{
	leaderCopy = t_leaderSprite;
	leaderPosition = t_leaderSprite.getPosition();
}

void Formation::generatePath()
{

}
