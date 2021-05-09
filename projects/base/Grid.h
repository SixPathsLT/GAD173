#pragma once

#include "Tile.h"
#include <SFML/Graphics.hpp>

#define MAP_GRID_START_X 75
#define MAP_GRID_START_Y 55
#define TOOL_GRID_START_X 1660
#define TOOL_GRID_START_Y 10

#define TOTAL_TILES_AMOUNT 500

class Grid {

private:
	int rows = 0;
	int columns = 0;
	int startX = 0;
	int startY = 0;


public:
	sf::RectangleShape rectShape;

	Grid();
	Grid(int totalRows, int totalColumns, int startX = 0, int startY = 0);

	Tile tiles[TOTAL_TILES_AMOUNT];

	void createTiles(int sizeX, int sizeY, double spacing = 1);
	void update(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	Tile* fetchTile(sf::Vector2i);
	int getSize();

	inline int getRows() { return rows; }
	inline int getColumns() { return columns; }
};

