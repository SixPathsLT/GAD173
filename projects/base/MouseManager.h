#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"

class MouseManager {

public:
	static void process(sf::Vector2i mousePos, Grid *mapGrid, Grid *toolGrid);

};

