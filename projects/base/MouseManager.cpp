#include "MouseManager.h"
#include <iostream>


//remove tiles
void removeTile(Grid *mapGrid, sf::Vector2i mousePos) {
	if (mapGrid->selectedTile != nullptr && mapGrid->selectedTile->sprite.getTexture() != nullptr && mapGrid->selectedTile->isInTile(mousePos.x, mousePos.y)) {
		mapGrid->selectedTile->removeSprite();
		mapGrid->selectedTile = nullptr;
	}
}

void MouseManager::process(sf::Vector2i mousePos, Grid *mapGrid, Grid *toolGrid) {
	bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

	if (!mousePressed)
		return;

	mapGrid->selectedTile = nullptr;

	if (toolGrid->selectedTile != nullptr && toolGrid->fetchTile(mousePos) != nullptr)
		toolGrid->selectedTile = nullptr;

	if (mapGrid->selectedTile == nullptr)
		mapGrid->selectedTile = mapGrid->fetchTile(mousePos);
	if (toolGrid->selectedTile == nullptr)
		toolGrid->selectedTile = toolGrid->fetchTile(mousePos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		//place selected tile on map
		if (toolGrid->selectedTile != nullptr && toolGrid->selectedTile->sprite.getTexture() != nullptr && mapGrid->selectedTile != nullptr && mapGrid->selectedTile->isInTile(mousePos.x, mousePos.y)) {
			sf::Sprite sprite = toolGrid->selectedTile->sprite;
			sprite.setPosition(sf::Vector2f(mapGrid->selectedTile->x, mapGrid->selectedTile->y));
			mapGrid->selectedTile->setTexture(toolGrid->selectedTile->textureName);
			mapGrid->selectedTile = nullptr;
		}

		//remove tiles
		removeTile(mapGrid, mousePos);
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		removeTile(mapGrid, mousePos);
	}
}



