#include "Squad.h"

void Squad::init(int t_squadStrength, sf::Vector2f t_startingPos,int t_teamNum)
{
	squadStrength = t_squadStrength;
	teamNum = t_teamNum;

	resetColour();

	troopContainer.setSize(sf::Vector2f(TILE_SIZE -5, TILE_SIZE - 5));
	//troopContainer.setRotation(45);//can be used to have collision checks in all 9 surrounding squares or the 4 immediate squares

	//troopContainer.setSize(sf::Vector2f(TILE_SIZE + 15, TILE_SIZE + 15));// used to expand the squad to allow for collision checks of surrounding cells
	//troopContainer.setRotation(45);//can be used to have collision checks in all 9 surrounding squares or the 4 immediate squares

	troopContainer.setOutlineColor(sf::Color::Black);
	troopContainer.setOutlineThickness(1.5);
	troopContainer.setOrigin(troopContainer.getSize().x/2, troopContainer.getSize().y/2);
	troopContainer.setPosition(t_startingPos.x - (TILE_SIZE / 2), t_startingPos.y - (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = troopContainer.getPosition();
}

void Squad::update(sf::Time t_deltaTime)
{
	if (movementAllowed == true)
	{
		if (troopContainer.getPosition() != targetPosition && squadStrength > 0 && turnEnded == true)
		{
			sf::Vector2f vectorToTarget = targetPosition - troopContainer.getPosition();
			float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
			vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };
			if (distance <= 2.1)//lock player to target once close enough
			{
				troopContainer.setPosition(targetPosition);
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
				vectorToTarget = vectorToTarget * (distance / moveSpeed);//slow down as we get closer to the target

				troopContainer.move((vectorToTarget.x * t_deltaTime.asSeconds()) * moveSpeed, (vectorToTarget.y * t_deltaTime.asSeconds())* moveSpeed);
			}
		}
	}
}

void Squad::render(sf::RenderWindow& t_window)
{
	t_window.draw(troopContainer);
}

void Squad::unlockMovement(bool t_allowed)
{
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

bool Squad::movingAllowed()
{
	return movementAllowed;
}

void Squad::resetColour()
{
	if (teamNum == 0)
	{
		troopContainer.setFillColor(sf::Color(0, 0, 255, 100));
	}
	if (teamNum == 1)
	{
		troopContainer.setFillColor(sf::Color(255, 0, 0, 100));
	}
	if (teamNum == 2)
	{
		troopContainer.setFillColor(sf::Color(0, 255, 255, 100));
	}
	if (teamNum == 3)
	{
		troopContainer.setFillColor(sf::Color(255, 0, 255, 100));
	}
}

int Squad::getStrength()
{
	return squadStrength;
}

void Squad::setStrength(int t_strength)
{
	squadStrength = t_strength;
}
