#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"

class MouseManager {

public:
	static sf::Text *mouseInfo;
	static bool showMouseInfo;
	static void process(sf::RenderWindow &m_window, Grid *mapGrid);


};

