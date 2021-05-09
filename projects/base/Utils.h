#pragma once
#include "SFML/Graphics.hpp"
class Utils
{

public:
	static bool collides(int x, int y, sf::FloatRect rect);
	static bool collides(sf::FloatRect rect1, sf::FloatRect rect2);
	static int getRandom(int min, int max);
};

