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

	createGoldMineTower.setSize({ SCREEN_WIDTH / 15, SCREEN_HEIGHT / 12 });
	createGoldMineTower.setOrigin({ createGoldMineTower.getSize().x / 2 ,createGoldMineTower.getSize().y / 2 });
	createGoldMineTower.setPosition({ unitMenuBacking.getPosition().x + unitMenuBacking.getSize().x / 4,unitMenuBacking.getPosition().y - unitMenuBacking.getSize().y / 3 });
	createGoldMineTower.setFillColor(sf::Color(200, 200, 100));
	createGoldMineTower.setOutlineColor(sf::Color::Black);
	createGoldMineTower.setOutlineThickness(3);

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
}

void UI::update(sf::Time t_deltaTime)
{

}

void UI::fixedUpdate()
{

}

void UI::render(sf::RenderWindow& t_window, bool t_squadData, bool t_createUnit, bool t_createTower)
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
	//t_window.draw(framerateText);

	if (t_squadData == true)
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
		t_window.draw(createPistolUnit);
		t_window.draw(createHeavyTankUnit);
	}
	if (t_createTower == true)
	{
		t_window.draw(unitMenuBacking);
		t_window.draw(createGoldMineTower);
	}
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

}

void UI::handleMenuInteractions()
{
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && endTurnButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickTimer == 0)
	{
		attemptTurnEnd = true;
		endTurnButton.setFillColor(sf::Color(100, 150, 100));
		clickTimer = 30;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && openUnitMenuButton.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == false && clickTimer == 0)
	{
		openUnitMenuButton.setFillColor(sf::Color(100, 150, 100));
		clickTimer = 30;
		openCreateUnitMenu = true;
		openCreateTowerMenu = false;
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
		openCreateTowerMenu = true;
		openCreateUnitMenu = false;
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
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createPistolUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createPistolUnit.setFillColor(sf::Color(150, 150, 100));
		createUnitActive = true;
		unitTypeToCreate = 1;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createHeavyTankUnit.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateUnitMenu == true && clickTimer == 0)
	{
		clickTimer = 30;
		createHeavyTankUnit.setFillColor(sf::Color(150, 150, 100));
		createUnitActive = true;
		unitTypeToCreate = 2;
	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && createGoldMineTower.getGlobalBounds().contains({ static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) })) && openCreateTowerMenu == true && clickTimer == 0)
	{
		createGoldTower = true;
		clickTimer = 30;
		createGoldMineTower.setFillColor(sf::Color(150, 150, 100));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && createUnitActive == true && clickTimer == 0)
	{
		createNewUnit = true;
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
		createGoldMineTower.setFillColor(sf::Color(200, 200, 100));
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
