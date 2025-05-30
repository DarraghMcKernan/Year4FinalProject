#pragma once
#include "globals.h"
#include "Squad.h"
#include "Tower.h"
#include "FormationManager.h"
#include "Explosion.h"

class Player
{
	Formation formationTemp;
	PositionNormaliser nomaliser;

public:
	//std::vector<Formation> formations;

	void init(int t_teamNum, int t_unitType);
	void update(sf::Time& t_deltaTime);
	void updateMovingTexures(sf::Time& t_deltaTime);
	void fixedUpdate();
	void render(sf::RenderWindow& t_window);
	void setTargetPosition(int t_cellNum);//assign the cell set in worldTile to the squad currently being assigned
	bool checkIfContained(sf::Vector2f t_pointToCheck);//check if given coordinates is on a tile shared by one of the squads
	void attemptEndTurn();
	bool squadDistanceValid(sf::Vector2f t_hoveredTile);
	void generateNewUnit(int t_teamNum, int t_unitType, sf::Vector2f unitSpawnPos);
	void generateNewTower(int t_type, int t_teamNum, sf::Vector2f t_position);
	void eliminateUnit(int t_num);
	void turnActive();
	void dealDamageToUnit(int t_unit, int t_damage);
	int getUnitStrength(int t_unit);
	std::vector<sf::RectangleShape> returnSquadVerticalHitboxes();
	std::vector<sf::RectangleShape> returnSquadHorizontalHitboxes();
	std::vector<SquadData> returnMovedSquadsData();
	sf::Vector2f getFormationTarget();
	sf::Vector2f getFormationStart();
	void givePathToFormation(std::vector<int> t_path);
	void resetMovedUnitsAfterFight(int t_unit);
	void playerLateTurnEnd();
	sf::Vector2f getTargetPosition();

	bool targetNeeded = false;//do we need a target for a squad
	bool arrivedAtTarget = false;//has the squad reached its target
	int movementsPerTurn = 0;//how many units can the player move per turn
	bool turnEnded = false;//used to show that the player has ended their turn
	bool distanceOK = false;
	int squadTargetSet[MAX_MOVES_PER_TURN];
	int unitsMoved = 0;
	bool searchForPath = false;
	bool menuOpen = false;
	bool playerEliminated = false;

	sf::Vector2f getHoveredUnitPos();

	SquadData getSquadData(int t_squadNum);
	void setCustomSquadData(SquadData t_squadData, sf::Vector2f t_unitSpawnPos);
	int getSquadNumHovered(sf::Vector2f t_pointToCheck);
	int getTowerNumHovered(sf::Vector2f t_pointToCheck);

	int getMoney();
	void spendMoney(int t_money);

	void addIncomeFromTurn();

	void checkForDeadSquads();
	void resetPlayerForThisTurn();

	void turnFirstCheck();
	void passInvalidTiles(std::vector<int> t_invalidTiles);
	void upgradeCustomUnit(SquadData t_squadData,int t_selectedSprite);
	void setUnitToFaceEnemy(int t_unit, sf::Vector2f t_enemy);

	bool formationCreationAllowed = false;
	bool formationMovementUnlocked = false;
	int currentFormationLeader = -1;
	int customUnitSprite = 0;
	int unitThatRequestedPath = -1;
	sf::Vector2f requestedUnitPos = {0,0};
	sf::Vector2f requestedUnitTarget = {0,0};
	void givePathToSquad(std::vector<int> t_path);
	std::vector<Squad> playersSquads;//vector to hold the players squads
	std::vector<int> returnAllSquadPositions();
	sf::Vector2f getSquadsPosition(int t_unit);
private:
	std::vector<Explosion> activeExplosions;
	std::vector<Tower> playersTowers;
	std::vector<sf::Text> playersSquadsStrenghts;//used for debugging to display strengths on squads
	std::vector<int> squadsThatMoved;
	sf::Vector2f mousePos;
	sf::Vector2f targetPosition;//position that the squad is to move to
	sf::RectangleShape tileForColliding;//used to check the cell a squad is on regardless of its shape as this will be 1 tile big
	//sf::Text strengthValueText;
	sf::Font font;
	SquadData customUnitData;

	int squadBeingControlled = 1;//which squad is allowed to move
	int playerSquadsCount = 4;//how many squads does player have
	int strength = 100;//how strong is this unit
	int health = 100;
	int activeTargetTimer = 0;//a cooldown to prevent the player from trying to select the tile its on
	int timerForEnd = 0;
	int money = startingMoney - 25;
	int sendLeaderDataCooldown = 0;
	int currentTeam = -1;//which team is this player belongs to

	bool endTurnActive = false;
	bool squadSet = false;
	bool formationCreated = false;
	bool turnBegan = false;
};