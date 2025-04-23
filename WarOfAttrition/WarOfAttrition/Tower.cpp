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
		towerShadow.setTexture(goldmineTexture);
		towerSprite.setScale(0.25f, 0.25f);
		towerShadow.setScale(0.3f, 0.3f);
	}
	if (type == 1)
	{
		if (!researchBuildingTexture.loadFromFile("ASSETS/researchBuilding.png"))
		{
			std::cout << "error with research building texture file";
		}
		if (!researchBuildingOutlineTexture.loadFromFile("ASSETS/researchBuildingShadow.png"))
		{
			std::cout << "error with research building shadow texture file";
		}
		towerSprite.setTexture(researchBuildingTexture);
		towerShadow.setTexture(researchBuildingOutlineTexture);
		towerSprite.setScale(1.0f, 1.0f);
		towerShadow.setScale(1.1f, 1.1f);
	}
	towerSprite.setOrigin(towerSprite.getTextureRect().width / 2, towerSprite.getTextureRect().height / 2);
	towerShadow.setOrigin(towerShadow.getTextureRect().width / 2, towerShadow.getTextureRect().height / 2);

	towerSprite.setPosition(position);
	towerShadow.setPosition(position);


	if (t_teamNum == 0)
	{
		towerShadow.setColor(sf::Color(0, 0, 255, 200));
	}
	if (t_teamNum == 1)
	{
		towerShadow.setColor(sf::Color(255, 0, 0, 200));
	}
	if (t_teamNum == 2)
	{
		towerShadow.setColor(sf::Color(0, 255, 255, 200));
	}
	if (t_teamNum == 3)
	{
		towerShadow.setColor(sf::Color(255, 0, 255, 200));
	}
}

void Tower::update()
{

}

void Tower::render(sf::RenderWindow& t_window)
{
	t_window.draw(towerShadow);
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

sf::Sprite Tower::getTower()
{
	return towerSprite;
}
