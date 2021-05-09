#include "Utils.h"


bool Utils::collides(int x, int y, sf::FloatRect rect)
{
	return collides(sf::FloatRect(x, y, 1, 1), rect);

	//works but prefer overloading :D
	//return (x > rect.left && y > rect.top && x < (rect.left + rect.width) && y < (rect.top + rect.height));
}

bool Utils::collides(sf::FloatRect rect1, sf::FloatRect rect2)
{
	return rect1.intersects(rect2);

	// formula from TDD works... BUT intersects exists... so why not :)
	/*return (rect1.left < (rect2.left + rect2.width)
		&& (rect1.left + rect1.width) > rect2.left
		&& rect1.top < (rect2.top + rect2.height)
		&& (rect1.height + rect1.top) > rect2.top);*/
}

int Utils::getRandom(int min, int max)
{
	return rand() % max + min;
}
