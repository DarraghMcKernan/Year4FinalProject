#include "Squad.h"

void Squad::init(int t_squadStrength, sf::Vector2f t_startingPos,int t_teamNum)
{
	squadStrength = t_squadStrength;
	teamNum = t_teamNum;

	/*if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}*/

	resetColour();

	troopContainer.setRadius(20);
	troopContainer.setOutlineColor(sf::Color::Black);
	troopContainer.setOutlineThickness(1.5);
	troopContainer.setOrigin(troopContainer.getRadius(), troopContainer.getRadius());
	troopContainer.setPosition(t_startingPos.x - (TILE_SIZE / 2), t_startingPos.y - (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = troopContainer.getPosition();

	//debugStrengthDisplay.setFont(font);
	//debugStrengthDisplay.setString("test");
	//debugStrengthDisplay.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	//debugStrengthDisplay.setFillColor(sf::Color::Black);
	//debugStrengthDisplay.setScale(0.2, 0.2);
	//debugStrengthDisplay.setPosition((troopContainer.getPosition().x - troopContainer.getRadius() / 1.625), (troopContainer.getPosition().y - troopContainer.getRadius() / 1.625));
}

void Squad::update()
{
	if (movementAllowed == true)
	{
		if (troopContainer.getPosition() != targetPosition && squadStrength > 0)
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
			}
			else
			{
				if (distance > 500)//cap speed
				{
					distance = 500;
				}
				else if (distance < 200)//prevent player from slowing too much
				{
					distance = 200;
				}
				vectorToTarget = vectorToTarget * (distance / 100);//slow down as we get closer to the target

				troopContainer.move(vectorToTarget);
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

sf::CircleShape Squad::getTroopContainter()
{
	return troopContainer;
}

void Squad::setTargetPosition(sf::Vector2f t_targetPos)
{
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
		troopContainer.setFillColor(sf::Color(0, 0, 255, 150));
	}
	if (teamNum == 1)
	{
		troopContainer.setFillColor(sf::Color(255, 0, 0, 150));
	}
	if (teamNum == 2)
	{
		troopContainer.setFillColor(sf::Color(0, 255, 255, 150));
	}
	if (teamNum == 3)
	{
		troopContainer.setFillColor(sf::Color(255, 0, 255, 150));
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
