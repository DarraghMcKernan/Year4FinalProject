#pragma once
#include "globals.h"

class UI
{
public:
	void init();
	void update(sf::Time t_deltaTime);
	void fixedUpdate();
	void render(sf::RenderWindow& t_window,bool t_squadData, bool t_createUnit, bool t_createTower,bool t_upgradeUnit);
	void renderMainMenu(sf::RenderWindow& t_window);
	void renderGameOver(sf::RenderWindow& t_window);
	void handleMouseInteractions();
	void handleButtonInteractions();
	void handleMenuInteractions();
	void setMousePos(sf::Vector2i t_mousePos);
	void updateUnitDataDisplay(SquadData t_squadData);

	bool upgradeMenuOpen = false;
	bool attemptTurnEnd = false;
	bool openCreateUnitMenu = false;
	bool openCreateTowerMenu = false;
	bool createUnitActive = false;
	bool resetPlayerForThisTurn = false;
	bool createGoldTower = false;
	bool createNewUnit = false;
	bool createNewTower = false;
	bool increaseUpgrade = false;
	bool spriteChanged = false;
	int unitTypeToCreate = 0;
	int towerTypeToCreate = 0;
	int cost = 0;
	int upgradeType = 0;
	int clickTimer = 0;
	int customUnitSprite = 0;

	SquadData customSquadData;

	sf::RectangleShape menuStartButton;
	sf::Text framerateText;
	sf::Text playerTurnDisplay;//text to shows whos turn it is
	sf::Text moneyDisplay;
	sf::Text winScreenMessage;
private:
	sf::RectangleShape hudBacking;//a temporary square to hold basic UI
	sf::RectangleShape endTurnButton;//button to allow player to end their turn
	sf::RectangleShape openUnitMenuButton;//button that brings up the menu to create units
	sf::RectangleShape openTowerMenuButton;
	sf::RectangleShape resetTurnButton;//button to reset all unit moves the player made during this turn
	sf::RectangleShape unitMenuBacking;//just a background ui for the buttons to create units
	sf::RectangleShape createTankUnit;//button to create a tank unit
	sf::RectangleShape createPistolUnit;//button to create a pistol unit
	sf::RectangleShape createHeavyTankUnit;
	sf::RectangleShape createHelicopterUnit;
	sf::RectangleShape createCustomUnit;
	sf::RectangleShape createGoldMineTower;
	sf::RectangleShape createUpgradeTower;
	sf::RectangleShape menuBackground;
	sf::RectangleShape unitDataDisplayBacking;

	sf::RectangleShape customUnitSpriteBacking;
	sf::RectangleShape customUnitNextSprite;
	sf::RectangleShape customUnitPreviousSprite;
	sf::RectangleShape customUnitSelectedSprite;

	sf::RectangleShape upgradeUnitMenuBacking;//background for the upgrade menu
	sf::RectangleShape upgradeUnitHealth;
	sf::RectangleShape downgradeUnitHealth;
	sf::RectangleShape upgradeUnitStrength;
	sf::RectangleShape downgradeUnitStrength;
	sf::RectangleShape upgradeUnitSpeed;
	sf::RectangleShape downgradeUnitSpeed;
	sf::RectangleShape upgradeUnitDistance;
	sf::RectangleShape downgradeUnitDistance;
	sf::RectangleShape closeUpgradeMenu;
	
	sf::Sprite tankUnitButtonIcon;
	sf::Sprite pistolUnitButtonIcon;
	sf::Sprite heavyUnitButtonIcon;
	sf::Sprite helicopterUnitButtonIcon;
	sf::Sprite customUnitButtonIcon;
	sf::Sprite goldmineButtonIcon;
	sf::Sprite researchStationButtonIcon;
	sf::Sprite nextSpriteIcon;
	sf::Sprite previousSpriteIcon;
	sf::Sprite currentSpriteIcon;

	sf::Font font;//default font
	
	sf::Text endTurnText;
	sf::Text createUnitText;
	sf::Text createTowerText;
	sf::Text menuStartButtonText;
	sf::Text customUnitText;
	sf::Text upgradeHealthText;
	sf::Text customHealthText;
	sf::Text customStrengthText;
	sf::Text upgradeStrengthText;
	sf::Text upgradeSpeedText;
	sf::Text customSpeedText;
	sf::Text upgradeDistanceText;
	sf::Text customDistanceText;
	sf::Text closeMenuX;
	sf::Text chooseUnitSpriteText;
	sf::Text arrowIconText;
	
	//squad data display
	sf::Text squadStrengthDisplay;
	sf::Text squadTypeDisplay;
	sf::Text squadSpeedDisplay;
	sf::Text squadTeamDisplay;
	sf::Text squadHealthDisplay;
	sf::Text squadDistanceDisplay;

	sf::Vector2f mousePos;

	sf::Sprite moneyIcon;
	sf::Texture moneyIconTexture;
};