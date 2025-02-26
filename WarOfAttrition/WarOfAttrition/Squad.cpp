#include "Squad.h"

void Squad::init(sf::Vector2f t_startingPos,int t_teamNum, int t_unitType)
{
	if(t_unitType == 0)
	{
		squadData.health = 250;
		squadData.squadStrength = 200;
		moveSpeed = 80;
	}
	if(t_unitType == 1)
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

	resetColour();

	troopContainer.setSize(sf::Vector2f(TILE_SIZE -5, TILE_SIZE - 5));
	//troopContainer.setRotation(45);//can be used to have collision checks in all 9 surrounding squares or the 4 immediate squares

	//troopContainer.setSize(sf::Vector2f(TILE_SIZE + 15, TILE_SIZE + 15));// used to expand the squad to allow for collision checks of surrounding cells
	//troopContainer.setRotation(45);//can be used to have collision checks in all 9 surrounding squares or the 4 immediate squares

	//troopContainer.setOutlineColor(sf::Color::Black);
	//troopContainer.setOutlineThickness(1.5);
	troopContainer.setOrigin(troopContainer.getSize().x/2, troopContainer.getSize().y/2);
	troopContainer.setPosition(t_startingPos.x - (TILE_SIZE / 2), t_startingPos.y - (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = troopContainer.getPosition();

	setunitType();
}

void Squad::update(sf::Time t_deltaTime)
{
	if (movementAllowed == true)
	{
		if (troopContainer.getPosition() != targetPosition && squadData.squadStrength > 0 && turnEnded == true)
		{
			sf::Vector2f vectorToTarget = targetPosition - troopContainer.getPosition();
			float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
			vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };
			if (distance <= 2.1)//lock player to target once close enough
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
				UnitSprite.setRotation(0);
				if (extraSpriteNeeded == true)
				{
					unitSpriteExtras.setPosition(UnitSprite.getPosition());
					unitSpriteExtras.setRotation(0);
				}
				teamOutlineSprite.setPosition(troopContainer.getPosition());
				teamOutlineSprite.setRotation(0);
				movementAllowed = false;
				targetReached = true;
				resetColour();
				turnEnded = false;
				targetSet = false;
			}
			else
			{
				if (distance > 500)//artificially cap speed
				{
					distance = 500;
				}
				else if (distance < 200)//prevent player from slowing too much
				{
					distance = 200;
				}
				//vectorToTarget = vectorToTarget * (distance);//slow down as we get closer to the target

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
	if(extraSpriteNeeded == true)
	{
		t_window.draw(unitSpriteExtras);
	}
}

void Squad::unlockMovement(bool t_allowed)
{
	targetReached = false;
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
	sf::Vector2f vectorToTarget = t_formationPosition - troopContainer.getPosition();
	float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
	vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

	float speed = moveSpeed * t_deltaTime.asSeconds();
	troopContainer.move(vectorToTarget.x * (speed / 2), vectorToTarget.y * (speed/2));

	float rotation = (atan2(vectorToTarget.y, vectorToTarget.x) * 180 / 3.14159265) - 90;
	if (distance <= 2.1)
	{
		if (formationLeader == true)
		{
			formationLeaderReachedGoal = true;
			troopContainer.setPosition(t_formationPosition);
			formationActive = false;
			targetReached = true;
			std::cout << "formation leader position reached" << std::endl;
		}
		else if(formationLeaderReachedGoal == true){
			troopContainer.setPosition(t_formationPosition);
			formationActive = false;
			targetReached = true;
			std::cout << "formation position reached" << std::endl;
		}
		
		//rotation = 0;
	}

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
	if (squadData.unitType == 1)
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
	if (squadData.unitType == 2)
	{
		if (!BTRTexture.loadFromFile("ASSETS/BTR_Base.png"))
		{
			std::cout << "error loading squad texture";
		}
		if (!BTROutlineTexture.loadFromFile("ASSETS/BTRTeamOutline.png"))
		{
			std::cout << "error loading squad outline texture";
		}
		if(!unitSpriteExtrasTexture.loadFromFile("ASSETS/BTR_Tower.png"))
		{
			std::cout << "error loading squad extra texture";
		}
		extraSpriteNeeded = true;

		UnitSprite.setTexture(BTRTexture);
		UnitSprite.setScale((UnitSprite.getScale().x / 128) * (TILE_SIZE), (UnitSprite.getScale().y / 128) * (TILE_SIZE));
		UnitSprite.setOrigin((UnitSprite.getGlobalBounds().getSize().x / 2) - (worldTileOffset.x), (UnitSprite.getGlobalBounds().getSize().y / 2) - (worldTileOffset.y));
		UnitSprite.setPosition(troopContainer.getPosition() - worldTileOffset);

		teamOutlineSprite.setTexture(BTROutlineTexture);
		teamOutlineSprite.setScale((teamOutlineSprite.getScale().x / 128) * (TILE_SIZE)+0.04, (teamOutlineSprite.getScale().y / 128) * (TILE_SIZE)+0.04);
		teamOutlineSprite.setOrigin(((teamOutlineSprite.getGlobalBounds().getSize().x / 2) + 3) - (worldTileOffset.x), ((teamOutlineSprite.getGlobalBounds().getSize().y / 2) + 3) - (worldTileOffset.y));
		teamOutlineSprite.setPosition(troopContainer.getPosition() - worldTileOffset);

		unitSpriteExtras.setTexture(unitSpriteExtrasTexture);
		unitSpriteExtras.setScale((unitSpriteExtras.getScale().x / 128) * (TILE_SIZE), (unitSpriteExtras.getScale().y / 128) * (TILE_SIZE));
		unitSpriteExtras.setOrigin((unitSpriteExtras.getGlobalBounds().getSize().x / 2) - (worldTileOffset.x), (unitSpriteExtras.getGlobalBounds().getSize().y / 2) - (worldTileOffset.y));
		unitSpriteExtras.setPosition(troopContainer.getPosition() - worldTileOffset);
	}
}