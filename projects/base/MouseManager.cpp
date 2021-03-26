#include "MouseManager.h"
#include <iostream>


void MouseManager::processClick(sf::Vector2i mousePos, Grid *mapGrid, Grid *toolGrid){
	mapGrid->selectedTile = nullptr;

	if (toolGrid->selectedTile != nullptr && toolGrid->fetchTile(mousePos) != nullptr)
		toolGrid->selectedTile = nullptr;

	if (mapGrid->selectedTile == nullptr)
		mapGrid->selectedTile = mapGrid->fetchTile(mousePos);
	if (toolGrid->selectedTile == nullptr)
		toolGrid->selectedTile = toolGrid->fetchTile(mousePos);

	//place selected tile on map
	if (toolGrid->selectedTile != nullptr && toolGrid->selectedTile->sprite.getTexture() != nullptr && mapGrid->selectedTile != nullptr && mapGrid->selectedTile->isInTile(mousePos.x, mousePos.y)) {
		sf::Sprite sprite = toolGrid->selectedTile->sprite;
		sprite.setPosition(sf::Vector2f(mapGrid->selectedTile->x, mapGrid->selectedTile->y));
		mapGrid->selectedTile->setTexture(toolGrid->selectedTile->textureName);
		mapGrid->selectedTile = nullptr;
	}

	//remove tiles;
	if (mapGrid->selectedTile != nullptr && mapGrid->selectedTile->sprite.getTexture() != nullptr && mapGrid->selectedTile->isInTile(mousePos.x, mousePos.y)) {
		mapGrid->selectedTile->removeSprite();
		mapGrid->selectedTile = nullptr;
	}
}


