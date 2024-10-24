#include "Enemy.h"

void Enemy::init()
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	enemyShape.setRadius(20);
	enemyShape.setFillColor(sf::Color(255, 0, 0, 150));
	enemyShape.setOutlineColor(sf::Color::Black);
	enemyShape.setOutlineThickness(1.5);
	enemyShape.setOrigin(enemyShape.getRadius(), enemyShape.getRadius());
	enemyShape.setPosition((SCREEN_WIDTH / 2) + (TILE_SIZE / 2), (SCREEN_HEIGHT / 2) + (TILE_SIZE / 2));//spawn player in the center of the map
	targetPosition = enemyShape.getPosition();//prevent the player from seeking to 0,0 at the start

	strengthText.setFont(font);
	strengthText.setString(std::to_string(strength));
	strengthText.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	strengthText.setFillColor(sf::Color::Black);
	strengthText.setScale(0.2, 0.2);
	strengthText.setPosition((enemyShape.getPosition().x - enemyShape.getRadius() / 2.5), (enemyShape.getPosition().y - enemyShape.getRadius() / 1.625));
}

void Enemy::update()
{
	if (enemyShape.getPosition() != targetPosition && strength > 0)
	{
		sf::Vector2f vectorToTarget = targetPosition - enemyShape.getPosition();
		float distance = sqrt((vectorToTarget.x * vectorToTarget.x) + (vectorToTarget.y * vectorToTarget.y));
		vectorToTarget = { vectorToTarget.x / distance,vectorToTarget.y / distance };
		std::cout << std::to_string(distance) + "\n";
		if (distance <= 2.1)//lock enemy to target once close enough
		{
			enemyShape.setPosition(targetPosition);
			strengthText.setPosition((enemyShape.getPosition().x - enemyShape.getRadius() / 1.625), (enemyShape.getPosition().y - enemyShape.getRadius() / 1.625));
		}
		else
		{
			if (distance > 500)//cap speed
			{
				distance = 500;
			}
			else if (distance < 200)//prevent enemy from slowing too much
			{
				distance = 200;
			}
			vectorToTarget = vectorToTarget * (distance / 100);//slow down as we get closer to the target

			enemyShape.move(vectorToTarget);
			strengthText.setPosition((enemyShape.getPosition().x - enemyShape.getRadius() / 1.625), (enemyShape.getPosition().y - enemyShape.getRadius() / 1.625));
		}
	}
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(enemyShape);
	t_window.draw(strengthText);
}

int Enemy::getStrength()
{
	return strength;
}

sf::CircleShape Enemy::getEnemyShape()
{
	return enemyShape;
}

void Enemy::setTargetPos(int t_cellNum)
{
	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };
}

void Enemy::takeDamage(int t_damage)
{
	strength -= t_damage;
	if (strength < 0)
	{
		strength = 0;
		enemyShape.setFillColor(sf::Color(255, 255, 255, 100));
	}
	strengthText.setString(std::to_string(strength));
}
