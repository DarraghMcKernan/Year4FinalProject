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
	//targetPosition = enemyShape.getPosition();//prevent the player from seeking to 0,0 at the start

	strengthText.setFont(font);
	strengthText.setString(std::to_string(strength));
	strengthText.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	strengthText.setFillColor(sf::Color::Black);
	strengthText.setScale(0.2, 0.2);
	strengthText.setPosition((enemyShape.getPosition().x - enemyShape.getRadius() / 2.5), (enemyShape.getPosition().y - enemyShape.getRadius() / 1.625));
}

void Enemy::update()
{

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
		enemyShape.setFillColor(sf::Color(255, 0, 0, 100));
	}
	strengthText.setString(std::to_string(strength));
}
