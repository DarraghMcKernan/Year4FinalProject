#include "FormationManager.h"

void Formation::update(sf::Time t_deltaTime)
{
	sf::Vector2f vectorToTarget = targetPosition - formationFront;
	float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
	vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

	//std::cout << "Leader pos: " << leaderPosition.x << " " << leaderPosition.y << "\n";
	//std::cout << "Target pos: " << targetPosition.x << " " << targetPosition.y << "\n\n";
	//std::cout << "formation front pos: " << formationFront.x << " " << formationFront.y << "\n";

	//std::cout << distance << "\n"; 

	if (distance > 2.1)
	{
		float speed = formationMoveSpeed * t_deltaTime.asSeconds();
		formationFront = sf::Vector2f(formationFront.x + (vectorToTarget.x * speed), formationFront.y + (vectorToTarget.y * speed));
	}
	
	if (distance <= 2.1)
	{
		formationFront = targetPosition;
		formationMovingActive = false;
		leaderTargetReached = true;
	}
}

void Formation::setLeaderPosAndTarget(sf::Vector2f t_leaderPos, sf::Vector2f t_targetPos)
{
	startPosition = t_leaderPos;
	formationFront = t_leaderPos;
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

	if (formationFront == sf::Vector2f(0, 0))
	{
		return sf::Vector2f(0, 0);
	}

	PositionNormaliser normaliser;

	sf::Vector2f offset = sf::Vector2f(0,0);
	if (t_posInFormation == 0)
	{
		return normaliser.normalizeToTileCenter(formationFront);
	}
	else if (t_posInFormation == 1)
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

	actualFormationPoint += formationFront;

	actualFormationPoint = normaliser.normalizeToTileCenter(actualFormationPoint);

	return actualFormationPoint;
}



void Formation::setLeaderInfo(sf::Sprite t_leaderSprite)
{
	leaderCopy = t_leaderSprite;
	leaderPosition = t_leaderSprite.getPosition();
}

sf::Vector2f Formation::getTargetPosition()
{
	return targetPosition;
}

sf::Vector2f Formation::getStartPosition()
{
	return startPosition;
}

void Formation::setFoundPath(std::vector<int> t_path)
{
	pathToTarget = t_path;
}

void Formation::generatePath()
{

}
