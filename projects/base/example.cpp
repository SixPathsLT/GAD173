#include "example.h"
#include <iostream>
#include "Grid.h"
#include "ResourceManager.h"
#include "MouseManager.h"

Example::Example(): App()
{
}

Example::~Example()
{
}

Example &Example::inst()
{
	static Example s_instance;
	return s_instance;
}



bool Example::start()
{

	m_backgroundSprite = kage::TextureManager::getSprite("data/sky.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window.getSize().x) / resolution.x, float(m_window.getSize().y) / resolution.y);

	//creates desirable grid (rows, columns, start loc X, start loc Y, spacing)
	mapGrid = Grid(15, 25, MAP_GRID_START_X, MAP_GRID_START_Y);
	toolGrid = Grid(8, 3, TOOL_GRID_START_X, TOOL_GRID_START_Y, 1.2);

	//loads textures for the tool grid
	ResourceManager::init(toolGrid);

	//loads default map
	ResourceManager::loadMap("custom_map_1", mapGrid);

	return true;
}



void Example::update(float deltaT)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window.hasFocus())
	{
		m_running = false;
	}

	ImGui::Begin("Kage2D");


	if (ImGui::Button("Toggle Grid Lines")) { //enables/disables the map grid lines
		mapGrid.showLines = !mapGrid.showLines;
	} else if(ImGui::Button("Toggle Tile Info")) { //enables/disables info of each tile such as the tile id (index)
		mapGrid.showTileInfo = !mapGrid.showTileInfo;
	} else if (ImGui::Button("Load Map 1")) {
		ResourceManager::loadMap("custom_map_1", mapGrid);
	} else if (ImGui::Button("Load Map 2")) {
		ResourceManager::loadMap("custom_map_2", mapGrid);
	} else if (ImGui::Button("Save as Map 1")) {
		ResourceManager::saveMap("custom_map_1", mapGrid);
	} else if (ImGui::Button("Save as Map 2")) {
		ResourceManager::saveMap("custom_map_2", mapGrid);
	} else if (ImGui::Button("Print Map Details (future saving/loading)")) { //outputs the current map grid data, which can be used to save/load a map.
		std::string mapDetails = ResourceManager::getMapDetails(mapGrid);

		if (mapDetails.length() > 0)
			std::cout << "=== Printing Map Details (TEXTURE_NAME - TILE_ID[]) ===" << std::endl << mapDetails << std::endl;
		else
			std::cout << "=== Map has no set textures. Click a texture from the tool grid and then place it on the Map Grid. ===" << std::endl;

	} else if (ImGui::Button("CLEAR ENTIRE MAP")) {	//removes all textures from the tiles on the map grid
		ResourceManager::clearMap(mapGrid);
	}


	if(ImGui::Button("Exit"))
	{ 
		m_running = false;
	}
	ImGui::End();
}

void Example::render()
{
	m_window.draw(*m_backgroundSprite);

	mapGrid.draw(m_window);
	toolGrid.draw(m_window);

}


void Example::processMouseClick(sf::Vector2i mousePos) {
	MouseManager::processClick(mousePos, &mapGrid, &toolGrid);
}

void Example::cleanup()
{
	delete m_backgroundSprite;

}



