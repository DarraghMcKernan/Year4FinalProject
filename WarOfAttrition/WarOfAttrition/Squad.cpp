#include "Squad.h"

void Squad::init(int t_squadStrength, sf::Vector2f t_startingPos)
{
	squadStrength = t_squadStrength;

	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	troopContainer.setRadius(20);
	troopContainer.setFillColor(sf::Color(0, 0, 255, 150));
	troopContainer.setOutlineColor(sf::Color::Black);
	troopContainer.setOutlineThickness(1.5);
	troopContainer.setOrigin(troopContainer.getRadius(), troopContainer.getRadius());
	troopContainer.setPosition(t_startingPos.x - (TILE_SIZE / 2), t_startingPos.y - (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = troopContainer.getPosition();

	debugStrengthDisplay.setFont(font);
	debugStrengthDisplay.setString(std::to_string(squadStrength));
	debugStrengthDisplay.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	debugStrengthDisplay.setFillColor(sf::Color::Black);
	debugStrengthDisplay.setScale(0.2, 0.2);
	debugStrengthDisplay.setPosition((troopContainer.getPosition().x - troopContainer.getRadius() / 1.625), (troopContainer.getPosition().y - troopContainer.getRadius() / 1.625));
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
			std::cout << std::to_string(distance) + "\n";
			if (distance <= 2.1)//lock player to target once close enough
			{
				troopContainer.setPosition(targetPosition);
				debugStrengthDisplay.setPosition((troopContainer.getPosition().x - troopContainer.getRadius() / 1.625), (troopContainer.getPosition().y - troopContainer.getRadius() / 1.625));
				movementAllowed = false;
				targetReached = true;
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
				debugStrengthDisplay.setPosition((troopContainer.getPosition().x - troopContainer.getRadius() / 1.625), (troopContainer.getPosition().y - troopContainer.getRadius() / 1.625));
			}
		}
	}
}

void Squad::render(sf::RenderWindow& t_window)
{
	t_window.draw(troopContainer);
	//t_window.draw(debugStrengthDisplay);
}

void Squad::unlockMovement(bool t_allowed)
{
	movementAllowed = t_allowed;
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
