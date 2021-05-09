#include "MouseManager.h"
#include <iostream>
#include "ResourceManager.h"

sf::Text *MouseManager::mouseInfo = new sf::Text();
bool MouseManager::showMouseInfo = true;

//remove tiles
void removeTile(Grid *mapGrid, sf::Vector2i mousePos) {
	if (mapGrid->selectedTile != nullptr && mapGrid->selectedTile->sprite->getTexture() != nullptr && mapGrid->selectedTile->isInTile(mousePos.x, mousePos.y)) {
		mapGrid->selectedTile->removeSprite();
		mapGrid->selectedTile = nullptr;
	}
}

void MouseManager::process(sf::RenderWindow &m_window, Grid *mapGrid) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

	if (MouseManager::showMouseInfo) {
		mouseInfo->setFont(ResourceManager::FONT_BLUE_HIGH);
		mouseInfo->setString("X: " + std::to_string(mousePos.x) + "\nY: " + std::to_string(mousePos.y));
		mouseInfo->setCharacterSize(20);
		mouseInfo->setPosition(1575, 3);
		m_window.draw(*mouseInfo);
	}

	bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

	if (!mousePressed)
		return;

	mapGrid->selectedTile = mapGrid->fetchTile(mousePos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		//place selected tile on map
		if (ResourceManager::selectedTexture != nullptr && mapGrid->selectedTile != nullptr && mapGrid->selectedTile->isInTile(mousePos.x, mousePos.y)) {
			std::string textureName = ResourceManager::getKey(ResourceManager::selectedTexture);
			if (textureName.length() < 1)
				return;

			sf::Sprite sprite;
			sprite.setTexture(*ResourceManager::selectedTexture);
			sprite.setPosition(sf::Vector2f(mapGrid->selectedTile->startX, mapGrid->selectedTile->startY));
			
			
			mapGrid->selectedTile->setTexture(textureName);
			mapGrid->selectedTile = nullptr;
		}

		//remove tiles
		//removeTile(mapGrid, mousePos); // disabled for now, so that we only delete textures with right click.
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		removeTile(mapGrid, mousePos);
	}
}



