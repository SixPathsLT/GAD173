#include "Grid.h"
#include <iostream>
#include "example.h"

	sf::Font font;

	sf::Color Grid::HIGHLIGHT_COLOR = sf::Color(0, 255, 0, 50);
	sf::Color Grid::TRANSPARENT_COLOR = sf::Color(0, 0, 0, 0);

	Tile* selectedTile = nullptr;

	Grid::Grid(int totalRows, int totalColumns, int startX, int startY, double spacing) {
		font.loadFromFile("data/bluehigh.ttf");

		rows = totalRows;
		columns = totalColumns;

		int index = 0;
		//creates each tile and sets it in the tiles[] array
		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) { 
				int x = startX + (column * TILE_SIZE) * spacing;
				int y = startY + (row * TILE_SIZE) * spacing;

				tiles[index] = Tile(index, x, y);
				index++;
			}
		}
	}

	void Grid::draw(sf::RenderWindow& m_window) {
		for (int i = 0; i < Grid::getSize(); i++) {
			Tile *tile = &tiles[i];

			sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

			//used to toggle on/off the map grid lines
			if (showLines)
				tile->tileShape.setOutlineThickness(1);
			else
				tile->tileShape.setOutlineThickness(0);

			if (tile->isInTile(mousePos.x, mousePos.y)) { //checks if the mouse cursor is inside the current tile, then highlight that tile.
				tile->tileShape.setFillColor(HIGHLIGHT_COLOR);
				tile->tileShape.setOutlineColor(sf::Color::Green);
			} else if (selectedTile == tile && selectedTile->sprite.getTexture() != nullptr) { // outlines the selected tile.
				selectedTile->tileShape.setOutlineColor(sf::Color::Magenta);
			} else { // resets any color modifications done to the tile
				tile->tileShape.setFillColor(TRANSPARENT_COLOR);
				tile->tileShape.setOutlineColor(sf::Color::White);
			}

			//draws the tile shape itself
			m_window.draw(tile->tileShape);

			//draws the sprite on the tile
			if (tile->showSprite && tile->textureName.length() > 0)
				m_window.draw(tile->sprite);

			if (showTileInfo) {
				sf::Text tileInfo;
				tileInfo.setFont(font);
				tileInfo.setString(std::to_string(tile->id));
				tileInfo.setCharacterSize(15);
				tileInfo.setPosition(5 + tile->x, tile->y);

				m_window.draw(tileInfo);
			}
		}

		//visually shows selected sprite for placements, by following mouse cursor
		if (selectedTile != nullptr && selectedTile->sprite.getTexture() != nullptr) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

			sf::Sprite sprite = selectedTile->sprite;
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 170));
			sprite.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
			
			m_window.draw(sprite);
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





