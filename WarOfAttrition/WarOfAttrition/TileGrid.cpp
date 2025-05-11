#include "TileGrid.h"

void TileGrid::init()
{
	Tile newTile;

	setupTextures();

	sf::Sprite tempSprite;
	tempSprite.setTexture(customWaterSpritesheet);
	int tilesPerRow = 10;
	int tileWidth = 64;
	int tileHeight = 64;
	int x = (38 % tilesPerRow) * tileWidth;
	int y = (38 / tilesPerRow) * tileHeight;
	tempSprite.setTextureRect(sf::IntRect(x, y, tileWidth, tileHeight));

	tempSprite.setOrigin(tempSprite.getGlobalBounds().getSize().x / 2, tempSprite.getGlobalBounds().getSize().y / 2);
	tempSprite.setScale((tempSprite.getScale().x / 64) * 50, (tempSprite.getScale().y / 64) * 50);

	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		tiles.push_back(newTile);//add new tile to list
		tiles[index].init({ (index % TILE_COLUMNS) * TILE_SIZE,(index / TILE_COLUMNS) * TILE_SIZE } , index);//place new tile in position relative to its number
		tempSprite.setPosition(tiles[index].getTileShape().getPosition());
		worldTileTemp.push_back(tempSprite);
	}

	std::ifstream wallsData("walls.txt");
	tileSetAsWalls;

	if (wallsData.is_open()) {
		int tileIndex;
		while (wallsData >> tileIndex) 
		{
			tileSetAsWalls.push_back(tileIndex);
		}
		wallsData.close();
	}
	else 
	{
		std::cerr << "Failed to open walls.txt" << std::endl;
	}

	for (int index : tileSetAsWalls)
	{
		tiles[index].setType(2);
		updateTileTexture(index, 0);
	}
	allInvalidTiles = tileSetAsWalls;
	//updateTileType(2);
}

void TileGrid::update(sf::Time& t_deltaTime)
{
	
}

void TileGrid::hightlightTiles(bool t_valid)
{
	tiles[lastCellHovered].clearTile();
	int column = mousePosViewPort.x / TILE_SIZE;
	int row = mousePosViewPort.y / TILE_SIZE;

	if (row * TILE_COLUMNS + column > tiles.size())
	{
		//std::cout << "Mouse no longer in bounds of map\n";
		return;
	}

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
		if (tiles[index].getType() != 2)//water
		{
			tiles[index].setTarget(false);
			tiles[index].setType(0);
		}
	}
}

void TileGrid::render(sf::RenderWindow& t_window)
{
	sf::Vector2i temp = sf::Mouse::getPosition(t_window);
	if (temp.x >= 0 && temp.y >= 0 && static_cast<unsigned int>(temp.x) < t_window.getSize().x && static_cast<unsigned int>(temp.y) < t_window.getSize().y)
	{
		mousePos = sf::Mouse::getPosition(t_window);
		mousePosViewPort = t_window.mapPixelToCoords(mousePos);//get coords relative to the viewport
	}
	//else std::cout << "(TileGrid) mouse out of bounds\n";

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
			if (tiles[index].getType() == 0 && std::find(playerTakenTiles.begin(), playerTakenTiles.end(), index) == playerTakenTiles.end())
			{
				return tiles[index].getTileShape().getPosition();
			}
		}
	}
	return sf::Vector2f(0,0);
}

sf::Vector2f TileGrid::tileOnMouse()
{
	sf::Vector2f temp = mousePosViewport();
	for (int index = 0; index < (TILE_ROWS * TILE_COLUMNS); index++)
	{
		if (tiles[index].getTileShape().getGlobalBounds().contains(temp))
		{
			return tiles[index].getTileShape().getPosition();
		}
	}
	return sf::Vector2f(0, 0);
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
		if (tiles[tileSetAsWalls.at(index)].getType() == 2 && tileSetAsWalls.at(index) == t_tileNum)
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
		if (tiles[index].getType() == 2)//water
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
	//normalise it because the path was weird without doing it
	sf::Vector2f startPosNormalised = sf::Vector2f(static_cast<int>(t_startPos.x/ TILE_SIZE) * TILE_SIZE,static_cast<int>(t_startPos.y/ TILE_SIZE) * TILE_SIZE);
	sf::Vector2f targetPosNormalised = sf::Vector2f(static_cast<int>(t_targetPos.x/ TILE_SIZE) * TILE_SIZE,static_cast<int>(t_targetPos.y/ TILE_SIZE) * TILE_SIZE);

	std::vector<int> path;
	std::queue<int> queue;
	std::vector<int> cameFrom(TILE_ROWS * TILE_COLUMNS, -1);

	int startTile = (int(startPosNormalised.y) / TILE_SIZE) * TILE_COLUMNS + (int(startPosNormalised.x) / TILE_SIZE);//go from coords to tiles
	int targetTile = (int(targetPosNormalised.y) / TILE_SIZE) * TILE_COLUMNS + (int(targetPosNormalised.x ) / TILE_SIZE);

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

			if (checkIfWall(neighbour) == true || std::find(playerTakenTiles.begin(), playerTakenTiles.end(), neighbour) != playerTakenTiles.end())
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

void TileGrid::getPlayerTakenTiles(std::vector<int> t_playerTakenTiles)
{
	playerTakenTiles = t_playerTakenTiles;
}

int TileGrid::preventOutOfBoundsCheck(int index)
{
	if (index >= 0 && index < static_cast<int>(tiles.size()))
	{
		return tiles[index].getType();
	}
	return -999;
}

void TileGrid::setupTextures()
{
	//if (!defaultTileTexture.loadFromFile("ASSETS/Tiles/Grass/tile_0029_grass6.png"))
		//std::cout << "ERROR loading DEFAULT tile\n";

	if (!customWaterSpritesheet.loadFromFile("ASSETS/Tiles/GrassWaterSpritesheet.png"))
		std::cout << "ERROR loading CustomWaterSpritesheet.png\n";
}

void TileGrid::updateTileTexture(int t_tileNum, int t_depth)
{
	if (t_tileNum < 0 || t_tileNum >= tiles.size())
		return;

	int tileType = tiles[t_tileNum].getType();
	int spritesheetNumber = checkSurroundingTiles(t_tileNum);

	sf::Sprite& sprite = worldTileTemp[t_tileNum];

	if (tileType == 0)
	{
		sprite.setTexture(customWaterSpritesheet);
		int tilesPerRow = 10;
		int tileWidth = 64;
		int tileHeight = 64;
		int x = (38 % tilesPerRow) * tileWidth;
		int y = (38 / tilesPerRow) * tileHeight;
		sprite.setTextureRect(sf::IntRect(x, y, tileWidth, tileHeight));
	}
	else if (tileType == 2)
	{
		sprite.setTexture(customWaterSpritesheet);
		int tilesPerRow = 10;
		int tileWidth = 64;
		int tileHeight = 64;
		int x = (spritesheetNumber % tilesPerRow) * tileWidth;
		int y = (spritesheetNumber / tilesPerRow) * tileHeight;
		sprite.setTextureRect(sf::IntRect(x, y, tileWidth, tileHeight));
	}

	if (t_depth == 0)//update all neighbours textures to ensure they are correctly connected after changing current
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
	int row = t_tileNum / TILE_COLUMNS;
	int col = t_tileNum % TILE_COLUMNS;
	int centerType = preventOutOfBoundsCheck(t_tileNum);

	//check if the cell at specified offset is the same as the current cell so we know if we need to connect to it or not
	auto matchesType = [&](int rowOffset, int colOffset) -> bool 
	{
		int neighborRow = row + rowOffset;
		int neighborCol = col + colOffset;

		if (neighborRow >= 0 && neighborRow < TILE_ROWS && neighborCol >= 0 && neighborCol < TILE_COLUMNS)
		{
			int neighborIndex = neighborRow * TILE_COLUMNS + neighborCol;
			return preventOutOfBoundsCheck(neighborIndex) == centerType;
		}
		return false;
	};

	bool N = matchesType(-1, 0);
	bool W = matchesType(0, -1);
	bool E = matchesType(0, 1);
	bool S = matchesType(1, 0);
	bool NW = matchesType(-1, -1);
	bool NE = matchesType(-1, 1);
	bool SW = matchesType(1, -1);
	bool SE = matchesType(1, 1);

	if (N && S && E && W && NE && NW && SE && SW) return 13;//fully surrounded
	//2 blank corners
	if (!N && W && E && S && !SW && !SE) return 34;//straight path with 1 offshoot
	if (N && W && !E && S && !NW && !SW) return 14;
	if (N && !W && E && S && !NE && !SE) return 24;
	if (N && W && E && !S && !NW && !NE) return 4;
	//2 empty corners
	if (N && W && E && S && NW && NE && !SW && !SE) return 9;
	if (N && W && E && S && !NW && !NE && SW && SE) return 19;
	if (N && W && E && S && !NW && NE && !SW && SE) return 29;
	if (N && W && E && S && NW && !NE && SW && !SE) return 39;
	//interior corners
	if (N && W && E && S && !NW && NE && SW && SE) return 7;// 1 corner piece empty
	if (N && W && E && S && NW && !NE && SW && SE) return 17;
	if (N && W && E && S && NW && NE && !SW && SE) return 27;
	if (N && W && E && S && NW && NE && SW && !SE) return 37;
	//diagonal interior corners
	if (N && W && E && S && !NW && NE && SW && !SE) return 8;
	if (N && W && E && S && NW && !NE && !SW && SE) return 18;

	if (N && W && E && S && !NW && !NE && !SW && SE) return 36;//SE filled
	if (N && W && E && S && !NW && !NE && SW && !SE) return 26;//SW filled
	if (N && W && E && S && !NW && NE && !SW && !SE) return 16;//NE filled
	if (N && W && E && S && NW && !NE && !SW && !SE) return 6;//NW filled
	//Turn with interior corner missing
	if (!N && W && !E && S && !NE && !SW) return 22;
	if (!N && !W && E && S && !NW && !SE) return 32;
	if (N && W && !E && !S && !NW && !SE) return 2;
	if (N && !W && E && !S && !NE && !SW) return 12;
	//flat on 3 sides
	if (!N && W && E && S && SW && SE) return 35;
	if (N && !W && E && S && NE && SE) return 15;
	if (N && W && !E && S && NW && SW) return 25;
	if (N && W && E && !S && NW && NE) return 5;

	if (!N && !W && E && S && SE) return 31;//nothing up and left
	if (!N && W && !E && S && SW) return 21;//nothing up and left
	if (N && !W && E && !S && NE) return 11;//nothing up and left
	if (N && W && !E && !S && NW) return 1;//nothing up and left

	if (N && W && E && S && !NW && !NE && !SW && !SE) return 29;//center no corners
	if (N && S) return 33;// up and below only
	if (W && E) return 23;// left and right only
	//just 1 connection
	if (N) return 0;
	if (W) return 10;
	if (E) return 20;
	if (S) return 30;

	return 3;//3rd space on tilesheet - no neighbours
}
