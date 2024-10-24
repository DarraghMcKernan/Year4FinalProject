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

}
