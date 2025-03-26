#include "Squad.h"

void Squad::init(sf::Vector2f t_startingPos, int t_teamNum, int t_unitType)
{
	if (t_unitType == 0)
	{
		squadData.health = 250;
		squadData.squadStrength = 200;
		moveSpeed = 80;
	}
	if (t_unitType == 1)
	{
		squadData.health = 50;
		squadData.squadStrength = 50;
		moveSpeed = 100;
	}
	if (t_unitType == 2)
	{
		squadData.health = 300;
		squadData.squadStrength = 300;
		moveSpeed = 65;
	}
	squadData.moveSpeed = moveSpeed;
	squadData.teamNum = t_teamNum;
	squadData.unitType = t_unitType;
	squadData.moveDistance = maxMoveDistance;

	resetColour();

	troopContainer.setSize(sf::Vector2f(TILE_SIZE - 5, TILE_SIZE - 5));
	//troopContainer.setRotation(45);//can be used to have collision checks in all 9 surrounding squares or the 4 immediate squares

	//troopContainer.setSize(sf::Vector2f(TILE_SIZE + 15, TILE_SIZE + 15));// used to expand the squad to allow for collision checks of surrounding cells
	//troopContainer.setRotation(45);//can be used to have collision checks in all 9 surrounding squares or the 4 immediate squares

	//troopContainer.setOutlineColor(sf::Color::Black);
	//troopContainer.setOutlineThickness(1.5);
	troopContainer.setOrigin(troopContainer.getSize().x / 2, troopContainer.getSize().y / 2);
	troopContainer.setPosition(t_startingPos.x - (TILE_SIZE / 2), t_startingPos.y - (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = troopContainer.getPosition();

	movableCollider.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	movableCollider.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
	movableCollider.setFillColor(sf::Color::Magenta);

	setunitType();
}

void Squad::update(sf::Time t_deltaTime)
{
	if (movementAllowed == true)
	{
		sf::Vector2f troopPos = troopContainer.getPosition();
		if (troopPos != targetPosition && squadData.squadStrength > 0 && turnEnded == true)
		{
			if (pathToTarget.size() == 0)
			{
				return;
			}
			if (positionOnPath == 0)
			{
				positionOnPath = 1;

				nextPlaceOnPath = { (pathToTarget[positionOnPath] % TILE_COLUMNS) * TILE_SIZE, (pathToTarget[positionOnPath] / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
				nextPlaceOnPath = { nextPlaceOnPath.x + (TILE_SIZE / 2) , nextPlaceOnPath.y + (TILE_SIZE / 2) };//center the target on a tile
			}

			sf::Vector2f vectorToTarget = nextPlaceOnPath - troopContainer.getPosition();
			sf::Vector2f vectorToEnd = targetPosition - troopContainer.getPosition();

			float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
			vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

			float distanceToTarget = sqrt((vectorToEnd.x * vectorToEnd.x) + (vectorToEnd.y * vectorToEnd.y));

			if (distanceToTarget <= 2.1)//lock player to target once close enough
			{
				if (formationLeader == true)
				{
					formationLeaderReachedGoal = true;
					formationActive = false;
					targetReached = true;
					std::cout << "formation leader position reached" << std::endl;
				}

				troopContainer.setPosition(targetPosition);
				UnitSprite.setPosition(troopContainer.getPosition());
				float rotatiion = (atan2(vectorToTarget.y, vectorToTarget.x) * 180 / 3.14159265) - 90;
				UnitSprite.setRotation(rotatiion);
				if (extraSpriteNeeded == true)
				{
					unitSpriteExtras.setPosition(UnitSprite.getPosition());
					unitSpriteExtras.setRotation(rotatiion);
				}
				teamOutlineSprite.setPosition(troopContainer.getPosition());
				teamOutlineSprite.setRotation(rotatiion);
				movementAllowed = false;
				targetReached = true;
				resetColour();
				turnEnded = false;
				targetSet = false;
			}
			else
			{
				if (distance <= 2.1)
				{
					positionOnPath++;

					nextPlaceOnPath = { (pathToTarget[positionOnPath] % TILE_COLUMNS) * TILE_SIZE, (pathToTarget[positionOnPath] / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
					nextPlaceOnPath = { nextPlaceOnPath.x + (TILE_SIZE / 2) , nextPlaceOnPath.y + (TILE_SIZE / 2) };//center the target on a tile

					std::cout << "path point reached, next cell selected\n";
				}

				if (distance > 500)//artificially cap speed
				{
					distance = 500;
				}
				else if (distance < 200)//prevent player from slowing too much
				{
					distance = 200;
				}
				//vectorToTarget = vectorToTarget * (distance);//slow down as we get closer to the target

				int column = static_cast<int>(UnitSprite.getPosition().x / TILE_SIZE);
				int row = static_cast<int>(UnitSprite.getPosition().y / TILE_SIZE);

				if (currentCell != (row * TILE_COLUMNS) + column)
				{
					mostRecentCell = currentCell;
				}
				currentCell = (row * TILE_COLUMNS) + column;

				//std::cout << "current cell: " << currentCell << " most recent: " << mostRecentCell << "\n";

				troopContainer.move((vectorToTarget.x * t_deltaTime.asSeconds()) * (moveSpeed * SPEED_MULTIPLIER), (vectorToTarget.y * t_deltaTime.asSeconds()) * (moveSpeed * SPEED_MULTIPLIER));
				UnitSprite.setPosition(troopContainer.getPosition());

				UnitSprite.setRotation((atan2(vectorToTarget.y, vectorToTarget.x) * 180 / 3.14159265) - 90);

				if (extraSpriteNeeded == true)
				{
					unitSpriteExtras.setPosition(UnitSprite.getPosition());
					unitSpriteExtras.setRotation((atan2(vectorToTarget.y, vectorToTarget.x) * 180 / 3.14159265) - 90);
				}
				teamOutlineSprite.setPosition(troopContainer.getPosition());
				teamOutlineSprite.setRotation((atan2(vectorToTarget.y, vectorToTarget.x) * 180 / 3.14159265) - 90);
			}
		}
	}
}

void Squad::render(sf::RenderWindow& t_window)
{
	t_window.draw(troopContainer);
	t_window.draw(teamOutlineSprite);
	t_window.draw(UnitSprite);
	t_window.draw(movableCollider);
	if(extraSpriteNeeded == true)
	{
		t_window.draw(unitSpriteExtras);
	}
}

void Squad::unlockMovement(bool t_allowed)
{
	targetReached = false;
	attacker = true;
	movementAllowed = t_allowed;
	troopContainer.setFillColor(sf::Color(0, 255, 0, 150));
}

sf::RectangleShape Squad::getTroopContainter()
{
	return troopContainer;
}

void Squad::setTargetPosition(sf::Vector2f t_targetPos)
{
	targetSet = true;
	targetPosition = t_targetPos;
}

void Squad::setPosition(sf::Vector2f t_debugPosition)
{
	troopContainer.setPosition(t_debugPosition);
	UnitSprite.setPosition(troopContainer.getPosition());
	teamOutlineSprite.setPosition(troopContainer.getPosition());
	if (extraSpriteNeeded == true)
	{
		unitSpriteExtras.setPosition(troopContainer.getPosition());
	}
}

void Squad::moveToFormationPosition(sf::Vector2f t_formationPosition, sf::Time& t_deltaTime)
{
	switch (currentMovementState)
	{
	case MoveToFormationPoint:
		moveToFormation(t_formationPosition, t_deltaTime);
		break;
	case SteerAroundObstacle:
		steerAroundObstacle(t_formationPosition, t_deltaTime);
		break;
	case TakeLeadersPath:
		takeLeadersPath(t_formationPosition, t_deltaTime);
		break;
	case BreakFormation:
		breakFormation(t_formationPosition, t_deltaTime);
		break;
	}
}

void Squad::placeOnRecentCell()
{
	int row = mostRecentCell / TILE_COLUMNS;
	int column = mostRecentCell % TILE_COLUMNS;

	sf::Vector2f recentCellPos;

	recentCellPos.x = column * TILE_SIZE + TILE_SIZE / 2.0f;
	recentCellPos.y = row * TILE_SIZE + TILE_SIZE / 2.0f;

	troopContainer.setPosition(recentCellPos);
	UnitSprite.setPosition(recentCellPos);
	teamOutlineSprite.setPosition(recentCellPos);
	if (extraSpriteNeeded == true)
	{
		unitSpriteExtras.setPosition(recentCellPos);
	}
}

bool Squad::movingAllowed()
{
	return movementAllowed;
}

void Squad::resetColour()
{
	if (squadData.teamNum == 0)
	{
		troopContainer.setFillColor(sf::Color(0, 0, 255, 00));
		teamOutlineSprite.setColor(sf::Color(0, 0, 255, 200));
	}
	if (squadData.teamNum == 1)
	{
		troopContainer.setFillColor(sf::Color(255, 0, 0, 00));
		teamOutlineSprite.setColor(sf::Color(255, 0, 0, 200));
	}
	if (squadData.teamNum == 2)
	{
		troopContainer.setFillColor(sf::Color(0, 255, 255, 00));
		teamOutlineSprite.setColor(sf::Color(0, 255, 255, 200));
	}
	if (squadData.teamNum == 3)
	{
		troopContainer.setFillColor(sf::Color(255, 0, 255, 00));
		teamOutlineSprite.setColor(sf::Color(255, 0, 255, 200));
	}
}

int Squad::getStrength()
{
	return squadData.squadStrength;
}

void Squad::setStrength(int t_strength)
{
	squadData.squadStrength = t_strength;
}

void Squad::setHealth(int t_health)
{
	if (attacker == true && t_health > 0)
	{
		attacker = false;
		needToMove = true;
		std::cout << "moved attacker needs to return to previous cell\n";
	}
	squadData.health = t_health;
}

void Squad::setFormationNum(int t_formationPosition)
{
	posInFormation = t_formationPosition;
}

int Squad::getFormationNum()
{
	return posInFormation;
}

SquadData Squad::getSquadData()
{
	return squadData;
}

int Squad::getUnitType()
{
	return squadData.unitType;
}

sf::Sprite Squad::getSprite()
{
	return UnitSprite;
}

void Squad::checkIfTargetReached()
{
	sf::Vector2f vectorToTarget = targetPosition - troopContainer.getPosition();
	float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
	if (distance <= 2.1)
	{
		if (formationLeader == true)
		{
			formationLeaderReachedGoal = true;
			formationActive = false;
			targetReached = true;
		}
		else if (formationLeaderReachedGoal == true) {
			formationActive = false;
			targetReached = true;
		}
	}
}

void Squad::stopMovement()
{
	movementAllowed = false;
}

void Squad::passInvalidTiles(std::vector<int> t_invalidTiles)
{
	allInvalidTiles = t_invalidTiles;
}

void Squad::setunitType()
{
	if (squadData.unitType == 0)
	{
		if (!tankTexture.loadFromFile("ASSETS/ACS_Preview.png"))
		{
			std::cout << "error loading squad texture";
		}
		if (!tankOutlineTexture.loadFromFile("ASSETS/TankTeamOutline.png"))
		{
			std::cout << "error loading squad outline texture";
		}
		UnitSprite.setTexture(tankTexture);
		UnitSprite.setScale((UnitSprite.getScale().x / 128) * (TILE_SIZE), (UnitSprite.getScale().y / 128) * (TILE_SIZE));
		UnitSprite.setOrigin(96, 96);
		UnitSprite.setPosition(troopContainer.getPosition());

		teamOutlineSprite.setTexture(tankOutlineTexture);
		teamOutlineSprite.setScale((teamOutlineSprite.getScale().x / 128) * (TILE_SIZE)+0.03, (teamOutlineSprite.getScale().y / 128) * (TILE_SIZE)+0.03);
		teamOutlineSprite.setOrigin(96, 96);
		teamOutlineSprite.setPosition(troopContainer.getPosition());
	}
	else if (squadData.unitType == 1)
	{
		if (!infantryTexture.loadFromFile("ASSETS/Hero_Pistol.png"))
		{
			std::cout << "error loading squad texture";
		}
		if (!infantryOutlineTexture.loadFromFile("ASSETS/HeroPistolOutline.png"))
		{
			std::cout << "error loading squad outline texture";
		}
		UnitSprite.setTexture(infantryTexture);
		UnitSprite.setScale((UnitSprite.getScale().x / 128) * (TILE_SIZE), (UnitSprite.getScale().y / 128) * (TILE_SIZE));
		UnitSprite.setOrigin(UnitSprite.getGlobalBounds().getSize().x / 2, UnitSprite.getGlobalBounds().getSize().y / 2);
		UnitSprite.setPosition(troopContainer.getPosition());

		teamOutlineSprite.setTexture(infantryOutlineTexture);
		teamOutlineSprite.setScale((teamOutlineSprite.getScale().x / 128) * (TILE_SIZE)+0.04, (teamOutlineSprite.getScale().y / 128) * (TILE_SIZE)+0.04);
		teamOutlineSprite.setOrigin((teamOutlineSprite.getGlobalBounds().getSize().x / 2) + 0.5, (teamOutlineSprite.getGlobalBounds().getSize().y / 2) + 0.5);
		teamOutlineSprite.setPosition(troopContainer.getPosition());
	}
	else if (squadData.unitType == 2)
	{
		if (!BTRTexture.loadFromFile("ASSETS/BTR_Base.png"))
		{
			std::cout << "error loading squad texture";
		}
		if (!BTROutlineTexture.loadFromFile("ASSETS/BTRTeamOutline.png"))
		{
			std::cout << "error loading squad outline texture";
		}
		if (!unitSpriteExtrasTexture.loadFromFile("ASSETS/BTR_Tower.png"))
		{
			std::cout << "error loading squad extra texture";
		}
		extraSpriteNeeded = true;

		UnitSprite.setTexture(BTRTexture);
		UnitSprite.setScale((UnitSprite.getScale().x / 128) * (TILE_SIZE), (UnitSprite.getScale().y / 128) * (TILE_SIZE));
		UnitSprite.setOrigin(64, 64);
		UnitSprite.setPosition(troopContainer.getPosition());

		teamOutlineSprite.setTexture(BTROutlineTexture);
		teamOutlineSprite.setScale((teamOutlineSprite.getScale().x / 128) * (TILE_SIZE)+0.04, (teamOutlineSprite.getScale().y / 128) * (TILE_SIZE)+0.04);
		teamOutlineSprite.setOrigin(64, 64);
		teamOutlineSprite.setPosition(troopContainer.getPosition());

		unitSpriteExtras.setTexture(unitSpriteExtrasTexture);
		unitSpriteExtras.setScale((unitSpriteExtras.getScale().x / 128) * (TILE_SIZE), (unitSpriteExtras.getScale().y / 128) * (TILE_SIZE));
		unitSpriteExtras.setOrigin(64, 64);
		unitSpriteExtras.setPosition(troopContainer.getPosition());
	}
}

void Squad::moveToFormation(sf::Vector2f t_formationPosition,sf::Time t_deltaTime)
{
	if (t_formationPosition != sf::Vector2f(0, 0))		
	{
		if (formationLeader == false)
		{
			bool outcome = checkFormationPointValid(t_formationPosition);
			if (outcome == false)
			{
				//std::cout << "position invalid\n";
				return;
			}
		}

		sf::Vector2f vectorToTarget = t_formationPosition - troopContainer.getPosition();
		float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
		vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

		if (distance > 2.1)
		{
			float speed = moveSpeed * t_deltaTime.asSeconds();
			troopContainer.move(vectorToTarget.x * (speed), vectorToTarget.y * (speed));
		}

		float rotation = (atan2(vectorToTarget.y, vectorToTarget.x) * 180 / 3.14159265) - 90;
		if (distance <= 2.1)
		{
			if (formationLeader == true && formationFrontReachedGoal == true)
			{
				formationLeaderReachedGoal = true;
				troopContainer.setPosition(t_formationPosition);
				formationActive = false;
				targetReached = true;
				std::cout << "formation leader position reached" << std::endl;
			}
			else if (formationLeaderReachedGoal == true) {
				troopContainer.setPosition(t_formationPosition);
				formationActive = false;
				targetReached = true;
				std::cout << "formation position reached" << std::endl;
			}

			//rotation = 0;
		}

		int column = static_cast<int>(UnitSprite.getPosition().x / TILE_SIZE);
		int row = static_cast<int>(UnitSprite.getPosition().y / TILE_SIZE);

		if (currentCell != (row * TILE_COLUMNS) + column)
		{
			mostRecentCell = currentCell;
		}
		currentCell = (row * TILE_COLUMNS) + column;

		UnitSprite.setPosition(troopContainer.getPosition());
		teamOutlineSprite.setPosition(troopContainer.getPosition());
		if (extraSpriteNeeded == true)
		{
			unitSpriteExtras.setPosition(troopContainer.getPosition());
			unitSpriteExtras.setRotation(rotation);
		}

		UnitSprite.setRotation(rotation);
		teamOutlineSprite.setRotation(rotation);
	}
}

void Squad::steerAroundObstacle(sf::Vector2f t_formationPosition, sf::Time t_deltaTime)
{

}

void Squad::takeLeadersPath(sf::Vector2f t_formationPosition, sf::Time t_deltaTime)
{

}

void Squad::breakFormation(sf::Vector2f t_formationPosition, sf::Time t_deltaTime)
{

}

bool Squad::checkFormationPointValid(sf::Vector2f t_formationPosition)
{
	sf::Vector2f positionOfPoint = normaliser.normalizeToTileCenter(t_formationPosition);
	//std::cout << "formation pos X:  " << t_formationPosition.x << "  formation pos Y: " << t_formationPosition.y << "\n";
	for (int index = 0; index < allInvalidTiles.size(); index++)
	{
		sf::Vector2f tempPosFromCell = normaliser.convertCellNumToCoords(allInvalidTiles[index]);
		//std::cout << "movable pos X:  " << tempPosFromCell.x << "  movable pos Y: " << tempPosFromCell.y << "\n";

		movableCollider.setPosition(tempPosFromCell);
		if (movableCollider.getGlobalBounds().contains(positionOfPoint))
		{
			//std::cout << "overlap found\n";
			return false;
		}
	}
	return true;
}