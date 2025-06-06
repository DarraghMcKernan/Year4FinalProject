#include "FormationManager.h"

void Formation::update(sf::Time t_deltaTime)
{
	if (formationMovingActive == false|| pathToTarget.size() == 0)
	{
		return;
	}

	if (placeOnPath == 0)
	{
		placeOnPath = 1;

		nextPlaceOnPath = { (pathToTarget[placeOnPath] % TILE_COLUMNS) * TILE_SIZE, (pathToTarget[placeOnPath] / TILE_COLUMNS) * TILE_SIZE};//the tile that the player wants to move to
		nextPlaceOnPath = { nextPlaceOnPath.x + (TILE_SIZE / 2) , nextPlaceOnPath.y + (TILE_SIZE / 2) };//center the target on a tile
	}

	sf::Vector2f vectorToTarget = nextPlaceOnPath - formationFront;
	sf::Vector2f vectorToEnd = targetPosition - formationFront;
	float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
	vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

	float distanceToTarget = sqrt((vectorToEnd.x * vectorToEnd.x) + (vectorToEnd.y * vectorToEnd.y));

	if (distanceToTarget <= 2.1)
	{
		formationFront = targetPosition;
		formationMovingActive = false;
		leaderTargetReached = true;

		std::cout << "leader reached target\n";

		return;
	}

	if (turning == true)
	{
		float desiredAngle = std::atan2(vectorToTarget.y, vectorToTarget.x) * (180.0f / 3.14159f); 
		desiredAngle -= 90;
		if (desiredAngle < 0.0f) 
		{
			desiredAngle += 360.0f;
		}

		float angleDifference = desiredAngle - leaderRotation;

		if (rotateRight == true)
		{
			leaderRotation += rotationSpeed * t_deltaTime.asSeconds();
		}

		if (angleDifference > 180.0f)
		{
			angleDifference -= 360.0f;
		}
		else if (angleDifference < -180.0f)
		{
			angleDifference += 360.0f;
		}

		if (angleDifference < 0)
		{
			rotateRight = false;
		}
		else rotateRight = true;

		if (rotateRight)
		{
			leaderRotation += rotationSpeed * t_deltaTime.asSeconds();
		}
		else leaderRotation -= rotationSpeed * t_deltaTime.asSeconds();

		int checkLeaderRotation = static_cast<int>(leaderRotation);
		int checkDesiredRotation = static_cast<int>(desiredAngle);

		if (checkLeaderRotation == checkDesiredRotation)
		{
			turning = false;
			leaderRotation = checkDesiredRotation;
		}
	}

	if (distance > 2.1 && turning == false)
	{
		float speed = formationMoveSpeed * t_deltaTime.asSeconds();
		formationFront = sf::Vector2f(formationFront.x + (vectorToTarget.x * speed), formationFront.y + (vectorToTarget.y * speed));
	}
	if (distance <= 2.1)
	{
		placeOnPath++;
		nextPlaceOnPath = { (pathToTarget[placeOnPath] % TILE_COLUMNS) * TILE_SIZE, (pathToTarget[placeOnPath] / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
		nextPlaceOnPath = { nextPlaceOnPath.x + (TILE_SIZE / 2) , nextPlaceOnPath.y + (TILE_SIZE / 2) };//center the target on a tile
		std::cout << "path point reached, next cell selected\n";
		turning = true;
	}
}

void Formation::setLeaderPosAndTarget(sf::Vector2f t_leaderPos, sf::Vector2f t_targetPos)
{
	startPosition = t_leaderPos;
	formationFront = t_leaderPos;
	leaderPosition = t_leaderPos;
	targetPosition = t_targetPos;

	formationCircleDebugLeader.setRadius(5);
	formationCircleDebugLeader.setOrigin(5, 5);
	formationCircleDebugLeader.setFillColor(sf::Color::Red);
	formationCircleDebugLeader.setPosition(t_leaderPos);

	formationCircleDebug1.setRadius(5);
	formationCircleDebug1.setOrigin(5, 5);
	formationCircleDebug1.setFillColor(sf::Color::Yellow);

	formationCircleDebug2.setRadius(5);
	formationCircleDebug2.setOrigin(5, 5);
	formationCircleDebug2.setFillColor(sf::Color::Yellow);

	formationCircleDebug3.setRadius(5);
	formationCircleDebug3.setOrigin(5, 5);
	formationCircleDebug3.setFillColor(sf::Color::Yellow);
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
	int pos = 0;
	PositionNormaliser normaliser;

	sf::Vector2f offset = sf::Vector2f(0,0);
	if (t_posInFormation == 0)
	{
		formationCircleDebugLeader.setPosition(formationFront);
		return normaliser.normalizeToTileCenter(formationFront);
	}
	else if (t_posInFormation == 1)
	{
		pos = 1;
		offset = sf::Vector2f(standardOffset.x * formationXSpread, -standardOffset.y * formationYSpread);
	}
	else if (t_posInFormation == 2)
	{
		pos = 2;
		offset = sf::Vector2f(-standardOffset.x * formationXSpread, -standardOffset.y * formationYSpread);
	}
	else if (t_posInFormation == 3)
	{
		pos = 3;
		offset = sf::Vector2f((standardOffset.x * formationXSpread)*2, (-standardOffset.y * formationYSpread) * 2);
	}
	else if (t_posInFormation == 4)
	{
		offset = sf::Vector2f(standardOffset.x * formationXSpread, -standardOffset.y * formationYSpread);
	}

	float cosTheta = std::cos(radians);
	float sinTheta = std::sin(radians);

	sf::Vector2f actualFormationPoint = sf::Vector2f(offset.x * cosTheta - offset.y * sinTheta, offset.x * sinTheta + offset.y * cosTheta);

	actualFormationPoint += formationFront;

	if (pos == 1)
	{
		formationCircleDebug1.setPosition(actualFormationPoint);
	}
	else if (pos == 2)
	{
		formationCircleDebug2.setPosition(actualFormationPoint);
	}
	else if (pos == 3)
	{
		formationCircleDebug3.setPosition(actualFormationPoint);
	}

	actualFormationPoint = normaliser.normalizeToTileCenter(actualFormationPoint);

	return actualFormationPoint;
}



void Formation::setLeaderInfo(sf::Sprite t_leaderSprite,float t_leaderSpeed)
{
	formationMoveSpeed = t_leaderSpeed * 0.5f;//50% of leaders speed so it stops on cell for a bit
	leaderCopy = t_leaderSprite;
	leaderPosition = t_leaderSprite.getPosition();
	leaderRotation = t_leaderSprite.getRotation();
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

std::vector<sf::CircleShape> Formation::getDebugCirclesToDraw()
{
	std::vector<sf::CircleShape> circles;

	circles.push_back(formationCircleDebugLeader);
	circles.push_back(formationCircleDebug1);
	circles.push_back(formationCircleDebug2);
	circles.push_back(formationCircleDebug3);

	return circles;
}

void Formation::updateLeaderCopy(sf::Sprite t_leaderSprite)
{
	leaderCopy = t_leaderSprite;
	leaderRotation = t_leaderSprite.getRotation();
	turning = true;
}

void Formation::clearData()
{
	for (int i = 0; i < MAX_FORMATION_SIZE; ++i)
	{
		formationPositions[i] = -1;
	}

	leaderTargetReached = false;
	formationMovingActive = false;
	leaderInfoSet = false;
	turning = true;
	rotateRight = true;
	goalReached = false;

	placeOnPath = 0;
	pathToTarget.clear();
	nextPlaceOnPath = { 0.0f, 0.0f };

	leaderPosition = { 0.0f, 0.0f };
	formationFront = { 0.0f, 0.0f };
	targetPosition = { 0.0f, 0.0f };
	startPosition = { 0.0f, 0.0f };

	formationCircleDebugLeader.setPosition(0.f, 0.f);
	formationCircleDebug1.setPosition(0.f, 0.f);
	formationCircleDebug2.setPosition(0.f, 0.f);
	formationCircleDebug3.setPosition(0.f, 0.f);

	leaderRotation = 0.0f;
	leaderCopy = sf::Sprite();
}

float Formation::updatedLeaderRotation()
{
	return leaderRotation;
}

void Formation::generatePath()
{

}
