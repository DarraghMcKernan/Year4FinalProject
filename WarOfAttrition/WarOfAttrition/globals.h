#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> 

const float SCREEN_WIDTH = 1000.0f;
const float SCREEN_HEIGHT = 800.0f;

const float VIEWPORT_WIDTH = 600.0f;
const float VIEWPORT_HEIGHT = 500.0f;

const float TILE_SIZE = 50.0f;

const int TILE_ROWS = SCREEN_HEIGHT / TILE_SIZE;
const int TILE_COLUMNS = SCREEN_WIDTH / TILE_SIZE;