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
		playersSquads[index].init(startPos, t_teamNum,0);

	}

	tileForColliding.setSize(sf::Vector2f(TILE_SIZE +3, TILE_SIZE+3));//used for making sure player cant select a tile that its own squads are on
	tileForColliding.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));

}

void Player::update(sf::Time& t_deltaTime)
{
	//std::cout << currentFormationLeader << " leader\n";

	if (currentFormationLeader != -1 && formationTemp.formationMovingActive == false && targetPosition != sf::Vector2f(0,0) && formationTemp.leaderTargetReached == false && formationTemp.leaderInfoSet == false && formationCreated == true)
	{
		formationTemp.setLeaderInfo(playersSquads[currentFormationLeader].getSprite(), playersSquads[currentFormationLeader].getSquadData().moveSpeed);
		formationTemp.setLeaderPosAndTarget(playersSquads[currentFormationLeader].getSprite().getPosition(), targetPosition);
		formationTemp.leaderInfoSet = true;
		searchForPath = true;
		std::cout << currentFormationLeader << " leader setup\n";
	}

	if (formationTemp.formationMovingActive == true)
	{
		formationTemp.updateLeaderCopy(playersSquads[currentFormationLeader].getSprite());
		formationTemp.update(t_deltaTime);
		playersSquads[currentFormationLeader].setRotation(formationTemp.updatedLeaderRotation());
	}

	int checkIfAllMoved = 0;
	for (int index = 0; index < playerSquadsCount; index++)
	{
		if (playersSquads[index].formationLeader == true && playersSquads[index].formationLeaderReachedGoal == true)
		{
			for (int i = 0; i < playerSquadsCount; i++)
			{
				playersSquads[i].formationLeaderReachedGoal = true;
				playersSquads[i].checkIfTargetReached();
			}
		}

		if (formationCreationAllowed == true)
		{
			if (playersSquads[index].formationLeader == false && playersSquads[index].formationActive == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && playersSquads[index].getTroopContainter().getGlobalBounds().contains(mousePos)
					&& activeTargetTimer == 0 && turnEnded == false && playersSquads[index].movingAllowed() == false)
				{
					if (playersSquads[currentFormationLeader].formationLeader == false)
					{
						playersSquads[currentFormationLeader].formationLeader = true;
						std::cout << currentFormationLeader << " is now the temp leader\n";
						playersSquads[currentFormationLeader].setFormationNum(formationTemp.getPositionInFormation());
						formationCreated = true;
					}

					playersSquads[currentFormationLeader].formationActive = true;
					playersSquads[index].formationActive = true;
					std::cout << index << " added to formation\n";
					playersSquads[index].setFormationNum(formationTemp.getPositionInFormation());
				}
			}
		}

		if (formationTemp.leaderTargetReached == true && index == currentFormationLeader)
		{
			playersSquads[index].formationFrontReachedGoal = true;
			//std::cout << "leader doing something \n";
		}
		if (playersSquads[index].formationActive == true && formationMovementUnlocked == true)// && playersSquads[index].formationLeader == false)
		{
			playersSquads[index].moveToFormationPosition(formationTemp.getFormationPosition(playersSquads[index].getFormationNum()),t_deltaTime);
			//std::cout << "leader doing something \n";
		}
		else {
			if (playersSquads[index].targetReached == true && turnEnded == true)//all have reached their targets
			{
				checkIfAllMoved++;
			}
			else if (playersSquads[index].movingAllowed() == false && turnEnded == true)//if they have not been set to move at all ignore them
			{
				checkIfAllMoved++;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && playersSquads[index].getTroopContainter().getGlobalBounds().contains(mousePos)
				&& activeTargetTimer == 0 && turnEnded == false && unitsMoved < MAX_MOVES_PER_TURN && playersSquads[index].movingAllowed() == false
				&& playersSquads[index].formationActive == false)
			{
				if (squadSet == false)//allows for selected squad to be changed without wasting moves
				{
					unitsMoved++;
				}
				else playersSquads[squadBeingControlled].unlockMovement(false);

				if (currentFormationLeader == -1)
				{
					currentFormationLeader = index;
				}
				else if (formationCreated == false)
				{
					currentFormationLeader = index;
				}
				squadSet = true;
				searchForPath = true;
				playersSquads[squadBeingControlled].resetColour();
				formationCreationAllowed = true;
				squadBeingControlled = index;
				std::cout << "squad being controlled " << squadBeingControlled << "\n";
				playersSquads[index].unlockMovement(true);
				activeTargetTimer = 10;

				std::cout << "unit selected \n";
			}
		}

		if (playersSquads[index].formationLeader == false && playersSquads[index].movingAllowed() == true)
		{
 			playersSquads[index].update(t_deltaTime);//not getting path to target
		}
	}

	if (endTurnActive == true)//if space is pressed allow all squads to move
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			if (playersSquads[index].movingAllowed() == true && playersSquads[index].targetSet == true)
			{
				playersSquads[index].turnEnded = true;
				turnEnded = true;
				formationMovementUnlocked = true;
			}
			else if (playersSquads[index].movingAllowed() == true && playersSquads[index].targetSet != true)
			{
				playersSquads[index].unlockMovement(false);
				playersSquads[index].targetReached = false;
				playersSquads[index].resetColour();
			}
		}

		formationTemp.formationMovingActive = true;
	}

	int counter = 0;
	for (int index = 0; index < playerSquadsCount; index++)
	{
		if (playersSquads[index].targetReached == true)
		{
			counter++;
		}
	}
	if (counter == playerSquadsCount)
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			playersSquads[index].targetReached = false;
			//playersSquads[index].formationActive = false;
			//playersSquads[index].formationLeader = false;
			playersSquads[index].targetSet = false;
			playersSquads[index].turnEnded = false;
			playersSquads[index].formationLeaderReachedGoal = false;
			playersSquads[index].stopMovement();
		}
		squadBeingControlled = 1;
		formationCreationAllowed = false;
		formationMovementUnlocked = false;
		formationCreated = false;
		arrivedAtTarget = true;
		turnEnded = false;
		unitsMoved = 0;
		timerForEnd = 0;
		endTurnActive = false;
		formationTemp.formationMovingActive = false;
		formationTemp.leaderInfoSet = false;
	}

	if (checkIfAllMoved == playerSquadsCount)//if all squads that were allowed to move have moved end turn
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			playersSquads[index].targetReached = false;
			playersSquads[index].stopMovement();
		}
		squadBeingControlled = 1;
		formationCreationAllowed = false;
		arrivedAtTarget = true;
		turnEnded = false;
		unitsMoved = 0;
		timerForEnd = 0;
		endTurnActive = false;
		formationTemp.leaderInfoSet = false;
		formationTemp.formationMovingActive = false;
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
}

void Player::render(sf::RenderWindow& t_window)
{
	mousePos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].render(t_window);
		//t_window.draw(playersSquadsStrenghts[index]);
	}
	if(playersTowers.size() > 0)
	{
		for (int index = 0; index < playersTowers.size(); index++)
		{
			playersTowers[index].render(t_window);
		}
	}

	std::vector<sf::CircleShape> debug = formationTemp.getDebugCirclesToDraw();
	if (debug.size() > 0)
	{
		for (int index = 0; index < debug.size(); index++)
		{
			t_window.draw(debug[index]);
		}
	}
}

void Player::setTargetPosition(int t_cellNum)
{//////////
	squadSet = false;
	targetNeeded = false;
	formationCreationAllowed = false;
	squadsThatMoved.push_back(squadBeingControlled);

	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };//center the target on a tile

	if (playersSquads[squadBeingControlled].movingAllowed() == true)
	{
		playersSquads[squadBeingControlled].setTargetPosition(targetPosition);
	}
}

std::vector<int> Player::collisionCheckerDamage(std::vector<sf::RectangleShape> targetToCheck, std::vector<SquadData> t_strength)
{
	std::vector<int> damageTaken;
	int currentStrength = 0;

	for (int enemySquadsIndex = 0; enemySquadsIndex < targetToCheck.size(); enemySquadsIndex++)
	{
		damageTaken.push_back(0);
	}

	for (int enemySquadsIndex = 0; enemySquadsIndex < targetToCheck.size(); enemySquadsIndex++)
	{
		for (int index = 0; index < playerSquadsCount; index++)
		{
			if (playersSquads[index].getTroopContainter().getGlobalBounds().intersects(targetToCheck[enemySquadsIndex].getGlobalBounds()))
			{
				int damage = t_strength[currentStrength].squadStrength;

				int randomChance = rand() % 100;
				if (randomChance < 30)
				{
					damage = damage * 0.9f;
					std::cout << "Damage reduced\n";
				}
				else if (randomChance > 70)
				{
					damage = damage * 1.1f;
					std::cout << "Damage increased\n";
				}
				currentStrength++;

				int outcome = playersSquads[index].getSquadData().health - damage;
				playersSquads[index].setHealth(outcome);

				damageTaken[enemySquadsIndex] = damage;
				//damageTaken.push_back(damage);
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

	sf::Vector2f positionWithOffset = {t_unitSpawnPos.x + TILE_SIZE/2,t_unitSpawnPos.y + TILE_SIZE/2};
	newSquad.init(positionWithOffset, t_teamNum,t_unitType);

	playersSquads.push_back(newSquad);

	playerSquadsCount++;
}

void Player::generateNewTower(int t_type, int t_teamNum, sf::Vector2f t_position)
{
	Tower newTower(t_type, t_teamNum, t_position);
	playersTowers.push_back(newTower);
}

void Player::eliminateUnit(int t_num)
{
	if (t_num < playerSquadsCount)
	{
		if (playersSquads[t_num].getUnitType() == 1)
		{
			money += 75;
		}
		else if (playersSquads[t_num].getUnitType() == 0)
		{
			money += 50;
		}
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
		if (t_damage[index] != 0)
		{
			int randomChance = rand() % 100;
			if (randomChance < 30)
			{
				t_damage[index] = t_damage[index] * 0.9f;
				std::cout << "Damage reduced\n";
			}
			else if (randomChance > 70)
			{
				t_damage[index] = t_damage[index] * 1.1f;
				std::cout << "Damage increased\n";
			}

			int outcome = playersSquads[squadsThatMoved[index]].getSquadData().health - t_damage[index];
			playersSquads[squadsThatMoved[index]].setHealth(outcome);
		}

		//playersSquadsStrenghts[index].setString(std::to_string(playersSquads[index].getStrength()));
	/*	if (playersSquads[squadsThatMoved[index]].getStrength() <= 0)
		{
			eliminateUnit(squadsThatMoved[index]);
		}*/
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

std::vector<SquadData> Player::returnMovedSquadsData()
{
	std::vector<SquadData> allMovedSquadsData;

	for (int index = 0; index < squadsThatMoved.size(); index++)
	{
		allMovedSquadsData.push_back(playersSquads[squadsThatMoved[index]].getSquadData());
	}

	return allMovedSquadsData;
}

sf::Vector2f Player::getFormationTarget()
{
	return formationTemp.getTargetPosition();
}

sf::Vector2f Player::getFormationStart()
{
	return playersSquads[squadBeingControlled].getTroopContainter().getPosition();
}

void Player::givePathToFormation(std::vector<int> t_path)
{
	if (formationCreated == true && currentFormationLeader == squadBeingControlled)
	{
		formationTemp.setFoundPath(t_path);
		for (int index = 0; index < playerSquadsCount; index++)
		{
			if (playersSquads[index].formationActive == true)//give all squads the leaders path so that they can default to it if needed
			{
				playersSquads[index].pathToTarget = t_path;
			}			
		}
	}
	std::cout << "path given to " << squadBeingControlled << "\n";
	playersSquads[squadBeingControlled].pathToTarget = t_path;
	targetPosition = sf::Vector2f(0, 0);
}

void Player::resetMovedUnitsAfterFight(int t_unit)//should be the last function to run this turn
{
	playersSquads[t_unit].placeOnRecentCell();

	targetPosition = sf::Vector2f(0, 0);
	currentFormationLeader = -1;
	formationTemp.formationMovingActive = false;

	formationTemp.pathToTarget.clear();
	formationTemp.placeOnPath = 0;
	formationTemp.leaderTargetReached = false;
	formationTemp.formationMovingActive = false;
	formationTemp.clearData();

	turnBegan = false;

	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].attacker = false;
		playersSquads[index].formationLeader = false;
		playersSquads[index].stopMovement();
	}
}

void Player::playerLateTurnEnd()
{
	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].attacker = false;
		playersSquads[index].formationLeader = false;
		playersSquads[index].pathToTarget.clear();
		playersSquads[index].positionOnPath = 0;
		playersSquads[index].nextPlaceOnPath = sf::Vector2f(0, 0);
		playersSquads[index].stopMovement();
	}

	targetPosition = sf::Vector2f(0, 0);
	currentFormationLeader = -1;
	formationTemp.formationMovingActive = false;

	formationTemp.pathToTarget.clear();
	formationTemp.placeOnPath = 0;
	formationTemp.leaderTargetReached = false;
	formationTemp.formationMovingActive = false;

	turnBegan = false;
}

sf::Vector2f Player::getTargetPosition()
{

	return targetPosition;
	//return playersSquads[squadBeingControlled].targetPosition;
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
		tileForColliding.setPosition(t_pointToCheck);
		if (playersSquads[index].getTroopContainter().getGlobalBounds().contains(t_pointToCheck))
		{
			return index;
		}
	}
	return -1;
}

int Player::getMoney()
{
	return money;
}

void Player::spendMoney(int t_money)
{
	money -= t_money;
}

void Player::addIncomeFromTurn()
{
	money += globalMoneyPerTurn;
	if (playersTowers.size() > 0)
	{
		for (int index = 0; index < playersTowers.size(); index++)
		{
			money += playersTowers[index].getIncome();
		}
	}
}

void Player::checkForDeadSquads()
{
	squadBeingControlled = 0;
	formationCreationAllowed = false;
	std::vector<int> deadSquads;
	for (int index = 0; index < playerSquadsCount; index++)
	{
		//playersSquads[index].attacker = false;
		if (playersSquads[index].getSquadData().health <= 0)
		{
			deadSquads.push_back(index);//get units that are dead in order
		}
		else if (playersSquads[index].needToMove == true)
		{
			playersSquads[index].needToMove = false;
			resetMovedUnitsAfterFight(index);
		}
	}
    for (int index = deadSquads.size() - 1; index >= 0; index--)//go in reverse order and remove units
    {
		eliminateUnit(deadSquads[index]);
    }
}

void Player::resetPlayerForThisTurn()
{	
	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].targetReached = false;
		playersSquads[index].formationActive = false;
		playersSquads[index].formationLeader = false;
		playersSquads[index].targetSet = false;
		playersSquads[index].turnEnded = false;
		playersSquads[index].formationLeaderReachedGoal = false;
		playersSquads[index].resetColour();
		playersSquads[index].stopMovement();
	}
	currentFormationLeader = -1;
	squadBeingControlled = 1;
	formationCreationAllowed = false;
	formationMovementUnlocked = false;
	formationCreated = false;
	turnEnded = false;
	unitsMoved = 0;
	endTurnActive = false;
	turnBegan = false;
	formationTemp.leaderInfoSet = false;
	formationTemp.formationMovingActive = false;
}

void Player::turnFirstCheck()
{
	if (turnBegan == false)
	{
		turnBegan = true;

		targetPosition = sf::Vector2f(0, 0);
		currentFormationLeader = -1;
		formationTemp.formationMovingActive = false;

		formationTemp.pathToTarget.clear();
		formationTemp.placeOnPath = 0;
		formationTemp.leaderTargetReached = false;
		formationTemp.formationMovingActive = false;
	}
}

void Player::passInvalidTiles(std::vector<int> t_invalidTiles)
{
	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].passInvalidTiles(t_invalidTiles);
	}
}
