#include "UI.h"

void UI::init()
{
	hudBacking.setSize({ SCREEN_WIDTH,SCREEN_HEIGHT / 5 });//the HUD element that shows player turn
	hudBacking.setOrigin({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 5) });
	hudBacking.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT + (SCREEN_HEIGHT / 5) / 2 });
	hudBacking.setFillColor(sf::Color(200, 200, 200));
	hudBacking.setOutlineColor(sf::Color::Black);
	hudBacking.setOutlineThickness(5);

	endTurnButton.setSize({ hudBacking.getSize().x / 6, hudBacking.getSize().y / 3 });
	endTurnButton.setOrigin({ endTurnButton.getSize().x / 2 ,endTurnButton.getSize().y / 2 });
	endTurnButton.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) / 2 });
	endTurnButton.setFillColor(sf::Color(100, 200, 100));
	endTurnButton.setOutlineColor(sf::Color::Black);
	endTurnButton.setOutlineThickness(3);

	openUnitMenuButton.setSize({ hudBacking.getSize().x / 6, hudBacking.getSize().y / 3 });
	openUnitMenuButton.setOrigin({ openUnitMenuButton.getSize().x / 2 ,openUnitMenuButton.getSize().y / 2 });
	openUnitMenuButton.setPosition({ SCREEN_WIDTH - (SCREEN_WIDTH / 10),SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) / 2 });
	openUnitMenuButton.setFillColor(sf::Color(100, 200, 150));
	openUnitMenuButton.setOutlineColor(sf::Color::Black);
	openUnitMenuButton.setOutlineThickness(3);

	openTowerMenuButton.setSize({ hudBacking.getSize().x / 5.5f, hudBacking.getSize().y / 3 });
	openTowerMenuButton.setOrigin({ openTowerMenuButton.getSize().x / 2 ,openTowerMenuButton.getSize().y / 2 });
	openTowerMenuButton.setPosition({ SCREEN_WIDTH - (SCREEN_WIDTH / 3.5),SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) / 2 });
	openTowerMenuButton.setFillColor(sf::Color(100, 150, 200));
	openTowerMenuButton.setOutlineColor(sf::Color::Black);
	openTowerMenuButton.setOutlineThickness(3);

	resetTurnButton.setSize({ hudBacking.getSize().y / 4, hudBacking.getSize().y / 4 });
	resetTurnButton.setOrigin({ resetTurnButton.getSize().x / 2 ,resetTurnButton.getSize().y / 2 });
	resetTurnButton.setPosition({ (SCREEN_WIDTH / 2.58),SCREEN_HEIGHT - (SCREEN_HEIGHT / 10) / 2 });
	resetTurnButton.setFillColor(sf::Color(200, 100, 100));
	resetTurnButton.setOutlineColor(sf::Color::Black);
	resetTurnButton.setOutlineThickness(3);

	unitMenuBacking.setSize({ SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 });
	unitMenuBacking.setOrigin({ unitMenuBacking.getSize().x / 2 ,unitMenuBacking.getSize().y / 2 });
	unitMenuBacking.setPosition({ SCREEN_WIDTH - (SCREEN_WIDTH / 7),SCREEN_HEIGHT - (SCREEN_HEIGHT / 2.65) });
	unitMenuBacking.setFillColor(sf::Color(125, 125, 125));
	unitMenuBacking.setOutlineColor(sf::Color::Black);
	unitMenuBacking.setOutlineThickness(3);

	createTankUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createTankUnit.setOrigin({ createTankUnit.getSize().x / 2 ,createTankUnit.getSize().y / 2 });
	createTankUnit.setPosition({ unitMenuBacking.getPosition().x - unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createTankUnit.setFillColor(sf::Color(200, 200, 100));
	createTankUnit.setOutlineColor(sf::Color::Black);
	createTankUnit.setOutlineThickness(3);

	createPistolUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createPistolUnit.setOrigin({ createPistolUnit.getSize().x / 2 ,createPistolUnit.getSize().y / 2 });
	createPistolUnit.setPosition({ unitMenuBacking.getPosition().x + unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createPistolUnit.setFillColor(sf::Color(100, 200, 200));
	createPistolUnit.setOutlineColor(sf::Color::Black);
	createPistolUnit.setOutlineThickness(3);

	createHeavyTankUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createHeavyTankUnit.setOrigin({ createHeavyTankUnit.getSize().x / 2 ,createHeavyTankUnit.getSize().y / 2 });
	createHeavyTankUnit.setPosition({ unitMenuBacking.getPosition().x - unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y });
	createHeavyTankUnit.setFillColor(sf::Color(200, 100, 200));
	createHeavyTankUnit.setOutlineColor(sf::Color::Black);
	createHeavyTankUnit.setOutlineThickness(3);

	createHelicopterUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createHelicopterUnit.setOrigin({ createHelicopterUnit.getSize().x / 2 ,createHelicopterUnit.getSize().y / 2 });
	createHelicopterUnit.setPosition({ unitMenuBacking.getPosition().x + unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y });
	createHelicopterUnit.setFillColor(sf::Color(200, 100, 100));
	createHelicopterUnit.setOutlineColor(sf::Color::Black);
	createHelicopterUnit.setOutlineThickness(3);

	createCustomUnit.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createCustomUnit.setOrigin({ createCustomUnit.getSize().x / 2 ,createCustomUnit.getSize().y / 2 });
	createCustomUnit.setPosition({ unitMenuBacking.getPosition().x - unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y + unitMenuBacking.getSize().y / 3 });
	createCustomUnit.setFillColor(sf::Color(100, 100, 200));
	createCustomUnit.setOutlineColor(sf::Color::Black);
	createCustomUnit.setOutlineThickness(3);

	createGoldMineTower.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createGoldMineTower.setOrigin({ createGoldMineTower.getSize().x / 2 ,createGoldMineTower.getSize().y / 2 });
	createGoldMineTower.setPosition({ unitMenuBacking.getPosition().x + unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createGoldMineTower.setFillColor(sf::Color(200, 200, 100));
	createGoldMineTower.setOutlineColor(sf::Color::Black);
	createGoldMineTower.setOutlineThickness(3);

	createUpgradeTower.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createUpgradeTower.setOrigin({ createUpgradeTower.getSize().x / 2 ,createUpgradeTower.getSize().y / 2 });
	createUpgradeTower.setPosition({ unitMenuBacking.getPosition().x - unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createUpgradeTower.setFillColor(sf::Color(200, 100, 200));
	createUpgradeTower.setOutlineColor(sf::Color::Black);
	createUpgradeTower.setOutlineThickness(3);

	menuBackground.setFillColor(sf::Color::Black);
	menuBackground.setSize({ SCREEN_WIDTH - 10,SCREEN_HEIGHT - 10 });
	menuBackground.setOrigin({ menuBackground.getSize().x / 2,menuBackground.getSize().y / 2 });
	menuBackground.setPosition({ (menuBackground.getSize().x / 2) + 5,(menuBackground.getSize().y / 2) + 5 });
	menuBackground.setOutlineColor(sf::Color(200, 200, 100));
	menuBackground.setOutlineThickness(10);

	menuStartButton.setFillColor(sf::Color(200, 200, 200));
	menuStartButton.setSize({ SCREEN_WIDTH / 4,SCREEN_HEIGHT / 10 });
	menuStartButton.setOrigin({ menuStartButton.getSize().x / 2,menuStartButton.getSize().y / 2 });
	menuStartButton.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
	menuStartButton.setOutlineColor(sf::Color(100, 250, 200));
	menuStartButton.setOutlineThickness(3);

	if (!font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "Error loading BebasNeue.otf from file\n";
	}

	playerTurnDisplay.setFont(font);
	playerTurnDisplay.setString("Player " + std::to_string(1) + "'s Turn");
	playerTurnDisplay.setCharacterSize(60);//increase size and then downscale to prevent blurred text
	playerTurnDisplay.setFillColor(sf::Color(0, 0, 255));
	playerTurnDisplay.setOutlineThickness(2);
	playerTurnDisplay.setScale(0.75, 0.75);
	playerTurnDisplay.setOrigin(0, 10);
	playerTurnDisplay.setPosition(SCREEN_WIDTH / 50, SCREEN_HEIGHT - (SCREEN_HEIGHT / 6.5) / 2);

	winScreenMessage.setFont(font);
	winScreenMessage.setString("Player " + std::to_string(1) + "'s Wins!");
	winScreenMessage.setCharacterSize(60);//increase size and then downscale to prevent blurred text
	winScreenMessage.setFillColor(sf::Color(0, 0, 255));
	winScreenMessage.setOutlineThickness(2);
	winScreenMessage.setScale(0.75, 0.75);
	winScreenMessage.setOrigin(winScreenMessage.getGlobalBounds().width / 2, winScreenMessage.getGlobalBounds().height / 2);
	winScreenMessage.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	endTurnText.setFont(font);
	endTurnText.setString("End Turn");
	endTurnText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	endTurnText.setFillColor(sf::Color(0, 0, 0));
	endTurnText.setScale(0.75, 0.75);
	endTurnText.setOrigin({ (endTurnText.getGlobalBounds().getSize().x / 2) + 15,(endTurnText.getGlobalBounds().getSize().y / 2) + 15 });
	endTurnText.setPosition(endTurnButton.getPosition());

	createUnitText.setFont(font);
	createUnitText.setString("Create Unit");
	createUnitText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	createUnitText.setFillColor(sf::Color(0, 0, 0));
	createUnitText.setScale(0.75, 0.75);
	createUnitText.setOrigin({ (endTurnText.getGlobalBounds().getSize().x / 2) + 40,(endTurnText.getGlobalBounds().getSize().y / 2) + 15 });
	createUnitText.setPosition(openUnitMenuButton.getPosition());

	createTowerText.setFont(font);
	createTowerText.setString("Create Tower");
	createTowerText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	createTowerText.setFillColor(sf::Color(0, 0, 0));
	createTowerText.setScale(0.75, 0.75);
	createTowerText.setOrigin({ (createTowerText.getGlobalBounds().getSize().x / 2) + 29,(createTowerText.getGlobalBounds().getSize().y / 2) + 15 });
	createTowerText.setPosition(openTowerMenuButton.getPosition());

	menuStartButtonText.setFont(font);
	menuStartButtonText.setString("Start Game");
	menuStartButtonText.setCharacterSize(70);//increase size and then downscale to prevent blurred text
	menuStartButtonText.setFillColor(sf::Color::Black);
	menuStartButtonText.setScale(0.75, 0.75);
	menuStartButtonText.setOrigin({ (menuStartButtonText.getGlobalBounds().getSize().x / 2) + 30,(menuStartButtonText.getGlobalBounds().getSize().y / 2) + 22 });
	menuStartButtonText.setPosition(menuStartButton.getPosition());

	squadSpeedDisplay.setFont(font);
	squadSpeedDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadSpeedDisplay.setFillColor(sf::Color::Black);
	squadSpeedDisplay.setScale(0.75, 0.75);
	squadSpeedDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadSpeedDisplay.setPosition(50, 90);

	squadStrengthDisplay.setFont(font);
	squadStrengthDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadStrengthDisplay.setFillColor(sf::Color::Black);
	squadStrengthDisplay.setScale(0.75, 0.75);
	squadStrengthDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadStrengthDisplay.setPosition(50, 110);

	squadTeamDisplay.setFont(font);
	squadTeamDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadTeamDisplay.setFillColor(sf::Color::Black);
	squadTeamDisplay.setScale(0.75, 0.75);
	squadTeamDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadTeamDisplay.setPosition(50, 130);

	squadDistanceDisplay.setFont(font);
	squadDistanceDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadDistanceDisplay.setFillColor(sf::Color::Black);
	squadDistanceDisplay.setScale(0.75, 0.75);
	squadDistanceDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadDistanceDisplay.setPosition(50, 150);

	squadTypeDisplay.setFont(font);
	squadTypeDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadTypeDisplay.setFillColor(sf::Color::Black);
	squadTypeDisplay.setScale(0.75, 0.75);
	squadTypeDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadTypeDisplay.setPosition(50, 150);

	squadHealthDisplay.setFont(font);
	squadHealthDisplay.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	squadHealthDisplay.setFillColor(sf::Color::Black);
	squadHealthDisplay.setScale(0.75, 0.75);
	squadHealthDisplay.setOrigin({ (squadSpeedDisplay.getGlobalBounds().getSize().x / 2),(squadSpeedDisplay.getGlobalBounds().getSize().y / 2) });
	squadHealthDisplay.setPosition(50, 170);

	unitDataDisplayBacking.setSize({ SCREEN_WIDTH / 3,SCREEN_HEIGHT / 5 });
	unitDataDisplayBacking.setOrigin({ unitDataDisplayBacking.getSize().x / 2 ,unitDataDisplayBacking.getSize().y / 2 });
	unitDataDisplayBacking.setPosition({ SCREEN_WIDTH / 5,SCREEN_HEIGHT / 5 });
	unitDataDisplayBacking.setFillColor(sf::Color(200, 200, 200));
	unitDataDisplayBacking.setOutlineThickness(6);
	unitDataDisplayBacking.setOutlineColor(sf::Color::Black);

	moneyDisplay.setFont(font);
	moneyDisplay.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	moneyDisplay.setFillColor(sf::Color::Black);
	moneyDisplay.setScale(0.75, 0.75);
	moneyDisplay.setOrigin({ (moneyDisplay.getGlobalBounds().getSize().x / 2),(moneyDisplay.getGlobalBounds().getSize().y / 2) });
	moneyDisplay.setPosition((SCREEN_WIDTH / 2) - SCREEN_WIDTH / 5, SCREEN_HEIGHT - (SCREEN_HEIGHT / 12.5));
	moneyDisplay.setString(std::to_string(1000));

	if (!moneyIconTexture.loadFromFile("ASSETS/MoneyIcon.png"))
	{
		std::cout << "Error loading moneyIcon from file\n";
	}
	moneyIcon.setTexture(moneyIconTexture);
	moneyIcon.setOrigin(moneyIcon.getGlobalBounds().width / 2, moneyIcon.getGlobalBounds().height / 2);
	moneyIcon.setPosition((SCREEN_WIDTH / 2) - SCREEN_WIDTH / 4.5, SCREEN_HEIGHT - (SCREEN_HEIGHT / 20));
	moneyIcon.setScale(3, 3);

	framerateText.setFont(font);

	upgradeUnitMenuBacking.setSize({ SCREEN_WIDTH/3,SCREEN_HEIGHT / 2 });//the HUD element that shows player turn
	upgradeUnitMenuBacking.setOrigin({ upgradeUnitMenuBacking.getSize().x / 2,upgradeUnitMenuBacking.getSize().y / 2 });
	upgradeUnitMenuBacking.setPosition({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 2) - (SCREEN_WIDTH / 8) });
	upgradeUnitMenuBacking.setFillColor(sf::Color(200, 200, 200));
	upgradeUnitMenuBacking.setOutlineColor(sf::Color::Black);
	upgradeUnitMenuBacking.setOutlineThickness(5);

	float upgradeMenuX = upgradeUnitMenuBacking.getGlobalBounds().getSize().x;
	float upgradeMenuY = upgradeUnitMenuBacking.getGlobalBounds().getSize().y;

	upgradeUnitHealth.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	upgradeUnitHealth.setOrigin({ upgradeUnitHealth.getSize().x / 2,upgradeUnitHealth.getSize().y / 2 });
	upgradeUnitHealth.setPosition({(SCREEN_WIDTH / 2) + (upgradeMenuX / 3),upgradeUnitMenuBacking.getPosition().y - (upgradeMenuY/3.5f)});
	upgradeUnitHealth.setFillColor(sf::Color(0, 200, 0));
	upgradeUnitHealth.setOutlineColor(sf::Color::Black);
	upgradeUnitHealth.setOutlineThickness(3);

	downgradeUnitHealth.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	downgradeUnitHealth.setOrigin({ downgradeUnitHealth.getSize().x / 2,downgradeUnitHealth.getSize().y / 2 });
	downgradeUnitHealth.setPosition({ (SCREEN_WIDTH / 2) - (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 3.5f) });
	downgradeUnitHealth.setFillColor(sf::Color(200, 0, 0));
	downgradeUnitHealth.setOutlineColor(sf::Color::Black);
	downgradeUnitHealth.setOutlineThickness(3);

	upgradeUnitStrength.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	upgradeUnitStrength.setOrigin({ upgradeUnitStrength.getSize().x / 2,upgradeUnitStrength.getSize().y / 2 });
	upgradeUnitStrength.setPosition({ (SCREEN_WIDTH / 2) + (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 13.0f) });
	upgradeUnitStrength.setFillColor(sf::Color(0, 200, 0));
	upgradeUnitStrength.setOutlineColor(sf::Color::Black);
	upgradeUnitStrength.setOutlineThickness(3);

	downgradeUnitStrength.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	downgradeUnitStrength.setOrigin({ downgradeUnitStrength.getSize().x / 2,downgradeUnitStrength.getSize().y / 2 });
	downgradeUnitStrength.setPosition({ (SCREEN_WIDTH / 2) - (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 13.0f) });
	downgradeUnitStrength.setFillColor(sf::Color(200, 0, 0));
	downgradeUnitStrength.setOutlineColor(sf::Color::Black);
	downgradeUnitStrength.setOutlineThickness(3);

	upgradeUnitSpeed.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	upgradeUnitSpeed.setOrigin({ upgradeUnitSpeed.getSize().x / 2,upgradeUnitSpeed.getSize().y / 2 });
	upgradeUnitSpeed.setPosition({ (SCREEN_WIDTH / 2) + (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 7.0f) });
	upgradeUnitSpeed.setFillColor(sf::Color(0, 200, 0));
	upgradeUnitSpeed.setOutlineColor(sf::Color::Black);
	upgradeUnitSpeed.setOutlineThickness(3);

	downgradeUnitSpeed.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	downgradeUnitSpeed.setOrigin({ downgradeUnitSpeed.getSize().x / 2,downgradeUnitSpeed.getSize().y / 2 });
	downgradeUnitSpeed.setPosition({ (SCREEN_WIDTH / 2) - (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 7.0f) });
	downgradeUnitSpeed.setFillColor(sf::Color(200, 0, 0));
	downgradeUnitSpeed.setOutlineColor(sf::Color::Black);
	downgradeUnitSpeed.setOutlineThickness(3);

	upgradeUnitDistance.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	upgradeUnitDistance.setOrigin({ upgradeUnitDistance.getSize().x / 2,upgradeUnitDistance.getSize().y / 2 });
	upgradeUnitDistance.setPosition({ (SCREEN_WIDTH / 2) + (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 2.8f) });
	upgradeUnitDistance.setFillColor(sf::Color(0, 200, 0));
	upgradeUnitDistance.setOutlineColor(sf::Color::Black);
	upgradeUnitDistance.setOutlineThickness(3);

	downgradeUnitDistance.setSize({ SCREEN_WIDTH / 20, SCREEN_HEIGHT / 16 });
	downgradeUnitDistance.setOrigin({ downgradeUnitDistance.getSize().x / 2,downgradeUnitDistance.getSize().y / 2 });
	downgradeUnitDistance.setPosition({ (SCREEN_WIDTH / 2) - (upgradeMenuX / 3),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 2.8f) });
	downgradeUnitDistance.setFillColor(sf::Color(200, 0, 0));
	downgradeUnitDistance.setOutlineColor(sf::Color::Black);
	downgradeUnitDistance.setOutlineThickness(3);

	closeUpgradeMenu.setSize({ SCREEN_WIDTH / 40, SCREEN_HEIGHT / 32 });
	closeUpgradeMenu.setOrigin({ closeUpgradeMenu.getSize().x / 2,closeUpgradeMenu.getSize().y / 2 });
	closeUpgradeMenu.setPosition({ (SCREEN_WIDTH / 2) - (upgradeMenuX / 2.3f),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 2.25f) });
	closeUpgradeMenu.setFillColor(sf::Color(255, 0, 0));
	closeUpgradeMenu.setOutlineColor(sf::Color::Black);
	closeUpgradeMenu.setOutlineThickness(2.5f);

	customUnitText.setFont(font);
	customUnitText.setString("Upgrade Custom Unit");
	customUnitText.setCharacterSize(50);//increase size and then downscale to prevent blurred text
	customUnitText.setFillColor(sf::Color(0, 0, 0));
	customUnitText.setScale(0.75, 0.75);
	customUnitText.setOrigin({ (customUnitText.getGlobalBounds().getSize().x / 2) + 40,(customUnitText.getGlobalBounds().getSize().y / 2) });
	customUnitText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 2.15f) });
	customUnitText.setStyle(customUnitText.Underlined);

	upgradeHealthText.setFont(font);
	upgradeHealthText.setString("Upgrade Health");
	upgradeHealthText.setCharacterSize(35);//increase size and then downscale to prevent blurred text
	upgradeHealthText.setFillColor(sf::Color(0, 0, 0));
	upgradeHealthText.setScale(0.75, 0.75);
	upgradeHealthText.setOrigin({ (upgradeHealthText.getGlobalBounds().getSize().x / 2) + 25,(upgradeHealthText.getGlobalBounds().getSize().y/2)});
	upgradeHealthText.setPosition({(SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 2.85f)});

	upgradeStrengthText.setFont(font);
	upgradeStrengthText.setString("Upgrade Damage");
	upgradeStrengthText.setCharacterSize(35);//increase size and then downscale to prevent blurred text
	upgradeStrengthText.setFillColor(sf::Color(0, 0, 0));
	upgradeStrengthText.setScale(0.75, 0.75);
	upgradeStrengthText.setOrigin({ (upgradeStrengthText.getGlobalBounds().getSize().x / 2) + 25,(upgradeStrengthText.getGlobalBounds().getSize().y / 2) });
	upgradeStrengthText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 7.f) });

	upgradeSpeedText.setFont(font);
	upgradeSpeedText.setString("Upgrade Damage");
	upgradeSpeedText.setCharacterSize(35);//increase size and then downscale to prevent blurred text
	upgradeSpeedText.setFillColor(sf::Color(0, 0, 0));
	upgradeSpeedText.setScale(0.75, 0.75);
	upgradeSpeedText.setOrigin({ (upgradeSpeedText.getGlobalBounds().getSize().x / 2) + 22,(upgradeSpeedText.getGlobalBounds().getSize().y / 2) });
	upgradeSpeedText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 12.f) });

	upgradeDistanceText.setFont(font);
	upgradeDistanceText.setString("Upgrade Distance");
	upgradeDistanceText.setCharacterSize(35);//increase size and then downscale to prevent blurred text
	upgradeDistanceText.setFillColor(sf::Color(0, 0, 0));
	upgradeDistanceText.setScale(0.75, 0.75);
	upgradeDistanceText.setOrigin({ (upgradeSpeedText.getGlobalBounds().getSize().x / 2) + 28,(upgradeSpeedText.getGlobalBounds().getSize().y / 2) });
	upgradeDistanceText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 3.4f) });

	customHealthText.setFont(font);
	customHealthText.setCharacterSize(40);//increase size and then downscale to prevent blurred text
	customHealthText.setFillColor(sf::Color::Black);
	customHealthText.setScale(0.75, 0.75);
	customHealthText.setString(std::to_string(customSquadData.health));
	customHealthText.setOrigin({ (customHealthText.getGlobalBounds().getSize().x / 2) + 10,(customHealthText.getGlobalBounds().getSize().y / 2) });
	customHealthText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 3.5f)});

	customStrengthText.setFont(font);
	customStrengthText.setCharacterSize(40);//increase size and then downscale to prevent blurred text
	customStrengthText.setFillColor(sf::Color::Black);
	customStrengthText.setScale(0.75, 0.75);
	customStrengthText.setString(std::to_string(customSquadData.squadStrength));
	customStrengthText.setOrigin({ (customStrengthText.getGlobalBounds().getSize().x / 2) + 10,(customStrengthText.getGlobalBounds().getSize().y / 2) });
	customStrengthText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 13.f) });

	customSpeedText.setFont(font);
	customSpeedText.setCharacterSize(40);//increase size and then downscale to prevent blurred text
	customSpeedText.setFillColor(sf::Color::Black);
	customSpeedText.setScale(0.75, 0.75);
	customSpeedText.setString(std::to_string(customSquadData.moveSpeed));
	customSpeedText.setOrigin({ (customSpeedText.getGlobalBounds().getSize().x / 2) + 10,(customSpeedText.getGlobalBounds().getSize().y / 2) });
	customSpeedText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 6.8f) });

	customDistanceText.setFont(font);
	customDistanceText.setCharacterSize(40);//increase size and then downscale to prevent blurred text
	customDistanceText.setFillColor(sf::Color::Black);
	customDistanceText.setScale(0.75, 0.75);
	customDistanceText.setString(std::to_string(customSquadData.moveDistance));
	customDistanceText.setOrigin({ (customDistanceText.getGlobalBounds().getSize().x / 2) + 7.5f,(customDistanceText.getGlobalBounds().getSize().y / 2) });
	customDistanceText.setPosition({ (SCREEN_WIDTH / 2),(upgradeUnitMenuBacking.getPosition().y) + (upgradeMenuY / 2.8f) });

	closeMenuX.setFont(font);
	closeMenuX.setCharacterSize(40);//increase size and then downscale to prevent blurred text
	closeMenuX.setFillColor(sf::Color::Black);
	closeMenuX.setScale(1.2, 0.75);
	closeMenuX.setString("X");
	closeMenuX.setOrigin({ (closeMenuX.getGlobalBounds().getSize().x / 2) - 2.0f,(closeMenuX.getGlobalBounds().getSize().y / 2) + 15.0f });
	closeMenuX.setPosition({ (SCREEN_WIDTH / 2) - (upgradeMenuX / 2.3f),(upgradeUnitMenuBacking.getPosition().y) - (upgradeMenuY / 2.25f) });

	chooseUnitSpriteText.setFont(font);
	chooseUnitSpriteText.setCharacterSize(30);//increase size and then downscale to prevent blurred text
	chooseUnitSpriteText.setFillColor(sf::Color::Black);
	chooseUnitSpriteText.setScale(1, 1);
	chooseUnitSpriteText.setString("Change Custom Unit Sprite");
	chooseUnitSpriteText.setOrigin({ (chooseUnitSpriteText.getGlobalBounds().getSize().x / 2),(chooseUnitSpriteText.getGlobalBounds().getSize().y / 2)});
	chooseUnitSpriteText.setPosition({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 2) + (SCREEN_WIDTH / 12) });

	arrowIconText.setFont(font);
	arrowIconText.setCharacterSize(100);//increase size and then downscale to prevent blurred text
	arrowIconText.setFillColor(sf::Color::Black);
	arrowIconText.setScale(1, 1);
	arrowIconText.setString("<       >");
	arrowIconText.setOrigin({ (arrowIconText.getGlobalBounds().getSize().x / 2),(arrowIconText.getGlobalBounds().getSize().y / 2) });
	arrowIconText.setPosition({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 2) + (SCREEN_WIDTH / 8.6f) });

	customUnitSpriteBacking.setSize({ SCREEN_WIDTH / 2.5,SCREEN_HEIGHT / 6 });//
	customUnitSpriteBacking.setOrigin({ customUnitSpriteBacking.getSize().x / 2,customUnitSpriteBacking.getSize().y / 2 });
	customUnitSpriteBacking.setPosition({ SCREEN_WIDTH / 2,(SCREEN_HEIGHT / 2) + (SCREEN_WIDTH / 7) });
	customUnitSpriteBacking.setFillColor(sf::Color(200, 200, 200));
	customUnitSpriteBacking.setOutlineColor(sf::Color::Black);
	customUnitSpriteBacking.setOutlineThickness(5);

	customUnitNextSprite.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	customUnitNextSprite.setOrigin({ customUnitNextSprite.getSize().x / 2,customUnitNextSprite.getSize().y / 2 });
	customUnitNextSprite.setPosition({ (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 7),(SCREEN_HEIGHT / 2) + (SCREEN_WIDTH / 6.5f) });
	customUnitNextSprite.setFillColor(sf::Color(100, 100, 200));
	customUnitNextSprite.setOutlineColor(sf::Color::Black);
	customUnitNextSprite.setOutlineThickness(3);

	customUnitPreviousSprite.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	customUnitPreviousSprite.setOrigin({ customUnitPreviousSprite.getSize().x / 2,customUnitPreviousSprite.getSize().y / 2 });
	customUnitPreviousSprite.setPosition({ (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 7),(SCREEN_HEIGHT / 2) + (SCREEN_WIDTH / 6.5f) });
	customUnitPreviousSprite.setFillColor(sf::Color(100, 100, 200));
	customUnitPreviousSprite.setOutlineColor(sf::Color::Black);
	customUnitPreviousSprite.setOutlineThickness(3);

	customUnitSelectedSprite.setSize({ SCREEN_WIDTH / (15 * 0.8f), SCREEN_HEIGHT / (12*0.8f) });
	customUnitSelectedSprite.setOrigin({ customUnitSelectedSprite.getSize().x / 2,customUnitSelectedSprite.getSize().y / 2 });
	customUnitSelectedSprite.setPosition({ (SCREEN_WIDTH / 2),(SCREEN_HEIGHT / 2) + (SCREEN_WIDTH / 6.5f) });
	customUnitSelectedSprite.setFillColor(sf::Color(100, 200, 100));
	customUnitSelectedSprite.setOutlineColor(sf::Color::Black);
	customUnitSelectedSprite.setOutlineThickness(3);

	if (!customTankTexture.loadFromFile("ASSETS/CustomACS.png"))
	{
		std::cout << "error loading custom tank texture";
	}
	if (!customCarTexture.loadFromFile("ASSETS/CustomHumvee.png"))
	{
		std::cout << "error loading custom car texture";
	}
	if (!customHeavyTankTexture.loadFromFile("ASSETS/CustomBTRModified.png"))
	{
		std::cout << "error loading custom tank heavy texture";
	}

	currentSpriteIcon.setTexture(customTankTexture);
	currentSpriteIcon.setOrigin(currentSpriteIcon.getTextureRect().getSize().x / 2, currentSpriteIcon.getTextureRect().getSize().y / 2);
	currentSpriteIcon.setPosition(customUnitSelectedSprite.getPosition());
	currentSpriteIcon.setScale(0.7f, 0.7f);

	nextSpriteIcon.setTexture(customCarTexture);
	nextSpriteIcon.setOrigin(nextSpriteIcon.getTextureRect().getSize().x / 2, nextSpriteIcon.getTextureRect().getSize().y / 2);
	nextSpriteIcon.setPosition(customUnitNextSprite.getPosition());
	nextSpriteIcon.setScale(0.6f, 0.6f);

	previousSpriteIcon.setTexture(customHeavyTankTexture);
	previousSpriteIcon.setOrigin(previousSpriteIcon.getTextureRect().getSize().x / 2, previousSpriteIcon.getTextureRect().getSize().y / 2);
	previousSpriteIcon.setPosition(customUnitPreviousSprite.getPosition());
	previousSpriteIcon.setScale(0.6f, 0.6f);


	if (!tankTexture.loadFromFile("ASSETS/ACS_Preview.png"))
	{
		std::cout << "error loading squad texture";
	}
	tankUnitButtonIcon.setTexture(tankTexture);
	tankUnitButtonIcon.setOrigin(tankUnitButtonIcon.getGlobalBounds().getSize().x / 2, tankUnitButtonIcon.getGlobalBounds().getSize().y / 2);
	tankUnitButtonIcon.setPosition(createTankUnit.getPosition());
	tankUnitButtonIcon.setScale(0.5f, 0.5f);
	
	if (!infantryTexture.loadFromFile("ASSETS/Hero_Pistol.png"))
	{
		std::cout << "error loading Pistol Unit texture";
	}
	pistolUnitButtonIcon.setTexture(infantryTexture);
	pistolUnitButtonIcon.setOrigin(pistolUnitButtonIcon.getGlobalBounds().getSize().x / 2, (pistolUnitButtonIcon.getGlobalBounds().getSize().y / 2) + 4);
	pistolUnitButtonIcon.setPosition(createPistolUnit.getPosition());
	pistolUnitButtonIcon.setScale(1.5f, 1.5f);

	if (!BTRTexture.loadFromFile("ASSETS/BTR_Fixed.png"))
	{
		std::cout << "error loading heavy tank texture";
	}
	heavyUnitButtonIcon.setTexture(BTRTexture);
	heavyUnitButtonIcon.setOrigin(heavyUnitButtonIcon.getGlobalBounds().getSize().x / 2, (heavyUnitButtonIcon.getGlobalBounds().getSize().y / 2) + 4);
	heavyUnitButtonIcon.setPosition(createHeavyTankUnit.getPosition());
	heavyUnitButtonIcon.setScale(0.6f, 0.6f);

	if (!HelicopterPreviewTexture.loadFromFile("ASSETS/Helicopter_Preview.png"))
	{
		std::cout << "error loading helicopter preview texture";
	}
	helicopterUnitButtonIcon.setTexture(HelicopterPreviewTexture);
	helicopterUnitButtonIcon.setOrigin(helicopterUnitButtonIcon.getGlobalBounds().getSize().x / 2, (helicopterUnitButtonIcon.getGlobalBounds().getSize().y / 2) + 4);
	helicopterUnitButtonIcon.setPosition(createHelicopterUnit.getPosition());
	helicopterUnitButtonIcon.setScale(0.3f, 0.3f);
	helicopterUnitButtonIcon.setRotation(45);

	if (!researchBuildingTexture.loadFromFile("ASSETS/researchBuilding.png"))
	{
		std::cout << "error loading researchBuilding texture";
	}
	researchStationButtonIcon.setTexture(researchBuildingTexture);
	researchStationButtonIcon.setOrigin(researchStationButtonIcon.getGlobalBounds().getSize().x / 2, (researchStationButtonIcon.getGlobalBounds().getSize().y / 2));
	researchStationButtonIcon.setPosition(createUpgradeTower.getPosition());
	researchStationButtonIcon.setScale(1.2f, 1.2f);

	if (!goldmineTexture.loadFromFile("ASSETS/GoldMine.png"))
	{
		std::cout << "error loading gold mine texture";
	}
	goldmineButtonIcon.setTexture(goldmineTexture);
	goldmineButtonIcon.setOrigin(goldmineButtonIcon.getGlobalBounds().getSize().x / 2, (goldmineButtonIcon.getGlobalBounds().getSize().y / 2));
	goldmineButtonIcon.setPosition(createGoldMineTower.getPosition());
	goldmineButtonIcon.setScale(0.3f, 0.3f);

	customSquadData.health = 100;
	customSquadData.moveDistance = 5;
	customSquadData.moveSpeed = 100;
	customSquadData.squadStrength = 100;
	customSquadData.teamNum = 0;
	customSquadData.unitType = 3;
}

void UI::update(sf::Time t_deltaTime)
{

}

void UI::fixedUpdate()
{
	if (spriteChanged == true)
	{
		if (customUnitSprite == 0)
		{
			currentSpriteIcon.setPosition(customUnitSelectedSprite.getPosition());
			currentSpriteIcon.setScale(0.7f, 0.7f);

			nextSpriteIcon.setPosition(customUnitNextSprite.getPosition());
			nextSpriteIcon.setScale(0.6f, 0.6f);

			previousSpriteIcon.setPosition(customUnitPreviousSprite.getPosition());
			previousSpriteIcon.setScale(0.6f, 0.6f);
		}
		if (customUnitSprite == 1)
		{
			currentSpriteIcon.setPosition(customUnitPreviousSprite.getPosition());
			currentSpriteIcon.setScale(0.5f, 0.5f);

			nextSpriteIcon.setPosition(customUnitSelectedSprite.getPosition());
			nextSpriteIcon.setScale(0.7f, 0.7f);

			previousSpriteIcon.setPosition(customUnitNextSprite.getPosition());
			previousSpriteIcon.setScale(0.6f, 0.6f);
		}
		if (customUnitSprite == 2)
		{
			currentSpriteIcon.setPosition(customUnitNextSprite.getPosition());
			currentSpriteIcon.setScale(0.5f, 0.5f);

			nextSpriteIcon.setPosition(customUnitPreviousSprite.getPosition());
			nextSpriteIcon.setScale(0.6f, 0.6f);

			previousSpriteIcon.setPosition(customUnitSelectedSprite.getPosition());
			previousSpriteIcon.setScale(0.7f, 0.7f);
		}

		spriteChanged = false;
	}
}

void UI::render(sf::RenderWindow& t_window, bool t_squadData, bool t_createUnit, bool t_createTower,bool t_upgradeUnit)
{
	t_window.draw(hudBacking);
	t_window.draw(endTurnButton);
	t_window.draw(openUnitMenuButton);
	t_window.draw(openTowerMenuButton);
	t_window.draw(resetTurnButton);
	t_window.draw(playerTurnDisplay);
	t_window.draw(endTurnText);
	t_window.draw(createUnitText);
	t_window.draw(createTowerText);
	t_window.draw(moneyDisplay);
	t_window.draw(moneyIcon);
	t_window.draw(framerateText);

	if (t_squadData == true && upgradeMenuOpen == false)
	{
		t_window.draw(unitDataDisplayBacking);
		t_window.draw(squadSpeedDisplay);
		t_window.draw(squadStrengthDisplay);
		t_window.draw(squadTypeDisplay);
		t_window.draw(squadHealthDisplay);
		t_window.draw(squadTeamDisplay);
		t_window.draw(squadDistanceDisplay);
	}

	if (t_createUnit == true)
	{
		t_window.draw(unitMenuBacking);
		t_window.draw(createTankUnit);
		t_window.draw(tankUnitButtonIcon);
		t_window.draw(createPistolUnit);
		t_window.draw(pistolUnitButtonIcon);
		t_window.draw(createHeavyTankUnit);
		t_window.draw(heavyUnitButtonIcon);
		t_window.draw(createHelicopterUnit);
		t_window.draw(helicopterUnitButtonIcon);
		t_window.draw(createCustomUnit);
	}
	if (t_createTower == true)
	{
		t_window.draw(unitMenuBacking);
		t_window.draw(createGoldMineTower);
		t_window.draw(goldmineButtonIcon);
		t_window.draw(createUpgradeTower);
		t_window.draw(researchStationButtonIcon);
	}
	if (t_upgradeUnit == true)
	{
		t_window.draw(upgradeUnitMenuBacking);
		t_window.draw(upgradeUnitHealth);
		t_window.draw(downgradeUnitHealth);
		t_window.draw(upgradeUnitStrength);
		t_window.draw(downgradeUnitStrength);
		t_window.draw(upgradeUnitSpeed);
		t_window.draw(downgradeUnitSpeed);
		t_window.draw(upgradeUnitDistance);
		t_window.draw(downgradeUnitDistance);
		t_window.draw(closeUpgradeMenu);
		t_window.draw(customUnitSpriteBacking);
		t_window.draw(customUnitNextSprite);
		t_window.draw(customUnitPreviousSprite);
		t_window.draw(customUnitSelectedSprite);
		t_window.draw(currentSpriteIcon);
		t_window.draw(nextSpriteIcon);
		t_window.draw(previousSpriteIcon);

		t_window.draw(customHealthText);
		t_window.draw(customStrengthText);
		t_window.draw(customSpeedText);
		t_window.draw(customDistanceText);
		t_window.draw(closeMenuX);
		t_window.draw(chooseUnitSpriteText);
		t_window.draw(arrowIconText);

		t_window.draw(customUnitText);
		t_window.draw(upgradeHealthText);
		t_window.draw(upgradeStrengthText);
		t_window.draw(upgradeDistanceText);
		t_window.draw(upgradeSpeedText);
	}
	upgradeMenuOpen = t_upgradeUnit;
}

void UI::renderMainMenu(sf::RenderWindow& t_window)
{
	t_window.draw(menuBackground);
	t_window.draw(menuStartButton);
	t_window.draw(menuStartButtonText);
}

void UI::renderGameOver(sf::RenderWindow& t_window)
{
	t_window.draw(menuBackground);
	t_window.draw(winScreenMessage);
}

void UI::handleMouseInteractions()
{

}

void UI::handleButtonInteractions()
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && clickTimer == 0)
	//{
	//	upgradeMenuOpen = !upgradeMenuOpen;
	//	clickTimer = 30;
	//}
}

void UI::handleMenuInteractions()
{
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && endTurnButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickTimer == 0)
	{
		attemptTurnEnd = true;
		endTurnButton.setFillColor(sf::Color(100, 150, 100));
		clickTimer = 30;
		openCreateTowerMenu = false;
		openCreateUnitMenu = false;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openUnitMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == false && clickTimer == 0)
	{
		openUnitMenuButton.setFillColor(sf::Color(100, 150, 100));
		clickTimer = 30;
		if (openCreateTowerMenu == false)
		{
			openCreateUnitMenu = true;
			openCreateTowerMenu = false;
		}
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openUnitMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		openUnitMenuButton.setFillColor(sf::Color(100, 150, 100));
		clickTimer = 30;
		openCreateUnitMenu = false;
		createUnitActive = false;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openTowerMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == false && clickTimer == 0)
	{
		openTowerMenuButton.setFillColor(sf::Color(100, 100, 150));
		clickTimer = 30;
		if (openCreateUnitMenu == false)
		{
			openCreateTowerMenu = true;
			openCreateUnitMenu = false;
		}
		
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openTowerMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == true && clickTimer == 0)
	{
		openTowerMenuButton.setFillColor(sf::Color(100, 100, 150));
		clickTimer = 30;
		openCreateTowerMenu = false;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && resetTurnButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && clickTimer == 0)
	{
		resetTurnButton.setFillColor(sf::Color(150, 50, 50));
		clickTimer = 30;
		resetPlayerForThisTurn = true;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createTankUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createTankUnit.setFillColor(sf::Color(150, 150, 100));
		createUnitActive = true;
		unitTypeToCreate = 0;
		cost = 250;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createPistolUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createPistolUnit.setFillColor(sf::Color(100, 150, 150));
		createUnitActive = true;
		unitTypeToCreate = 1;
		cost = 100;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createHeavyTankUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createHeavyTankUnit.setFillColor(sf::Color(150, 100, 150));
		createUnitActive = true;
		unitTypeToCreate = 2;
		cost = 600;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createHelicopterUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createHelicopterUnit.setFillColor(sf::Color(150, 100, 100));
		createUnitActive = true;
		unitTypeToCreate = 3;
		cost = 800;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createCustomUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createCustomUnit.setFillColor(sf::Color(100, 100, 150));
		createUnitActive = true;
		unitTypeToCreate = 4;
		cost = 500;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createGoldMineTower.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == true && clickTimer == 0)
	{
		createGoldTower = true;
		clickTimer = 30;
		createGoldMineTower.setFillColor(sf::Color(150, 150, 100));
		cost = 750;
		towerTypeToCreate = 0;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createUpgradeTower.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == true && clickTimer == 0)
	{
		createGoldTower = true;
		clickTimer = 30;
		cost = 1000;
		createUpgradeTower.setFillColor(sf::Color(150, 100, 150));
		towerTypeToCreate = 1;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && createUnitActive == true && clickTimer == 0)
	{
		createNewUnit = true;
		clickTimer = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && createGoldTower == true && clickTimer == 0)
	{
		createNewTower = true;
		clickTimer = 30;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && upgradeUnitHealth.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.health += 25;
		customHealthText.setString(std::to_string(customSquadData.health));
		clickTimer = 30;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && downgradeUnitHealth.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.health -= 25;
		if (customSquadData.health <= 25)
		{
			customSquadData.health = 25;
		}
		customHealthText.setString(std::to_string(customSquadData.health));
		clickTimer = 30;
	}


	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && upgradeUnitStrength.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.squadStrength += 25;
		customStrengthText.setString(std::to_string(customSquadData.squadStrength));
		clickTimer = 30;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && downgradeUnitStrength.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.squadStrength -= 25;
		if (customSquadData.squadStrength <= 25)
		{
			customSquadData.squadStrength = 25;
		}
		customStrengthText.setString(std::to_string(customSquadData.squadStrength));
		clickTimer = 30;
	}


	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && upgradeUnitSpeed.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.moveSpeed += 25;
		customSpeedText.setString(std::to_string(customSquadData.moveSpeed));
		clickTimer = 30;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && downgradeUnitSpeed.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.moveSpeed -= 25;
		if (customSquadData.moveSpeed <= 25)
		{
			customSquadData.moveSpeed = 25;
		}
		customSpeedText.setString(std::to_string(customSquadData.moveSpeed));
		clickTimer = 30;
	}


	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && upgradeUnitDistance.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.moveDistance += 1;
		customDistanceText.setString(std::to_string(customSquadData.moveDistance));
		clickTimer = 30;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && downgradeUnitDistance.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		customSquadData.moveDistance -= 1;
		if (customSquadData.moveDistance < 4)
		{
			customSquadData.moveDistance = 4;
		}
		customDistanceText.setString(std::to_string(customSquadData.moveDistance));
		clickTimer = 30;
	}

	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && customUnitNextSprite.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		spriteChanged = true;
		customUnitSprite++;
		if (customUnitSprite > 2)
		{
			customUnitSprite = 0;
		}
		clickTimer = 30;
	}

	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && customUnitPreviousSprite.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		spriteChanged = true;
		customUnitSprite--;
		if (customUnitSprite < 0)
		{
			customUnitSprite = 2;
		}
		clickTimer = 30;
	}


	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && closeUpgradeMenu.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && upgradeMenuOpen == true && clickTimer == 0)
	{
		upgradeMenuOpen = false;
		clickTimer = 30;
	}

	clickTimer--;
	if (clickTimer < 0)
	{
		clickTimer = 0;
	}
	if (clickTimer == 10)
	{
		endTurnButton.setFillColor(sf::Color(100, 200, 100));
		openUnitMenuButton.setFillColor(sf::Color(100, 200, 150));
		openTowerMenuButton.setFillColor(sf::Color(100, 150, 200));
		resetTurnButton.setFillColor(sf::Color(200, 100, 100));
		createTankUnit.setFillColor(sf::Color(200, 200, 100));
		createHeavyTankUnit.setFillColor(sf::Color(200, 100, 200));
		createPistolUnit.setFillColor(sf::Color(100, 200, 200));
		createHelicopterUnit.setFillColor(sf::Color(200, 100, 100));
		createCustomUnit.setFillColor(sf::Color(100, 100, 200));
		createGoldMineTower.setFillColor(sf::Color(200, 200, 100));
		createUpgradeTower.setFillColor(sf::Color(200, 100, 200));
	}
}

void UI::setMousePos(sf::Vector2i t_mousePos)
{
	mousePos.x = t_mousePos.x;
	mousePos.y = t_mousePos.y;
}

void UI::updateUnitDataDisplay(SquadData t_squadData)
{
	unitDataDisplayBacking.setPosition({ mousePos.x - (SCREEN_WIDTH / 5), mousePos.y - (SCREEN_HEIGHT / 7) });

	if (unitDataDisplayBacking.getPosition().x < unitDataDisplayBacking.getGlobalBounds().getSize().x / 2)
	{
		unitDataDisplayBacking.setPosition(unitDataDisplayBacking.getGlobalBounds().getSize().x / 2, unitDataDisplayBacking.getPosition().y);
	}
	if (unitDataDisplayBacking.getPosition().y < unitDataDisplayBacking.getGlobalBounds().getSize().y / 2)
	{
		unitDataDisplayBacking.setPosition(unitDataDisplayBacking.getPosition().x, unitDataDisplayBacking.getGlobalBounds().getSize().y / 2);
	}

	float xSize = unitDataDisplayBacking.getGlobalBounds().getSize().x;
	float ySize = unitDataDisplayBacking.getGlobalBounds().getSize().y;

	squadTeamDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25));
	squadTypeDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25) + ySize / 8);
	squadStrengthDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25) + ySize / 8 * 2);
	squadHealthDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25) + ySize / 8 * 3);
	squadSpeedDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25) + ySize / 8 * 4);
	squadDistanceDisplay.setPosition(unitDataDisplayBacking.getPosition().x - (xSize / 2.25), unitDataDisplayBacking.getPosition().y - (ySize / 2.25) + ySize / 8 * 5);

	squadSpeedDisplay.setString("Speed: " + std::to_string(t_squadData.moveSpeed));
	squadStrengthDisplay.setString("Damage: " + std::to_string(t_squadData.squadStrength));
	squadTypeDisplay.setString("Type: " + std::to_string(t_squadData.unitType));
	squadHealthDisplay.setString("Health: " + std::to_string(t_squadData.health));
	squadTeamDisplay.setString("Team: " + std::to_string(t_squadData.teamNum + 1));
	squadDistanceDisplay.setString("Move Distance: " + std::to_string(t_squadData.moveDistance));
}
