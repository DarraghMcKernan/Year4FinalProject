#include "Tower.h"

Tower::Tower(int t_type, int t_teamNum,sf::Vector2f t_position) : position(t_position) , type(t_type), teamNum(t_teamNum)
{
	if (type == 0)
	{
		if(!goldmineTexture.loadFromFile("ASSETS/GoldMine.png"))
		{
			std::cout << "error with goldmine texture file";
		}
		towerSprite.setTexture(goldmineTexture);
		towerSprite.setScale(0.25f, 0.25f);
	}
	towerSprite.setOrigin(towerSprite.getTextureRect().width / 2, towerSprite.getTextureRect().height / 2);

	towerSprite.setPosition(position);
}

void Tower::update()
{

}

void Tower::render(sf::RenderWindow& t_window)
{
	t_window.draw(towerSprite);
}

int Tower::getType()
{	
	return type;
}

int Tower::getTeamNum()
{
	return teamNum;
}

int Tower::getIncome()
{
	return moneyGeneratedPerRound;
}