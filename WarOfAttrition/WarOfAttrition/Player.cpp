#include "Player.h"

void Player::init()
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	tempPlayer.setRadius(20);
	tempPlayer.setFillColor(sf::Color(255, 255, 255, 150));
	tempPlayer.setOutlineColor(sf::Color::Black);
	tempPlayer.setOutlineThickness(1.5);
	tempPlayer.setOrigin(tempPlayer.getRadius(),tempPlayer.getRadius());
	tempPlayer.setPosition((SCREEN_WIDTH / 2) - (TILE_SIZE / 2), (SCREEN_HEIGHT / 2) - (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = tempPlayer.getPosition();//prevent the player from seeking to 0,0 at the start

	strengthValueText.setFont(font);
	strengthValueText.setString(std::to_string(strength));
	strengthValueText.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	strengthValueText.setFillColor(sf::Color::Black);
	strengthValueText.setScale(0.2, 0.2);
	strengthValueText.setPosition((tempPlayer.getPosition().x - tempPlayer.getRadius()/1.625),(tempPlayer.getPosition().y - tempPlayer.getRadius()/ 1.625));
}

void Player::update()
{
	if (activeTimer > 0)
	{
		activeTimer--;
	}
	if (activeTimer == 1)
	{
		playerActive = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && playerActive == false && activeTimer == 0 && tempPlayer.getGlobalBounds().contains(mousePos))
	{
		tempPlayer.setFillColor(sf::Color(0, 255, 0, 150));
		activeTimer = 20;
	}

	if (tempPlayer.getPosition() != targetPosition)
	{
		sf::Vector2f vectorToTarget = targetPosition - tempPlayer.getPosition();
		float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y* vectorToTarget.y));
		vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };

		if (distance < 1)//lock player to target once close enough
		{
			arrivedAtTarget = true;
			playerActive = false;
			tempPlayer.setFillColor(sf::Color(255, 255, 255, 150));
			tempPlayer.setPosition(targetPosition);
			strengthValueText.setPosition((tempPlayer.getPosition().x - tempPlayer.getRadius() / 1.625), (tempPlayer.getPosition().y - tempPlayer.getRadius() / 1.625));
		}
		else
		{
			if (distance < 200)//prevent player from slowing too much
			{
				distance = 200;
			}
			vectorToTarget = vectorToTarget * (distance / 100);//slow down as we get closer to the target

			tempPlayer.move(vectorToTarget);
			strengthValueText.setPosition((tempPlayer.getPosition().x - tempPlayer.getRadius() / 1.625), (tempPlayer.getPosition().y - tempPlayer.getRadius() / 1.625));
		}
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	mousePos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

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
	strengthValueText.setString(std::to_string(strength));
}

void Player::setTargetPosition(int t_cellNum)
{
	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };//center the target on a tile
	//std::cout << "target X: " + std::to_string(targetPosition.x) + "    target Y:" + std::to_string(targetPosition.y) + "\n";//debugging
	//std::cout << "player X: " + std::to_string(tempPlayer.getPosition().x) + "    player Y:" + std::to_string(tempPlayer.getPosition().y) + "\n";//debugging
}

int Player::getStrength()
{
	return strength;
}

sf::CircleShape Player::getPlayerShape()
{
	return tempPlayer;
}