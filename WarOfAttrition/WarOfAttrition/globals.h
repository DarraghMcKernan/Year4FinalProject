#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> 

const float SCREEN_WIDTH = 1000.0f;//must be a multiple of the TILE_SIZE
const float SCREEN_HEIGHT = 800.0f;

const float VIEWPORT_WIDTH = 600.0f;//can be any size
const float VIEWPORT_HEIGHT = 500.0f;

const float TILE_SIZE = 50.0f;//define the size of the square tiles that make up the world
const static float SPEED_MULTIPLIER = 0.6f;//allows the entire games units to be sped up or slowed down

const int TILE_ROWS = SCREEN_HEIGHT / TILE_SIZE;
const int TILE_COLUMNS = SCREEN_WIDTH / TILE_SIZE;

const int MAX_MOVES_PER_TURN = 3;

static int playerOneUnits = 4;
static int playerTwoUnits = 4;
static int playerThreeUnits = 4;
static int playerFourUnits = 4;

static int globalMoneyPerTurn = 25;

static sf::Texture tankTexture;
static sf::Texture tankOutlineTexture;

static sf::Texture infantryTexture;
static sf::Texture infantryOutlineTexture;

static sf::Texture BTRTexture;
static sf::Texture BTROutlineTexture;
static sf::Texture unitSpriteExtrasTexture;

static sf::Texture HelicopterTexture;
static sf::Texture HelicopterOutlineTexture;
static sf::Texture HelicopterBladeTexture;
static sf::Texture HelicopterBladeShadowTexture;

static sf::Texture goldmineTexture;
static sf::Texture researchBuildingTexture;

struct SquadData
{
	int teamNum = 0;
	int moveSpeed = 100;
	int squadStrength = 100;
	int unitType = 0;
	int health = 100;
	int moveDistance = 10;
};

class PositionNormaliser {
public:

    virtual sf::Vector2f normalizeToTileCenter(const sf::Vector2f& position) const {
        float tileSize = 50.0f;

        float tileX = std::floor(position.x / tileSize) * tileSize;
        float tileY = std::floor(position.y / tileSize) * tileSize;

        return sf::Vector2f(tileX + tileSize / 2.0f, tileY + tileSize / 2.0f);
    }

    virtual sf::Vector2f convertCellNumToCoords(const int t_cellNum) const {
		int row = t_cellNum / TILE_COLUMNS;
		int column = t_cellNum % TILE_COLUMNS;

		sf::Vector2f recentCellPos;

		recentCellPos.x = column * TILE_SIZE + TILE_SIZE / 2.0f;
		recentCellPos.y = row * TILE_SIZE + TILE_SIZE / 2.0f;

		return recentCellPos;
	}

	virtual int convertCoordsToCellNum(const sf::Vector2f& t_coords) const
	{
		int column = static_cast<int>(t_coords.x / TILE_SIZE);
		int row = static_cast<int>(t_coords.y / TILE_SIZE);

		return row * TILE_COLUMNS + column;
	}

    virtual ~PositionNormaliser() = default;
};