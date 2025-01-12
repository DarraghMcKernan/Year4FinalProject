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
	}

	for (int index = 0; index < tileSetAsWalls.size(); index++)
	{
		tiles[tileSetAsWalls.at(index)].setType(1);//1 is a wall type
	}
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

		int column = mousePosViewPort.x / TILE_SIZE;
		int row = mousePosViewPort.y / TILE_SIZE;

		int temp = row * TILE_COLUMNS + column;
		int tileInvalid = 0;

		if (temp > 0 || temp < (TILE_ROWS * TILE_COLUMNS))//ensure new tile is within the list
		{
			for (int index = 0; index < MAX_MOVES_PER_TURN; index++)
			{
				if (temp == tilesSelected[index] || checkIfWall(temp) == true)//if any of the tiles are already taken
				{
					tileInvalid++;
				}
			}
			if (tileInvalid == 0)//make sure none of the tiles are already taken
			{
				currentTile = temp;

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

void TileGrid::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);
	mousePosViewPort = t_window.mapPixelToCoords(mousePos);//get coords relative to the viewport

	for (int index = 0; index < TILE_ROWS * TILE_COLUMNS; index++)
	{
		tiles[index].render(t_window);
		t_window.draw(worldTileTemp[index]);
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
	//for (int index = 0; index < MAX_MOVES_PER_TURN; index++)
	//{
	//	tiles[tilesSelected[index]].tileSetAsTarget = false;
	//	tilesSelected[index] = 0;
	//}
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
	updateTileTexture(tileHoveredOverNum(),0);
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
}

void TileGrid::updateTileTexture(int t_tileNum, int t_depth)
{
	if (tiles[t_tileNum].getType() == 2)//water tile
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

		else if (checkSurroundingTiles(t_tileNum) == 11)
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

		if (t_depth == 0)//if this is the orignal tile recall this function on the surronding tiles so they can update themselves too
		{
			updateTileTexture(t_tileNum - TILE_COLUMNS-1, 1);
			updateTileTexture(t_tileNum - TILE_COLUMNS, 1);
			updateTileTexture(t_tileNum - TILE_COLUMNS+1, 1);

			updateTileTexture(t_tileNum - 1, 1);
			updateTileTexture(t_tileNum + 1, 1);

			updateTileTexture(t_tileNum + TILE_COLUMNS-1, 1);
			updateTileTexture(t_tileNum + TILE_COLUMNS, 1);
			updateTileTexture(t_tileNum + TILE_COLUMNS+1, 1);
		}
	}
}

int TileGrid::checkSurroundingTiles(int t_tileNum)
{
	int NW = tiles[t_tileNum - TILE_COLUMNS -1].getType();
	int N = tiles[t_tileNum - TILE_COLUMNS].getType();
	int NE = tiles[t_tileNum - TILE_COLUMNS +1].getType();

	int W = tiles[t_tileNum - 1].getType();

	int E = tiles[t_tileNum + 1].getType();

	int SW = tiles[t_tileNum + TILE_COLUMNS - 1].getType();
	int S = tiles[t_tileNum + TILE_COLUMNS].getType();
	int SE = tiles[t_tileNum + TILE_COLUMNS + 1].getType();

	if (N == 2 && W == 2 && E == 2 && S == 2 &&
		NW == 2 && NE == 2 && SW == 2 && SE == 2)
	{
		return 1;//surrounded by water on all sides
	}

	//flat on 1 side
	else if (N != 2 && W == 2 && E == 2 && S == 2 &&
		SW == 2 && SE == 2)
	{
		return 7;
	}
	else if (N == 2 && W != 2 && E == 2 && S == 2 &&
		NE == 2 && SE == 2)
	{
		return 8;
	}
	else if (N == 2 && W == 2 && E != 2 && S == 2 &&
		NW == 2  && SW == 2 )
	{
		return 9;
	}
	else if (N == 2 && W == 2 && E == 2 && S != 2 &&
		NW == 2 && NE == 2 )
	{
		return 10;
	}

	else if (N != 2 && W != 2 && E == 2 && S == 2 &&
		NW != 2 && SE == 2)
	{
		return 11;//nothing up and left
	}
	else if (N != 2 && W == 2 && E != 2 && S == 2 &&
		NE != 2 && SW == 2)
	{
		return 12;//nothing up and right
	}
	else if (N == 2 && W != 2 && E == 2 && S != 2 &&
		SW != 2 && NE == 2)
	{
		return 13;//nothing down and left
	}
	else if (N == 2 && W == 2 && E != 2 && S != 2 &&
		SE != 2 && NW == 2)
	{
		return 14;//nothing down and right
	}

	else if (N == 2 && W == 2 && E == 2 && S == 2&&
		NW != 2 && NE != 2 && SW != 2 && SE != 2)
	{
		return 6;//center no corners
	}

	else if (N == 2)
	{
		return 2;
	}
	else if (W == 2)
	{
		return 3;
	}
	else if (E == 2)
	{
		return 4;
	}
	else if (S == 2)
	{
		return 5;
	}
	
	//else if (N == 2 && W != 2 && E != 2 && S != 2 &&
	//	NW != 2 && NE != 2 && SW != 2 && SE != 2)
	//{
	//	return 2;
	//}
	//else if (N != 2 && W == 2 && E != 2 && S != 2 &&
	//	NW != 2 && NE != 2 && SW != 2 && SE != 2)
	//{
	//	return 3;
	//}
	//else if (N != 2 && W != 2 && E == 2 && S != 2 &&
	//	NW != 2 && NE != 2 && SW != 2 && SE != 2)
	//{
	//	return 4;
	//}
	//else if (N != 2 && W != 2 && E != 2 && S == 2 &&
	//	NW != 2 && NE != 2 && SW != 2 && SE != 2)
	//{
	//	return 5;
	//}


	return 0;
}