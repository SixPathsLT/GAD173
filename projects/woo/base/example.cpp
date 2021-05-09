#include "example.h"
#include <iostream>
#include "Grid.h"
#include "ResourceManager.h"
#include "MouseManager.h"
#include "AnimatedSprite.h"

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

	//loads resources
	ResourceManager::init();

	//creates desirable grid (rows, columns, start loc X, start loc Y)
	mapGrid = Grid(10, 15, MAP_GRID_START_X, MAP_GRID_START_Y);
	//creates desired tile dimensions (sizeX, sizeY, spacing)
	mapGrid.createTiles(100, 45);


	//loads default map
	ResourceManager::loadMap(mapGrid);
	//set the default tab
	selectedTab = ToolTab::DRAW;


	////blockAnimator.setAnimation(AnimatedSprite::BLOCK, 500);
	//blockAnimator.play(false);

	/*std::string line = "Bricks1 - 55 - 56 - 57 - 58 - 80 - 83 - 105 - 108 - 112 - 118 - 130";

	std::string delimiter = " - ";
	int index = 0;

	while (index >= 0) {
		index = line.find(delimiter); // updates the next index where the specified string is located at

		std::string word = line.substr(0, index); // process this data
		line = line.substr(index + delimiter.length()); // updates the line

		std::cout << word << std::endl;
	}*/

	/*std::string data = "341, 1, 344, 4, 5, 6, 7";

	int startIndex = 0;
	int commaIndex = data.find(",");

	while (true) {
		int cutCount = commaIndex - startIndex;
		std::string word = data.substr(startIndex, cutCount);

		startIndex = (commaIndex + 1);

		std::cout << word << std::endl;

		if (commaIndex == -1)
			break;

		commaIndex = data.find(",", startIndex);
	}*/
	
	return true;
}


void Example::update(float deltaT)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window.hasFocus())
	{
		m_running = false;
	}


	ImGui::Begin("Toolbox");

		std::map<std::string, sf::Texture*>::iterator iterator;
		for (iterator = ResourceManager::TEXTURES.begin(); iterator != ResourceManager::TEXTURES.end(); iterator++) {
			if (iterator->first.empty() || iterator->second == nullptr || iterator->first.find("tool_") != 0)
				continue;

			sf::Sprite sprite;
			sprite.setTexture(*iterator->second);
			sprite.setScale(44.f / iterator->second->getSize().x, 44.f / iterator->second->getSize().y);

			ImGui::SameLine();

			bool highlight = false;

			std::string key = iterator->first;
			if ((key == "tool_clear_map" && selectedTab == ToolTab::CLEAR_MAP)
				|| (key == "tool_settings" && selectedTab == ToolTab::SETTINGS)
				|| (key == "tool_info" && selectedTab == ToolTab::INFO)
				|| (key == "tool_draw" && selectedTab == ToolTab::DRAW)) {
				highlight = true;
			}

			if (ImGui::ImageButton(sprite, 2, sf::Color::Transparent, highlight ? sf::Color(0, 149, 206) : sf::Color::White)) {
				std::string key = iterator->first;
				
				if (key == "tool_clear_map") {		
					selectedTab = ToolTab::CLEAR_MAP;
				} else if (key == "tool_settings") {
					selectedTab = ToolTab::SETTINGS;
				} else if (key == "tool_info") {
					selectedTab = ToolTab::INFO;
				} else if (key == "tool_draw") {
					selectedTab = ToolTab::DRAW;
				}

				if (selectedTab != ToolTab::DRAW) {
					ResourceManager::selectedTexture = nullptr;
				}
			}
		}


		switch (selectedTab) {
		case ToolTab::CLEAR_MAP:
			ImGui::BeginChild("confirm_clear_map", ImVec2(0, 65), true);
			ImGui::Text("Are you sure you want to clear\nthe Entire Map?");

			if (ImGui::Button("Yes")) {
				selectedTab = ToolTab::DRAW;
				ResourceManager::clearMap(mapGrid);
			}

			ImGui::SameLine();

			if (ImGui::Button("No")) {
				selectedTab = ToolTab::DRAW;
			}
			ImGui::EndChild();

			break;
		case ToolTab::SETTINGS:
		{
			ImGui::BeginChild("file_panel", ImVec2(0, fileExists ? 145 : 75), true);
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
			ImGui::EndChild();

			if (ImGui::Button("Print Map Details")) { //outputs the current map grid data, which can be used to save/load a map.
				std::string mapDetails = ResourceManager::getMapDetails(mapGrid);

				if (mapDetails.length() > 0)
					std::cout << "=== Printing Map Details (TEXTURE_NAME - TILE_ID[]) ===" << std::endl << mapDetails << std::endl;
				else
					std::cout << "=== Map has no set textures. Click a texture from the tool grid and then place it on the Map Grid. ===" << std::endl;

			}

			if (ImGui::Button("Exit")) {
				m_running = false;
			}
		}
			break;
		case ToolTab::INFO:
			ImGui::BeginChild("info_panel", ImVec2(0, 0), true);
				ImGui::Checkbox("Grid Lines", &mapGrid.showLines);
				//ImGui::SameLine();
				ImGui::Checkbox("Tile Ids", &mapGrid.showTileIds);
				ImGui::Checkbox("Mouse Info", &MouseManager::showMouseInfo);
				//ImGui::SameLine();
				ImGui::Checkbox("Texture Names", &Tile::SHOW_TEXTURE_NAMES);
			ImGui::EndChild();
			break;
		case ToolTab::DRAW:
			float sprite_size = 64.f;
			float columns = 3.0;
			float spacing = 1.31;
			ImGui::Text("Textures:");

			ImGui::BeginChild("loaded_textures", ImVec2(sprite_size * (columns * spacing), sprite_size * 7.1), true);

				int index = 0;

				for (iterator = ResourceManager::TEXTURES.begin(); iterator != ResourceManager::TEXTURES.end(); iterator++) {
					if (iterator->first.empty() || iterator->second == nullptr || !ResourceManager::isDrawableTexture(iterator->first))
						continue;

					if (index % (int)columns != 0)
						ImGui::SameLine();

					index++;

					sf::Sprite sprite;
					sprite.setTexture(*iterator->second);
					sprite.setScale(sprite_size / iterator->second->getSize().x, sprite_size / iterator->second->getSize().y);

					if (ImGui::ImageButton(sprite, 3))
						ResourceManager::selectedTexture = iterator->second;
				}
			ImGui::EndChild();
			break;
		}

	ImGui::End();

	/*ImGui::Begin("File Manager");
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

	ImGui::End();*/


/*	ImGui::Begin("Settings");


	ImGui::Checkbox("Grid Lines", &mapGrid.showLines);
	ImGui::SameLine();
	ImGui::Checkbox("Tile Ids", &mapGrid.showTileIds);

	ImGui::Checkbox("Mouse Info", &MouseManager::showMouseInfo);
	ImGui::SameLine();
	ImGui::Checkbox("Texture Names", &Tile::showTextureNames);

	if (ImGui::Button("Print Map Details")) { //outputs the current map grid data, which can be used to save/load a map.
		std::string mapDetails = ResourceManager::getMapDetails(mapGrid);

		if (mapDetails.length() > 0)
			std::cout << "=== Printing Map Details (TEXTURE_NAME - TILE_ID[]) ===" << std::endl << mapDetails << std::endl;
		else
			std::cout << "=== Map has no set textures. Click a texture from the tool grid and then place it on the Map Grid. ===" << std::endl;

	}
	ImGui::SameLine();
	 if (ImGui::Button("Clear Map")) {	//removes all textures from the tiles on the map grid
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


	ImGui::End();*/


}

void Example::render()
{
	m_window.draw(*m_backgroundSprite);

	MouseManager::process(m_window, &mapGrid);

	mapGrid.draw(m_window);

}

void Example::cleanup()
{
	delete m_backgroundSprite;

}



