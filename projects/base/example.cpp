#include "example.h"
#include <iostream>
#include "Grid.h"
#include "ResourceManager.h"
#include "MouseManager.h"

Example::Example() : App()
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
	ResourceManager::loadMap(mapGrid);


	return true;
}


void Example::update(float deltaT)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window.hasFocus())
	{
		m_running = false;
	}
	

	ImGui::Begin("File Manager");
		int fileNameSize = IM_ARRAYSIZE(ResourceManager::fileName);
		ImGui::Text("File name:");
		ImGui::InputText("##file_name", ResourceManager::fileName, fileNameSize);

		if (ImGui::Button("Load Map")) {
			if (fileNameSize > 0)
				ResourceManager::loadMap(mapGrid);
		} 

		ImGui::SameLine();

		if (ImGui::Button("Save Map")) {
			if (fileNameSize > 0) {
				std::ifstream file("data/MapSaves/" + ((std::string) ResourceManager::fileName) + ".txt");

				if (file.good()) {
					fileExists = true;
				} else {
					ResourceManager::saveMap(mapGrid);
				}
			}
		} 

		if (fileExists) {
			ImGui::BeginChild("warning_message", ImVec2(0, 65), true);

				std::string warningMessage = ((std::string) ResourceManager::fileName) + " already exists. \nAre you sure you want to overwrite?";
				ImGui::Text(warningMessage.c_str());

				if (ImGui::Button("Yes")) {
					fileExists = false;
					ResourceManager::saveMap(mapGrid);
				}

				ImGui::SameLine();

				if (ImGui::Button("No")) {
					fileExists = false;
				}

			ImGui::EndChild();
		}

	ImGui::End();


	ImGui::Begin("Kage2D");


	ImGui::Checkbox("Grid Lines", &mapGrid.showLines);
	ImGui::Checkbox("Tile Info", &mapGrid.showTileInfo);

	if (ImGui::Button("Print Map Details")) { //outputs the current map grid data, which can be used to save/load a map.
		std::string mapDetails = ResourceManager::getMapDetails(mapGrid);

		if (mapDetails.length() > 0)
			std::cout << "=== Printing Map Details (TEXTURE_NAME - TILE_ID[]) ===" << std::endl << mapDetails << std::endl;
		else
			std::cout << "=== Map has no set textures. Click a texture from the tool grid and then place it on the Map Grid. ===" << std::endl;

	}
	else if (ImGui::Button("Clear Map")) {	//removes all textures from the tiles on the map grid
		requestedClearMap = !requestedClearMap;
	} else if (requestedClearMap) {
		ImGui::BeginChild("confirm_clear_map", ImVec2(0, 55), true);
			ImGui::Text("Are you sure you want to clear the map?");

			if (ImGui::Button("Yes")) {
				requestedClearMap = false;
				ResourceManager::clearMap(mapGrid);
			}

			ImGui::SameLine();

			if (ImGui::Button("No")) {
				requestedClearMap = false;
			}
		ImGui::EndChild();

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

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	MouseManager::process(mousePos, &mapGrid, &toolGrid);

	mapGrid.draw(m_window);
	toolGrid.draw(m_window);

}

void Example::cleanup()
{
	delete m_backgroundSprite;

}



