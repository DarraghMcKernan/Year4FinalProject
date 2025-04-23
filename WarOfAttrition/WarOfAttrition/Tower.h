#pragma once
#include "globals.h"

class Tower
{
public:
    Tower(int t_type, int t_teamNum, sf::Vector2f t_position);
    void update();
    void render(sf::RenderWindow& t_window);
    int getType();
    int getTeamNum();
    int getIncome();
    sf::Sprite getTower();

private:
    int type = 0;
    int teamNum = 0;
    sf::Sprite towerSprite;
    sf::Sprite towerShadow;
    sf::Vector2f position;
    int moneyGeneratedPerRound = 100;
};