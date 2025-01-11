#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> 

const float SCREEN_WIDTH = 1000.0f;//must be a multiple of the TILE_SIZE
const float SCREEN_HEIGHT = 800.0f;

const float VIEWPORT_WIDTH = 600.0f;//can be any size
const float VIEWPORT_HEIGHT = 500.0f;

const float TILE_SIZE = 50.0f;//define the size of the square tiles that make up the world

const int TILE_ROWS = SCREEN_HEIGHT / TILE_SIZE;
const int TILE_COLUMNS = SCREEN_WIDTH / TILE_SIZE;

const int MAX_MOVES_PER_TURN = 3;

static int playerOneUnits = 4;
static int playerTwoUnits = 4;
static int playerThreeUnits = 4;
static int playerFourUnits = 4;