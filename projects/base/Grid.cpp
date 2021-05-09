#include "Grid.h"
#include <iostream>
#include "ResourceManager.h"
#include "AnimatedSprite.h"

	Grid::Grid()
	{
	}

	Grid::Grid(int rows, int columns, int startX, int startY) {
		this->startX = startX;
		this->startY = startY;
		this->rows = rows;
		this->columns = columns;
	}


 	void Grid::createTiles(int sizeX, int sizeY, double spacing) {
		if (spacing < 1)
			spacing = 1;

		int index = 0;
		//creates each tile and sets it in the tiles[] array
		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) {
				int x = startX + (column * sizeX) * spacing;
				int y = startY + (row * sizeY) * spacing;

				tiles[index] = Tile(index, sizeX, sizeY, x, y);
				index++;
			}
		}

		rectShape = sf::RectangleShape(sf::Vector2f(tiles[0].width * getColumns(), 1100));
		rectShape.setPosition(tiles[0].startX, tiles[0].startY);
		rectShape.setFillColor(sf::Color::Transparent);
		rectShape.setOutlineColor(sf::Color::Black);
		rectShape.setOutlineThickness(5);
	}
	
	void Grid::update(sf::RenderWindow& m_window) {
		for (int i = 0; i < getSize(); i++) {
			Tile *tile = &tiles[i];
			sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

			if (tile->showSprite && tile->textureName.length() > 0)
				m_window.draw(*tile->sprite);

			tile->animatedSprite.update();

		}
	}

	void Grid::draw(sf::RenderWindow& m_window) {
		for (int i = 0; i < getSize(); i++) {
			Tile *tile = &tiles[i];

			sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);


			//draws the sprite on the tile
			if (tile->showSprite && tile->textureName.length() > 0)
				m_window.draw(*tile->sprite);

			tile->animatedSprite.render(m_window);

		}

	}

	Tile* Grid::fetchTile(sf::Vector2i mousePos) {
		for (int i = 0; i < (rows * columns); i++) {
			Tile *tile = &tiles[i];

			if (tile->isInTile(mousePos.x, mousePos.y))
				return tile;
		}
		return nullptr;
	}


	int Grid::getSize() {
		int size = (rows * columns);
		if (size > TOTAL_TILES_AMOUNT)
			size = TOTAL_TILES_AMOUNT;

		return size;
	}





