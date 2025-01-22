#include "Player.h"

void Player::init(int t_teamNum, int t_unitType)
{
	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	Squad newSquad;
	sf::Text newText;
	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads.push_back(newSquad);
		sf::Vector2f startPos = { ((150 + index) % TILE_COLUMNS) * TILE_SIZE, ((150 + index + t_teamNum) / TILE_COLUMNS) * TILE_SIZE };
		startPos.y += t_teamNum * (TILE_SIZE * 3);
		playersSquads[index].init(100 + (25*index), startPos, t_teamNum,0);

		//playersSquadsStrenghts.push_back(newText);
		//playersSquadsStrenghts[index].setFont(font);
		//playersSquadsStrenghts[index].setString(std::to_string(playersSquads[index].getStrength()));
		//playersSquadsStrenghts[index].setCharacterSize(100);//increase size and then downscale to prevent blurred text
		//playersSquadsStrenghts[index].setFillColor(sf::Color::White);
		//playersSquadsStrenghts[index].setOutlineThickness(5 );
		//playersSquadsStrenghts[index].setScale(0.2, 0.2);
		//playersSquadsStrenghts[index].setOrigin(sf::Vector2f(TILE_SIZE + playersSquadsStrenghts[index].getGlobalBounds().width/2, TILE_SIZE + playersSquadsStrenghts[index].getGlobalBounds().height / 2));
		//playersSquadsStrenghts[index].setPosition((playersSquads[index].getTroopContainter().getPosition()));
	}

	tileForColliding.setSize(sf::Vector2f(TILE_SIZE +3, TILE_SIZE+3));//used for making sure player cant select a tile that its own squads are on
	tileForColliding.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
}

void Player::update(sf::Time& t_deltaTime)
{
	int checkIfAllMoved = 0;
	for (int index = 0; index < playerSquadsCount; index++)
	{
		if (playersSquads[index].targetReached == true && turnEnded == true)//all have reached their targets
		{
			checkIfAllMoved++;
		}
		else if (playersSquads[index].movingAllowed() == false && turnEnded == true)//if they have not been set to move at all ignore them
		{
			checkIfAllMoved++;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && playersSquads[index].getTroopContainter().getGlobalBounds().contains(mousePos)
			&& activeTargetTimer == 0 && turnEnded == false && unitsMoved < MAX_MOVES_PER_TURN && playersSquads[index].movingAllowed() == false)
		{
			if (squadSet == false)//allows for selected squad to be changed without wasting moves
			{
				unitsMoved++;
			}
			else playersSquads[squadBeingControlled].unlockMovement(false);

			squadSet = true;
			playersSquads[squadBeingControlled].resetColour();
			squadBeingControlled = index;
			playersSquads[index].unlockMovement(true);
			activeTargetTimer = 10;
		}
		playersSquads[index].update(t_deltaTime);
	}

	if (endTurnActive == true)//if space is pressed allow all squads to move
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			if (playersSquads[index].movingAllowed() == true && playersSquads[index].targetSet == true)
			{
				playersSquads[index].turnEnded = true;
				turnEnded = true;
			}
			else if (playersSquads[index].movingAllowed() == true && playersSquads[index].targetSet != true)
			{
				playersSquads[index].unlockMovement(false);
				playersSquads[index].targetReached = false;
				playersSquads[index].resetColour();
			}
		}
	}

	if (checkIfAllMoved == playerSquadsCount)//if all squads that were allowed to move have moved end turn
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			playersSquads[index].targetReached = false;
		}
		squadBeingControlled = 1;
		arrivedAtTarget = true;
		turnEnded = false;
		unitsMoved = 0;
		timerForEnd = 0;
		endTurnActive = false;
	}
}

void Player::fixedUpdate()
{
	if (timerForEnd > 0)
	{
		timerForEnd--;
		if (timerForEnd == 1)
		{
			endTurnActive = false;
		}
	}
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
		//playersSquadsStrenghts[index].setPosition((playersSquads[index].getTroopContainter().getPosition()));
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	mousePos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].render(t_window);
		//t_window.draw(playersSquadsStrenghts[index]);
	}
}

void Player::setTargetPosition(int t_cellNum)
{
	squadSet = false;
	targetNeeded = false;
	squadsThatMoved.push_back(squadBeingControlled);

	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };//center the target on a tile

	if (playersSquads[squadBeingControlled].movingAllowed() == true)
	{
		playersSquads[squadBeingControlled].setTargetPosition(targetPosition);
	}
}

std::vector<int> Player::collisionCheckerDamage(std::vector<sf::RectangleShape> targetToCheck,int t_strength)
{
	std::vector<int> damageTaken;

	for (int enemySquadsIndex = 0; enemySquadsIndex < targetToCheck.size(); enemySquadsIndex++)
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			if (playersSquads[index].getTroopContainter().getGlobalBounds().intersects(targetToCheck[enemySquadsIndex].getGlobalBounds()))
			{
				if (t_strength < playersSquads[index].getStrength())
				{
					int outcome = playersSquads[index].getStrength() - t_strength;
					playersSquads[index].setStrength(outcome);
					//playersSquadsStrenghts[index].setString(std::to_string(playersSquads[index].getStrength()));
					//return t_strength;//lost the fight so is now 0
					damageTaken.push_back(t_strength);
				}
				else if (t_strength > playersSquads[index].getStrength())
				{
					int outcome = t_strength - playersSquads[index].getStrength();
					eliminateUnit(index);
					//return outcome;//won the fight but took damage
					damageTaken.push_back(outcome);
				}
				else {
					eliminateUnit(index);//both lose as equal health -- might change to defenders advantage
					damageTaken.push_back(t_strength);
					//return t_strength;
				}
			}
		}
	}
	
	return damageTaken;//no targets found no damage done
}

bool Player::checkIfContained(sf::Vector2f t_pointToCheck)
{
	for (int index = 0; index < playerSquadsCount; index++)
	{
		tileForColliding.setPosition(playersSquads[index].getTroopContainter().getPosition());
		if (tileForColliding.getGlobalBounds().contains(t_pointToCheck))
		{
			return true;
		}
	}
	return false;
}

void Player::attemptEndTurn()
{
	endTurnActive = true;
	timerForEnd = 120;
}

bool Player::squadDistanceValid(sf::Vector2f t_hoveredTile)
{
	distanceOK = false;
	sf::Vector2f temp = t_hoveredTile - getSquadPosition();
	float distance = sqrt((temp.x * temp.x) + (temp.y * temp.y));
	if (distance < (playersSquads[squadBeingControlled].maxMoveDistance) * TILE_SIZE)
	{
		distanceOK = true;
		return true;
	}
	return false;
}

void Player::generateNewUnit(int t_teamNum, int t_unitType, sf::Vector2f t_unitSpawnPos)
{
	Squad newSquad;

	int strength = 100;//will be determined based on type
	sf::Vector2f positionWithOffset = {t_unitSpawnPos.x + TILE_SIZE/2,t_unitSpawnPos.y + TILE_SIZE/2};
	newSquad.init(strength, positionWithOffset, t_teamNum,t_unitType);

	playersSquads.push_back(newSquad);

	playerSquadsCount++;
}

void Player::eliminateUnit(int t_num)
{
	if (t_num < playerSquadsCount)
	{
		//playersSquadsStrenghts.erase(playersSquadsStrenghts.begin() + t_num);
		playersSquads.erase(playersSquads.begin() + t_num);
		playerSquadsCount--;
	}
	if (playerSquadsCount <= 0)
	{
		playerEliminated = true;
	}
}

void Player::turnActive()
{
	squadsThatMoved.clear();
}

void Player::dealDamage(std::vector<int> t_damage)
{
	for (int index = 0; index < t_damage.size(); index++)
	{
		int outcome = playersSquads[squadsThatMoved[index]].getStrength() - t_damage[index];
		playersSquads[squadsThatMoved[index]].setStrength(outcome);
		//playersSquadsStrenghts[index].setString(std::to_string(playersSquads[index].getStrength()));
		if (playersSquads[squadsThatMoved[index]].getStrength() <= 0)
		{
			eliminateUnit(squadsThatMoved[index]);
		}
	}
}

std::vector<sf::RectangleShape> Player::returnMovedSquads()
{
	std::vector<sf::RectangleShape> allMovedSquads;

	for(int index = 0;index < squadsThatMoved.size();index++)
	{
		allMovedSquads.push_back(playersSquads[squadsThatMoved[index]].getTroopContainter());
	}

	return allMovedSquads;
}

sf::Vector2f Player::getSquadPosition()
{
	return playersSquads.at(squadBeingControlled).getTroopContainter().getPosition();
}

SquadData Player::getSquadData(int t_squadNum)
{
	if (t_squadNum > 0)
	{
		return playersSquads.at(t_squadNum).getSquadData();
	}
	return playersSquads.at(0).getSquadData();
}

int Player::getSquadNumHovered(sf::Vector2f t_pointToCheck)
{
	for (int index = 0; index < playerSquadsCount; index++)
	{
		tileForColliding.setPosition(playersSquads[index].getTroopContainter().getPosition());
		if (tileForColliding.getGlobalBounds().contains(t_pointToCheck))
		{
			return index;
		}
	}
	return -1;
}
