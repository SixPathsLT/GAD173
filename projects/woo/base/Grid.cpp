#include "Grid.h"
#include <iostream>
#include "example.h"
#include "ResourceManager.h"
#include "AnimatedSprite.h"

	sf::Color Grid::HIGHLIGHT_COLOR = sf::Color(0, 255, 0, 50);
	//sf::Color Grid::TRANSPARENT_COLOR = sf::Color(0, 0, 0, 0);

	Tile* selectedTile = nullptr;

	const int TOTAL_COINS = 5;
	AnimatedSprite coinAnimator[TOTAL_COINS];

	Grid::Grid()
	{
	}

	Grid::Grid(int rows, int columns, int startX, int startY) {
		this->startX = startX;
		this->startY = startY;
		this->rows = rows;
		this->columns = columns;

		tileIndexInfo->setFont(ResourceManager::FONT_BLUE_HIGH);
		tileIndexInfo->setCharacterSize(15);

		for (int i = 0; i < TOTAL_COINS; i++) {
			
			coinAnimator[i].setAnimation(AnimatedSprite::COIN, 90);
			coinAnimator[i].spriteSheet.setPosition(250 * (1 + i), 550);
			coinAnimator[i].spriteSheet.setScale(0.5, 0.5);
			coinAnimator[i].play(true);
		}

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
	}

	void Grid::draw(sf::RenderWindow& m_window) {
		for (int i = 0; i < getSize(); i++) {
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
			} else { // resets any color modifications done to the tile
				tile->tileShape.setFillColor(sf::Color::Transparent);
				tile->tileShape.setOutlineColor(sf::Color::White);
			}

			//draws the tile shape itself
			m_window.draw(tile->tileShape);

			//draws the sprite on the tile
			if (tile->showSprite && tile->textureName.length() > 0)
				m_window.draw(*tile->sprite);

			tile->animatedSprite.render(m_window);

			if (Tile::SHOW_TEXTURE_NAMES)
				m_window.draw(*tile->tileInfo);

			if (showTileIds) {
				tileIndexInfo->setString(std::to_string(tile->id));
				tileIndexInfo->setPosition(5 + tile->startX, tile->startY);

				m_window.draw(*tileIndexInfo);
			}
		}


		for (int i = 0; i < TOTAL_COINS; i++) {
			coinAnimator[i].render(m_window);
		}



		//visually shows selected sprite for placements, by following mouse cursor
		if (ResourceManager::selectedTexture != nullptr) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

			sf::Sprite sprite;
			sf::Texture texture = *ResourceManager::selectedTexture;
			sprite.setTexture(texture);
			sprite.scale(94.f / texture.getSize().x, 44.f / texture.getSize().y);
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





