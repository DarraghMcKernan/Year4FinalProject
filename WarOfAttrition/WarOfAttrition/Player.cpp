#include "Player.h"

void Player::init(int t_teamNum)
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
		playersSquads[index].init(100 + (25*index), startPos, t_teamNum);

		playersSquadsStrenghts.push_back(newText);
		playersSquadsStrenghts[index].setFont(font);
		playersSquadsStrenghts[index].setString(std::to_string(playersSquads[index].getStrength()));
		playersSquadsStrenghts[index].setCharacterSize(100);//increase size and then downscale to prevent blurred text
		playersSquadsStrenghts[index].setFillColor(sf::Color::Black);
		playersSquadsStrenghts[index].setScale(0.2, 0.2);
		playersSquadsStrenghts[index].setPosition((playersSquads[index].getTroopContainter().getPosition().x - playersSquads[index].getTroopContainter().getRadius() / 1.625)
			, (playersSquads[index].getTroopContainter().getPosition().y - playersSquads[index].getTroopContainter().getRadius() / 1.625));
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
			squadSet = true;
			playersSquads[squadBeingControlled].resetColour();
			squadBeingControlled = index;
			playersSquads[index].unlockMovement(true);
			activeTargetTimer = 10;
		}
		playersSquads[index].update(t_deltaTime);
		playersSquadsStrenghts[index].setPosition((playersSquads[index].getTroopContainter().getPosition().x - playersSquads[index].getTroopContainter().getRadius() / 1.625)
			, (playersSquads[index].getTroopContainter().getPosition().y - playersSquads[index].getTroopContainter().getRadius() / 1.625));//used to move the unit strength text with the unit
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || endTurnActive == true)//if space is pressed allow all squads to move
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
}

void Player::render(sf::RenderWindow& t_window)
{
	mousePos = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

	for (int index = 0; index < playerSquadsCount; index++)
	{
		playersSquads[index].render(t_window);
		t_window.draw(playersSquadsStrenghts[index]);
	}
}

void Player::setTargetPosition(int t_cellNum)
{
	squadSet = false;
	targetNeeded = false;

	targetPosition = { (t_cellNum % TILE_COLUMNS) * TILE_SIZE, (t_cellNum / TILE_COLUMNS) * TILE_SIZE };//the tile that the player wants to move to
	targetPosition = { targetPosition.x + (TILE_SIZE / 2) , targetPosition.y + (TILE_SIZE / 2) };//center the target on a tile

	if (playersSquads[squadBeingControlled].movingAllowed() == true)
	{
		playersSquads[squadBeingControlled].setTargetPosition(targetPosition);
	}
}

int Player::collisionCheckerDamage(sf::CircleShape targetToCheck,int t_strength)
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