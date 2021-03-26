#pragma once

#include "Tile.h"
#include <SFML/Graphics.hpp>

#define MAP_GRID_START_X 0
#define MAP_GRID_START_Y 0
#define TOOL_GRID_START_X 1660
#define TOOL_GRID_START_Y 10

#define TOTAL_TILES_AMOUNT 500

class Grid {

private:
	int rows = 0;
	int columns = 0;

public:
	Grid(int totalRows = 1, int totalColumns = 1, int startX = 0, int startY = 0, double spacing = 1);
	Tile tiles[TOTAL_TILES_AMOUNT];

	static sf::Color HIGHLIGHT_COLOR;
	static sf::Color TRANSPARENT_COLOR;

	bool showLines = true;
	bool showTileInfo = false;

	Tile* selectedTile = nullptr;

	void draw(sf::RenderWindow&);
	Tile* fetchTile(sf::Vector2i);
	int getSize();

};

