#include "Player.h"

void Player::init(int t_teamNum)
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	Squad newSquad;
	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads.push_back(newSquad);
		sf::Vector2f startPos = { ((150 + index) % TILE_COLUMNS) * TILE_SIZE, ((150 + index + t_teamNum) / TILE_COLUMNS) * TILE_SIZE };
		startPos.y += t_teamNum * (TILE_SIZE * 3);
		playersSquads[index].init(100,startPos,t_teamNum);
	}
}

void Player::update()
{
	if (activeTargetTimer > 0)
	{
		if (activeTargetTimer == 1)
		{
			targetNeeded = true;
		}
		activeTargetTimer--;
	}

	for (int index = 0; index < playerSquadsCount; index++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && playersSquads[index].getTroopContainter().getGlobalBounds().contains(mousePos) && activeTargetTimer == 0)
		{
			playersSquads[index].unlockMovement(true); 
			activeTargetTimer = 30;
			//targetNeeded = true;
		}
		if (playersSquads[index].targetReached == true)
		{
			playersSquads[index].targetReached = false;
			arrivedAtTarget = true;
		}
		playersSquads[index].update();
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	mousePos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].render(t_window);
	}
}

void Player::setTargetPosition(int t_cellNum)
{
	targetNeeded = false;

	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };//center the target on a tile

	for (int index = 0; index < playerSquadsCount; index++)
	{
		if (playersSquads[index].movingAllowed() == true)
		{
			playersSquads[index].setTargetPosition(targetPosition);
		}
	}
}

int Player::collisionChecker(sf::CircleShape targetToCheck,int t_strength)
{
	for (int index = 0; index < playerSquadsCount; index++)
	{
		if (playersSquads[index].getTroopContainter().getGlobalBounds().intersects(targetToCheck.getGlobalBounds()))
		{
			playersSquads[index].setStrength(playersSquads[index].getStrength() - t_strength);
			return playersSquads[index].getStrength() - t_strength;
		}
	}
	return 0;
}
