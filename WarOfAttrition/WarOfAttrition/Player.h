#pragma once
#include "globals.h"
#include "Squad.h"
#include "Tower.h"


class Player
{
public:
	void init(int t_teamNum, int t_unitType);
	void update(sf::Time& t_deltaTime);
	void fixedUpdate();
	void render(sf::RenderWindow& t_window);
	void setTargetPosition(int t_cellNum);//assign the cell set in worldTile to the squad currently being assigned
	std::vector<int> collisionCheckerDamage(std::vector<sf::RectangleShape> targetToCheck, int t_strength);//return damage dealt if any
	bool checkIfContained(sf::Vector2f t_pointToCheck);//check if given coordinates is on a tile shared by one of the squads
	void attemptEndTurn();
	bool squadDistanceValid(sf::Vector2f t_hoveredTile);
	void generateNewUnit(int t_teamNum, int t_unitType, sf::Vector2f unitSpawnPos);
	void generateNewTower(int t_type, int t_teamNum, sf::Vector2f t_position);
	void eliminateUnit(int t_num);
	void turnActive();
	void dealDamage(std::vector<int> t_damage);
	std::vector<sf::RectangleShape> returnMovedSquads();

	bool targetNeeded = false;//do we need a target for a squad
	bool arrivedAtTarget = false;//has the squad reached its target
	int movementsPerTurn = 0;//how many units can the player move per turn
	bool turnEnded = false;//used to show that the player has ended their turn
	bool distanceOK = false;
	int squadTargetSet[MAX_MOVES_PER_TURN];
	int unitsMoved = 0;

	bool playerEliminated = false;

	sf::Vector2f getSquadPosition();

	SquadData getSquadData(int t_squadNum);
	int getSquadNumHovered(sf::Vector2f t_pointToCheck);

	int getMoney();
	void spendMoney(int t_money);

	void addIncomeFromTurn();
private:
	std::vector<Squad> playersSquads;//vector to hold the players squads
	std::vector<Tower> playersTowers;
	std::vector<sf::Text> playersSquadsStrenghts;//used for debugging to display strengths on squads
	std::vector<int> squadsThatMoved;
	sf::Vector2f mousePos;
	sf::Vector2f targetPosition;//position that the squad is to move to
	sf::RectangleShape tileForColliding;//used to check the cell a squad is on regardless of its shape as this will be 1 tile big
	//sf::Text strengthValueText;
	sf::Font font;


	int squadBeingControlled = 1;//which squad is allowed to move
	int playerSquadsCount = 4;//how many squads does player have
	int strength = 100;//how strong is this unit
	int activeTargetTimer = 0;//a cooldown to prevent the player from trying to select the tile its on
	int timerForEnd = 0;
	int money = 1000;

	bool endTurnActive = false;
	bool squadSet = false;
};