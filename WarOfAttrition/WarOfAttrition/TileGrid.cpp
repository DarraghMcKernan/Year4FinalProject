#include "TileGrid.h"

void TileGrid::init()
{
	Tile newTile;

	setupTextures();

	sf::Sprite tempSprite;
	tempSprite.setTexture(defaultTileTexture);
	tempSprite.setOrigin(tempSprite.getGlobalBounds().getSize().x / 2, tempSprite.getGlobalBounds().getSize().y / 2);
	tempSprite.setScale((tempSprite.getScale().x / 64) * 50, (tempSprite.getScale().y / 64) * 50);

	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		tiles.push_back(newTile);//add new tile to list
		tiles[index].init({ (index % TILE_COLUMNS) * TILE_SIZE,(index / TILE_COLUMNS) * TILE_SIZE } , index);//place new tile in position relative to its number
		tempSprite.setPosition(tiles[index].getTileShape().getPosition());
		worldTileTemp.push_back(tempSprite);
	}
	for (int index = 0; index < 5; index++)//would eventually be read from a file
	{
		tileSetAsWalls.push_back(105 + index);
		tileSetAsWalls.push_back(105 + index + TILE_ROWS + 3);
		tileSetAsWalls.push_back(105 + index + 17 + TILE_ROWS*2);
		tileSetAsWalls.push_back(105 + index + 20 + TILE_ROWS*5);
	}

	std::ifstream wallsData("walls.txt");
	std::vector<int> tileSetAsWalls; // Store wall tile indices

	if (wallsData.is_open()) {
		int tileIndex;
		while (wallsData >> tileIndex) { // Read each index from the file
			tileSetAsWalls.push_back(tileIndex);
		}
		wallsData.close();
	}
	else {
		std::cerr << "Failed to open walls.txt" << std::endl;
	}

	// Now set the tile types
	for (int index : tileSetAsWalls) {
		tiles[index].setType(1); // 1 is a wall type
	}

	allInvalidTiles = tileSetAsWalls;

	//getPathToTarget(sf::Vector2f(155, 220), sf::Vector2f(550, 550));
}

void TileGrid::update(sf::Time& t_deltaTime)
{
	
}

void TileGrid::hightlightTiles(bool t_valid)
{
	tiles[lastCellHovered].clearTile();
	int column = mousePosViewPort.x / TILE_SIZE;
	int row = mousePosViewPort.y / TILE_SIZE;

	lastCellHovered = row * TILE_COLUMNS + column;

	tiles[lastCellHovered].setHighlight(t_valid);
}

void TileGrid::findTargetedTile()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0)
	{
		tiles[currentTile].setTarget(false);//unset previous target
		resetTiles();

		int column = mousePosViewPort.x / TILE_SIZE;
		int row = mousePosViewPort.y / TILE_SIZE;

		int tempTile = row * TILE_COLUMNS + column;
		int tileInvalid = 0;

		if (tempTile > 0 || tempTile < (TILE_ROWS * TILE_COLUMNS))//ensure new tile is within the list
		{
			for (int index = 0; index < MAX_MOVES_PER_TURN; index++)
			{
				if (checkIfWall(tempTile) == true)//if any of the tiles are already taken
				{
					tileInvalid++;
					std::cout << "tile not valid\n";
				}
			}
			if (tileInvalid == 0)//make sure none of the tiles are already taken
			{
				currentTile = tempTile;

				tiles[currentTile].setTarget(true);//update target

				positionUpdated = true;//allow new position to be given to player

				clickCooldown = 10;
			}
		}
	}
}

void TileGrid::deactiveateTile()
{
	//tiles[currentTile].setTarget(false);//unset previous target
	for (int index = 0; index < MAX_MOVES_PER_TURN; index++)
	{
		tiles[tilesSelected[index]].setTarget(false);
	}
}

void TileGrid::deactiveateAllTiles()
{
	for (int index = 0; index < TILE_ROWS * TILE_COLUMNS; index++)
	{
		if (tiles[index].getType() != 1)//wall
		{
			tiles[index].setTarget(false);
			tiles[index].setType(0);
		}
	}
}

void TileGrid::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);
	mousePosViewPort = t_window.mapPixelToCoords(mousePos);//get coords relative to the viewport

	for (int index = 0; index < TILE_ROWS * TILE_COLUMNS; index++)
	{
		t_window.draw(worldTileTemp[index]);
		tiles[index].render(t_window);
		
	}
}

int TileGrid::currentPlayerTarget(int t_turnNum)
{
	//std::cout << "mouse X: " + std::to_string(mousePosViewPort.x) + "    mouse Y:" + std::to_string(mousePosViewPort.y) + "\n";
	tilesSelected[t_turnNum-1] = currentTile;
	tiles[currentTile].tileSetAsTarget = true;
	return currentTile;
}

sf::Vector2f TileGrid::mousePosViewport()
{
	return mousePosViewPort;
}

sf::Vector2f TileGrid::tileHoveredOverPos()
{
	sf::Vector2f temp = mousePosViewport();
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		if (tiles[index].getTileShape().getGlobalBounds().contains(temp))
		{
			return tiles[index].getTileShape().getPosition();
		}
	}
	return sf::Vector2f(0,0);
}

sf::Vector2f TileGrid::normaliseToTilePosition(sf::Vector2f t_position)
{
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		if (tiles[index].getTileShape().getGlobalBounds().contains(t_position))
		{
			return tiles[index].getTileShape().getPosition();
		}
	}
	return sf::Vector2f(0, 0);
}

int TileGrid::tileHoveredOverNum()
{
	sf::Vector2f temp = mousePosViewport();
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		if (tiles[index].getTileShape().getGlobalBounds().contains(temp))
		{
			return index;
		}
	}
	return 0;
}

void TileGrid::resetTiles()
{
	for (int index = 0; index < MAX_MOVES_PER_TURN; index++)
	{
		tiles[tilesSelected[index]].tileSetAsTarget = false;
	}
	deactiveateTile();
	deactiveateAllTiles();//needs to be called to prevent tiles from staying claimed
}

bool TileGrid::checkIfWall(int t_tileNum)
{
	for (int index = 0; index < tileSetAsWalls.size(); index++)
	{
		if (tiles[tileSetAsWalls.at(index)].getType() == 1 && tileSetAsWalls.at(index) == t_tileNum)
		{
			return true;
		}
	}
	return false;
}

void TileGrid::updateTileType(int t_type)
{
	tiles[tileHoveredOverNum()].setType(t_type);
	
	std::fstream wallsData("walls.txt");
	wallsData.clear();

	tileSetAsWalls.clear();
	for (int index = 0; index < TILE_ROWS * TILE_COLUMNS; index++)
	{
		if (tiles[index].getType() == 1)//wall
		{
			wallsData << index <<"\n";
			tileSetAsWalls.push_back(index);
		}
	}
	allInvalidTiles = tileSetAsWalls;
	wallsData.close();

	updateTileTexture(tileHoveredOverNum(),0);
}

std::vector<int> TileGrid::getPathToTarget(sf::Vector2f t_startPos, sf::Vector2f t_targetPos)
{
	//std::cout << "generate path to target\n";

	//std::cout << t_startPos.x << " " << t_startPos.y << "\n";
	//std::cout << t_targetPos.x << " " << t_targetPos.y << "\n";

	sf::Vector2f startPosNormalised = sf::Vector2f(static_cast<int>(t_startPos.x/ TILE_SIZE) * TILE_SIZE,static_cast<int>(t_startPos.y/ TILE_SIZE) * TILE_SIZE);//normalise it because the path was weird without doing it
	sf::Vector2f targetPosNormalised = sf::Vector2f(static_cast<int>(t_targetPos.x/ TILE_SIZE) * TILE_SIZE,static_cast<int>(t_targetPos.y/ TILE_SIZE) * TILE_SIZE);

	//std::cout << startPosNormalised.x << " " << startPosNormalised.y << "\n";
	//std::cout << targetPosNormalised.x << " " << targetPosNormalised.y << "\n";

	std::vector<int> path;
	std::queue<int> queue;
	std::vector<int> cameFrom(TILE_ROWS * TILE_COLUMNS, -1);

	int startTile = (int(startPosNormalised.y) / TILE_SIZE) * TILE_COLUMNS + (int(startPosNormalised.x) / TILE_SIZE);//go from coords to tiles
	int targetTile = (int(targetPosNormalised.y) / TILE_SIZE) * TILE_COLUMNS + (int(targetPosNormalised.x ) / TILE_SIZE);

	//if (checkIfWall(startTile) || checkIfWall(targetTile))
	//{
	//	return path;
	//}

	queue.push(startTile);
	cameFrom[startTile] = startTile;

	//std::vector<int> directions = { -1, 1, -TILE_COLUMNS, TILE_COLUMNS, -TILE_COLUMNS - 1, -TILE_COLUMNS + 1, TILE_COLUMNS - 1, TILE_COLUMNS + 1 };//diagonals
	std::vector<int> directions = { -1, 1, -TILE_COLUMNS, TILE_COLUMNS };//no diagonals

	while (!queue.empty()) {
		int current = queue.front();
		queue.pop();

		if (current == targetTile)//goal reached
		{
			break;
		}
		int row = current / TILE_COLUMNS;
		int col = current % TILE_COLUMNS;

		for (int index = 0; index < directions.size(); index++)//check all neighbouring cells
		{
			int dir = directions[index];
			int neighbour = current + dir;
			int nRow = neighbour / TILE_COLUMNS;
			int nCol = neighbour % TILE_COLUMNS;

			if (neighbour < 0 || neighbour >= TILE_ROWS * TILE_COLUMNS || cameFrom[neighbour] != -1)
			{
				continue;
			}

			if (checkIfWall(neighbour) == true)
			{
				continue;
			}

			if ((dir == -1 || dir == 1) && (nRow != row))//reached outer tiles
			{
				continue;
			}

			if ((dir == -TILE_COLUMNS - 1 || dir == -TILE_COLUMNS + 1 || dir == TILE_COLUMNS - 1 || dir == TILE_COLUMNS + 1) && (abs(nRow - row) != 1 || abs(nCol - col) != 1))
			{
				continue;
			}

			queue.push(neighbour);//add the neighbour to the list of tiles that we need to now check
			cameFrom[neighbour] = current;
		}
	}

	if (cameFrom[targetTile] == -1)//if this is a wall ignore and return nothing
	{
		return path;
	}

	for (int index = targetTile; index != startTile; index = cameFrom[index])
	{
		path.push_back(index);//add all tiles to list
	}
	path.push_back(startTile);

	std::reverse(path.begin(), path.end());

	for (int index = 0; index < path.size(); index++)
	{
		tiles[path[index]].setType(3);//set the path to a new type so we can visually see it for debugging
	}

	return path;
}

std::vector<int> TileGrid::getInvalidTiles()
{
	return allInvalidTiles;
}


void TileGrid::setupTextures()
{
	if (!defaultTileTexture.loadFromFile("ASSETS/Tiles/Grass/tile_0029_grass6.png"))
		std::cout << "ERROR loading DEFAULT tile\n";

	if (!waterC.loadFromFile("ASSETS/Tiles/Water/tile_0077_water4.png"))
		std::cout << "ERROR loading CENTRAL WATER tile\n";

	if (!waterA.loadFromFile("ASSETS/Tiles/Water/Custom/WaterCenter.png"))
		std::cout << "ERROR loading ALONE WATER tile\n";
	if (!waterCI.loadFromFile("ASSETS/Tiles/Water/Custom/WaterCenterRoundedInterior.png"))
		std::cout << "ERROR loading SURROUNDED INVERTED WATER tile\n";

	if (!waterN.loadFromFile("ASSETS/Tiles/Water/tile_0079_water6.png"))
		std::cout << "ERROR loading NORTH WATER tile\n";
	if (!waterNW.loadFromFile("ASSETS/Tiles/Water/tile_0076_water3.png"))
		std::cout << "ERROR loading NORTH WEST WATER tile\n";
	if (!waterW.loadFromFile("ASSETS/Tiles/Water/tile_0078_water5.png"))
		std::cout << "ERROR loading WEST WATER tile\n";
	if (!waterSW.loadFromFile("ASSETS/Tiles/Water/tile_0087_water14.png"))
		std::cout << "ERROR loading SOUTH WEST WATER tile\n";

	if (!waterS.loadFromFile("ASSETS/Tiles/Water/tile_0088_water15.png"))
		std::cout << "ERROR loading SOUTH WATER tile\n";
	if (!waterSE.loadFromFile("ASSETS/Tiles/Water/tile_0089_water16.png"))
		std::cout << "ERROR loading SOUTH EAST WATER tile\n";
	if (!waterE.loadFromFile("ASSETS/Tiles/Water/tile_0075_water2.png"))
		std::cout << "ERROR loading EAST WATER tile\n";
	if (!waterNE.loadFromFile("ASSETS/Tiles/Water/tile_0080_water7.png"))
		std::cout << "ERROR loading NORTH EAST WATER tile\n";
	
	//straight upwards, nothing on sides
	if (!waterNA.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNCenter.png"))
		std::cout << "ERROR loading NORTH ALONE WATER tile\n";
	if (!waterWA.loadFromFile("ASSETS/Tiles/Water/Custom/WaterWCenter.png"))
		std::cout << "ERROR loading WEST ALONE WATER tile\n";
	if (!waterSA.loadFromFile("ASSETS/Tiles/Water/Custom/WaterSCenter.png"))
		std::cout << "ERROR loading SOUTH ALONE WATER tile\n";
	if (!waterEA.loadFromFile("ASSETS/Tiles/Water/Custom/WaterECenter.png"))
		std::cout << "ERROR loading EAST ALONE WATER tile\n";

	//interior corners
	if (!waterNWI.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNWInteriorCorner.png"))
		std::cout << "ERROR loading NORTH WEST INTERIOR WATER tile\n";
	if (!waterNEI.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNEInteriorCorner.png"))
		std::cout << "ERROR loading NORTH EAST INTERIOR WATER tile\n";
	if (!waterSWI.loadFromFile("ASSETS/Tiles/Water/Custom/WaterSWInteriorCorner.png"))
		std::cout << "ERROR loading SOUTH WEST INTERIOR WATER tile\n";
	if (!waterSEI.loadFromFile("ASSETS/Tiles/Water/Custom/WaterSEInteriorCorner.png"))
		std::cout << "ERROR loading SOUTH EAST INTERIOR WATER tile\n";
	//diagonal
	if (!waterSEINW.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNW&SECornerFilled.png"))
		std::cout << "ERROR loading SOUTH EAST INTERIOR WITH NORTH WEST WATER tile\n";
	if (!waterSWINE.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNE&SWCornerFilled.png"))
		std::cout << "ERROR loading SOUTH WEST INTERIOR WITH NORTH EAST WATER tile\n";

	//1 corner filled
	if (!waterSEF.loadFromFile("ASSETS/Tiles/Water/Custom/WaterSECornerFilled.png"))
		std::cout << "ERROR loading SOUTH EAST FILLED tile\n";
	if (!waterSWF.loadFromFile("ASSETS/Tiles/Water/Custom/WaterSWCornerFilled.png"))
		std::cout << "ERROR loading SOUTH WEST FILLED tile\n";
	if (!waterNEF.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNECornerFilled.png"))
		std::cout << "ERROR loading NORTH EAST FILLED tile\n";
	if (!waterNWF.loadFromFile("ASSETS/Tiles/Water/Custom/WaterNWCornerFilled.png"))
		std::cout << "ERROR loading NORTH WEST FILLED tile\n";

	if (!waterNEC.loadFromFile("ASSETS/Tiles/Water/Custom/WaterICornerNE.png"))
		std::cout << "ERROR loading NORTH EAST TURN INTERIOR CORNER CUT OUT tile\n";
	if (!waterNWC.loadFromFile("ASSETS/Tiles/Water/Custom/WaterCornerNW.png"))
		std::cout << "ERROR loading NORTH WEST TURN INTERIOR CORNER CUT OUT tile\n";
	if (!waterSEC.loadFromFile("ASSETS/Tiles/Water/Custom/WaterCornerSE.png"))
		std::cout << "ERROR loading SOUTH EAST TURN INTERIOR CORNER CUT OUT tile\n";
	if (!waterSWC.loadFromFile("ASSETS/Tiles/Water/Custom/WaterCornerSW.png"))
		std::cout << "ERROR loading SOUTH WEST TURN INTERIOR CORNER CUT OUT tile\n";
}

void TileGrid::updateTileTexture(int t_tileNum, int t_depth)
{
	if (tiles[t_tileNum].getType() == 0)//ground tile
	{
		checkSurroundingTiles(t_tileNum);
		worldTileTemp[t_tileNum].setTexture(defaultTileTexture);
	}
	else if (tiles[t_tileNum].getType() == 2)//water tile
	{
		if (checkSurroundingTiles(t_tileNum) == 0)//single tile
		{
			worldTileTemp[t_tileNum].setTexture(waterA);
		}
		else if (checkSurroundingTiles(t_tileNum) == 1)//surrounded by water
		{
			worldTileTemp[t_tileNum].setTexture(waterC);
		}
		else if (checkSurroundingTiles(t_tileNum) == 6)
		{
			worldTileTemp[t_tileNum].setTexture(waterCI);
		}

		else if (checkSurroundingTiles(t_tileNum) == 2)
		{
			worldTileTemp[t_tileNum].setTexture(waterSA);
		}
		else if (checkSurroundingTiles(t_tileNum) == 3)
		{
			worldTileTemp[t_tileNum].setTexture(waterEA);
		}
		else if (checkSurroundingTiles(t_tileNum) == 4)
		{
			worldTileTemp[t_tileNum].setTexture(waterWA);
		}
		else if (checkSurroundingTiles(t_tileNum) == 5)
		{
			worldTileTemp[t_tileNum].setTexture(waterNA);
		}

		else if (checkSurroundingTiles(t_tileNum) == 7)
		{
			worldTileTemp[t_tileNum].setTexture(waterN);
		}
		else if (checkSurroundingTiles(t_tileNum) == 8)
		{
			worldTileTemp[t_tileNum].setTexture(waterW);
		}
		else if (checkSurroundingTiles(t_tileNum) == 9)
		{
			worldTileTemp[t_tileNum].setTexture(waterE);
		}
		else if (checkSurroundingTiles(t_tileNum) == 10)
		{
			worldTileTemp[t_tileNum].setTexture(waterS);
		}

		else if (checkSurroundingTiles(t_tileNum) == 11)//turn
		{
			worldTileTemp[t_tileNum].setTexture(waterNW);
		}
		else if (checkSurroundingTiles(t_tileNum) == 12)
		{
			worldTileTemp[t_tileNum].setTexture(waterNE);
		}
		else if (checkSurroundingTiles(t_tileNum) == 13)
		{
			worldTileTemp[t_tileNum].setTexture(waterSW);
		}
		else if (checkSurroundingTiles(t_tileNum) == 14)
		{
			worldTileTemp[t_tileNum].setTexture(waterSE);
		}

		//interior corners
		else if (checkSurroundingTiles(t_tileNum) == 15)
		{
			worldTileTemp[t_tileNum].setTexture(waterNWI);
		}
		else if (checkSurroundingTiles(t_tileNum) == 16)
		{
			worldTileTemp[t_tileNum].setTexture(waterNEI);
		}
		else if (checkSurroundingTiles(t_tileNum) == 17)
		{
			worldTileTemp[t_tileNum].setTexture(waterSWI);
		}
		else if (checkSurroundingTiles(t_tileNum) == 18)
		{
			worldTileTemp[t_tileNum].setTexture(waterSEI);
		}

		//diagonal interior
		else if (checkSurroundingTiles(t_tileNum) == 20)
		{
			worldTileTemp[t_tileNum].setTexture(waterSEINW);
		}
		else if (checkSurroundingTiles(t_tileNum) == 19)
		{
			worldTileTemp[t_tileNum].setTexture(waterSWINE);
		}

		//1 corner filled
		else if (checkSurroundingTiles(t_tileNum) == 23)
		{
			worldTileTemp[t_tileNum].setTexture(waterNEF);
		}
		else if (checkSurroundingTiles(t_tileNum) == 24)
		{
			worldTileTemp[t_tileNum].setTexture(waterNWF);
		}
		else if (checkSurroundingTiles(t_tileNum) == 22)
		{
			worldTileTemp[t_tileNum].setTexture(waterSWF);
		}
		else if (checkSurroundingTiles(t_tileNum) == 21)
		{
			worldTileTemp[t_tileNum].setTexture(waterSEF);
		}

		else if (checkSurroundingTiles(t_tileNum) == 25)
		{
			worldTileTemp[t_tileNum].setTexture(waterNEC);
		}
		else if (checkSurroundingTiles(t_tileNum) == 26)
		{
			worldTileTemp[t_tileNum].setTexture(waterNWC);
		}
		else if (checkSurroundingTiles(t_tileNum) == 27)
		{
			worldTileTemp[t_tileNum].setTexture(waterSEC);
		}
		else if (checkSurroundingTiles(t_tileNum) == 28)
		{
			worldTileTemp[t_tileNum].setTexture(waterSWC);
		}

	}
	if (t_depth == 0)//if this is the orignal tile recall this function on the surronding tiles so they can update themselves too
	{
		updateTileTexture(t_tileNum - TILE_COLUMNS - 1, 1);
		updateTileTexture(t_tileNum - TILE_COLUMNS, 1);
		updateTileTexture(t_tileNum - TILE_COLUMNS + 1, 1);

		updateTileTexture(t_tileNum - 1, 1);
		updateTileTexture(t_tileNum + 1, 1);

		updateTileTexture(t_tileNum + TILE_COLUMNS - 1, 1);
		updateTileTexture(t_tileNum + TILE_COLUMNS, 1);
		updateTileTexture(t_tileNum + TILE_COLUMNS + 1, 1);
	}
}

int TileGrid::checkSurroundingTiles(int t_tileNum)
{
	int NW = tiles[t_tileNum - TILE_COLUMNS -1].getType();
	int N = tiles[t_tileNum - TILE_COLUMNS].getType();
	int NE = tiles[t_tileNum - TILE_COLUMNS +1].getType();

	int W = tiles[t_tileNum - 1].getType();
	int thisType = tiles[t_tileNum].getType();
	int E = tiles[t_tileNum + 1].getType();

	int SW = tiles[t_tileNum + TILE_COLUMNS - 1].getType();
	int S = tiles[t_tileNum + TILE_COLUMNS].getType();
	int SE = tiles[t_tileNum + TILE_COLUMNS + 1].getType();

	if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW == thisType && NE == thisType && SW == thisType && SE == thisType)
	{
		return 1;//surrounded by water on all sides
	}

	//interior corners
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW != thisType && NE == thisType && SW == thisType && SE == thisType)
	{
		return 15;// 1 corner piece empty
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW == thisType && NE != thisType && SW == thisType && SE == thisType)
	{
		return 16;
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW == thisType && NE == thisType && SW != thisType && SE == thisType)
	{
		return 17;
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW == thisType && NE == thisType && SW == thisType && SE != thisType)
	{
		return 18;
	}
	//diagonal interior corners
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW != thisType && NE == thisType && SW == thisType && SE != thisType)
	{
		return 19;
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW == thisType && NE != thisType && SW != thisType && SE == thisType)
	{
		return 20;
	}

	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW != thisType && NE != thisType && SW != thisType && SE == thisType)
	{
		return 21;//SE filled
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW != thisType && NE != thisType && SW == thisType && SE != thisType)
	{
		return 22;//SW filled
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW != thisType && NE == thisType && SW != thisType && SE != thisType)
	{
		return 23;//NE filled
	}
	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW == thisType && NE != thisType && SW != thisType && SE != thisType)
	{
		return 24;//NW filled
	}

	else if (N != thisType && W == thisType && E != thisType && S == thisType &&
		NE != thisType && SW != thisType)
	{
		return 25;//Turn with interior corner missing
	}
	else if (N != thisType && W != thisType && E == thisType && S == thisType &&
		SE != thisType && NW != thisType)
	{
		return 26;
	}
	else if (N == thisType && W == thisType && E != thisType && S != thisType &&
		NW != thisType && SE != thisType)
	{
		return 27;
	}
	else if (N == thisType && W != thisType && E == thisType && S != thisType &&
		NE != thisType && SW != thisType)
	{
		return 28;
	}

	//flat on 1 side
	else if (N != thisType && W == thisType && E == thisType && S == thisType &&
		SW == thisType && SE == thisType)
	{
		return 7;
	}
	else if (N == thisType && W != thisType && E == thisType && S == thisType &&
		NE == thisType && SE == thisType)
	{
		return 8;
	}
	else if (N == thisType && W == thisType && E != thisType && S == thisType &&
		NW == thisType && SW == thisType)
	{
		return 9;
	}
	else if (N == thisType && W == thisType && E == thisType && S != thisType &&
		NW == thisType && NE == thisType)
	{
		return 10;
	}

	else if (N != thisType && W != thisType && E == thisType && S == thisType &&
		 SE == thisType)
	{
		return 11;//nothing up and left
	}
	else if (N != thisType && W == thisType && E != thisType && S == thisType &&
		 SW == thisType)
	{
		return 12;//nothing up and right
	}
	else if (N == thisType && W != thisType && E == thisType && S != thisType &&
		 NE == thisType)
	{
		return 13;//nothing down and left
	}
	else if (N == thisType && W == thisType && E != thisType && S != thisType &&
		NW == thisType)
	{
		return 14;//nothing down and right
	}

	else if (N == thisType && W == thisType && E == thisType && S == thisType &&
		NW != thisType && NE != thisType && SW != thisType && SE != thisType)
	{
		return 6;//center no corners
	}

	else if (N == thisType)
	{
		return 2;
	}
	else if (W == thisType)
	{
		return 3;
	}
	else if (E == thisType)
	{
		return 4;
	}
	else if (S == thisType)
	{
		return 5;
	}


	return 0;
}