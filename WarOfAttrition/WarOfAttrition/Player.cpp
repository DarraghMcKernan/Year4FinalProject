#include "Player.h"

void Player::init()
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	tempPlayer.setRadius(20);
	tempPlayer.setFillColor(sf::Color(0, 200, 0, 150));
	tempPlayer.setOutlineColor(sf::Color::Black);
	tempPlayer.setOutlineThickness(1.5);
	tempPlayer.setOrigin(tempPlayer.getRadius(),tempPlayer.getRadius());

	strengthValueText.setFont(font);
	strengthValueText.setString(std::to_string(strength));
	strengthValueText.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	strengthValueText.setScale(0.2, 0.2);
	strengthValueText.setPosition(tempPlayer.getPosition());
}

void Player::update()
{
	if (tempPlayer.getPosition() != targetPosition)
	{
		sf::Vector2f vectorToTarget = targetPosition - tempPlayer.getPosition();
		float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y* vectorToTarget.y));
		vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

		if (distance < 1)//lock player to target once close enough
		{
			tempPlayer.setPosition(targetPosition);
			strengthValueText.setPosition(tempPlayer.getPosition());
		}
		else
		{
			if (distance < 100)//prevent player from slowing too much
			{
				distance = 100;
			}
			vectorToTarget = vectorToTarget * (distance / 100);//slow down as we get closer to the target

			tempPlayer.move(vectorToTarget);
			strengthValueText.setPosition(tempPlayer.getPosition());
		}
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(tempPlayer);
	t_window.draw(strengthValueText);
}

void Player::takeDamage(int t_damage)
{
	strength -= t_damage;
	if (strength < 0)
	{
		strength = 0;
	}
	strengthValueText.setFont(font);
}

void Player::setPosition(int t_cellNum)
{
	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };//center the target on a tile
	std::cout << "target X: " + std::to_string(targetPosition.x) + "    target Y:" + std::to_string(targetPosition.y) + "\n";//debugging
	std::cout << "player X: " + std::to_string(tempPlayer.getPosition().x) + "    player Y:" + std::to_string(tempPlayer.getPosition().y) + "\n";//debugging
}
