#include "ResourceManager.h"
#include "kage2dutil/texture_manager.h"
#include "Grid.h"
#include "example.h"

#define TOTAL_FILES 50

int ResourceManager::TOTAL_LOADED_TEXTURES;

std::map<std::string, sf::Texture*> ResourceManager::TEXTURES;

sf::Texture *ResourceManager::selectedTexture;

char ResourceManager::fileName[26] = "custom_map_1";
sf::Font ResourceManager::FONT_BLUE_HIGH;

//TEMPORARILY DEFINED
std::string files[TOTAL_FILES][2] = {

	{ "Water1", "data/MapEditorData/Water1.png" },
	{ "Water2", "data/MapEditorData/Water2.png" },
	{ "Bricks1", "data/MapEditorData/Bricks1.png" },
	{ "Bricks2", "data/MapEditorData/Bricks2.png" },
	{ "Lava1", "data/MapEditorData/Lava1.png" },
	{ "Lava2", "data/MapEditorData/Lava2.png" },
	{ "Grass1", "data/MapEditorData/Grass1.png" },
	{ "Wood1", "data/MapEditorData/Wood1.png" },

	{ "Wood2", "data/MapEditorData/Wood2.png" },
	{ "Grass2", "data/MapEditorData/Grass2.png" },

	{ "Lava3", "data/MapEditorData/Lava3.png" },
	{ "RedBlock", "data/MapEditorData/RedBlock.png" },
	{ "Bricks3", "data/MapEditorData/Bricks3.png" },

	//breakout blocks
	{ "blue_block", "data/MapEditorData/blocks/blue_block.png" },
	{ "red_block", "data/MapEditorData/blocks/red_block.png" },
	{ "green_block", "data/MapEditorData/blocks/green_block.png" },
	{ "orange_block", "data/MapEditorData/blocks/orange_block.png" },
	{ "yellow_block", "data/MapEditorData/blocks/yellow_block.png" },
	{ "purple_block", "data/MapEditorData/blocks/purple_block.png" },
	{ "teal_block", "data/MapEditorData/blocks/teal_block.png" },
	{ "brown_block", "data/MapEditorData/blocks/brown_block.png" },
	{ "grey_block", "data/MapEditorData/blocks/grey_block.png" },
	{ "cyan_block", "data/MapEditorData/blocks/cyan_block.png" },

	//editor tools
	{ "tool_draw", "data/MapEditorData/toolbox/draw.png" },
	{ "tool_settings", "data/MapEditorData/toolbox/settings.png" },
	{ "tool_info", "data/MapEditorData/toolbox/info.png" },
	{ "tool_clear_map", "data/MapEditorData/toolbox/clear_map.png" },

	//game data
	{ "coin_spritesheet", "data/GameData/coin.png" },
	{ "block_spritesheet", "data/GameData/block_sheet_1.png" },

};

void ResourceManager::init() {
	//load fonts here
	FONT_BLUE_HIGH.loadFromFile("data/bluehigh.ttf");

	//loads the texture from the engine and saves it in our TEXTURES map
	for (int i = 0; i < TOTAL_FILES; i++) {
		std::string name = files[i][0];
		if (name.length() < 1)
			break;
		std::string path = files[i][1];

		TEXTURES[name] = kage::TextureManager::getTexture(path);
	}

	TOTAL_LOADED_TEXTURES = getTotalLoadedTextures();
}

void ResourceManager::saveMap(Grid &grid) {
	std::string mapDetails = ResourceManager::getMapDetails(grid);

	std::ofstream file("data/MapSaves/" + ((std::string) ResourceManager::fileName) + ".txt");
	file << mapDetails;
	file.close();
}


void ResourceManager::loadMap(Grid &grid) {
	std::ifstream file("data/MapSaves/" + ((std::string) ResourceManager::fileName) + ".txt");
	if (!file.good()) { // checks if file exists
		std::cout << "File '" << ((std::string) ResourceManager::fileName) << "' does not exist." << std::endl;
		return;
	}

	ResourceManager::clearMap(grid); // clears current map grid before drawing on it.
	std::string line;

	while (std::getline(file, line)) {
		if (line.length() < 1)
			continue;

		loadMapData(line, grid);
	}
	file.close();
}

void ResourceManager::loadMapData(std::string data, Grid &grid) {
	int endIndex = data.find(" - ");
	std::string textureName = data.substr(0, endIndex); // extract the texture name
	data = data.substr(endIndex); // updates data to remove the texture name

	std::istringstream iss(data);
	std::string word;

	while (iss >> word) {
		if (word == "-" || TEXTURES[textureName] == nullptr)
			continue;

		int tileId = std::stoi(word);

		//sets the desired texture to the specified index on the map grid.
		grid.tiles[tileId].setTexture(textureName);
		
	}

	// following commented out code works also :)
	/*std::string textureName;
	std::string delimiter = " - ";
	int index = 0;

	while (index >= 0) {
		index = data.find(delimiter); // updates the next index where the specified string is located at

		std::string word = data.substr(0, index); // process this data

		if (textureName.length() < 1)
			textureName = word;
		else {
			int tileId = std::stoi(word);

			//sets the desired texture to the specified index on the map grid.
			grid.tiles[tileId].setTexture(textureName);
		}

		data = data.substr(index + delimiter.length()); // updates the line
	}*/
}

void ResourceManager::clearMap(Grid &grid) {
	for (int i = 0; i < grid.getSize(); i++) {
		Tile *tile = &grid.tiles[i];
		if (tile->textureName.length() < 1)
			continue;

		tile->removeSprite();
	}
}

std::string ResourceManager::getMapDetails(Grid &mapGrid) {
	//saves any tile data to map_textures if the tile has a texture on it
	std::map<std::string, std::string> map_textures;
	for (int i = 0; i < mapGrid.getSize(); i++) {
		Tile *tile = &mapGrid.tiles[i];
		if (tile->textureName.length() < 1)
			continue;

		std::string savedData = map_textures[tile->textureName];
		map_textures[tile->textureName] = savedData + " - " + std::to_string(tile->id);
	}

	std::string mapDetails;

	//iterates through map_textures to fetch each texture name, followed with all the tile id's that has that texture.
	std::map<std::string, std::string>::iterator iterator;
	for (iterator = map_textures.begin(); iterator != map_textures.end(); iterator++) {
		mapDetails += iterator->first + iterator->second + "\n";
	}

	return mapDetails;
}

//returns the texture name when provided with the pointer of the texture
std::string ResourceManager::getKey(sf::Texture *texture) {
	std::map<std::string, sf::Texture*>::iterator iterator;

	for (iterator = ResourceManager::TEXTURES.begin(); iterator != ResourceManager::TEXTURES.end(); iterator++) {
		if (iterator->first.empty() || iterator->second == nullptr || !ResourceManager::isDrawableTexture(iterator->first))
			continue;

		if (iterator->second == texture)
			return iterator->first;
	}

	return "";
}


int ResourceManager::getTotalLoadedTextures() {
	int count = 0;
	for (int i = 0; i < TOTAL_FILES; i++) {
		std::string name = files[i][0];
		if (name.length() < 1)
			break;
		
		count++;
	}

	return count;
}


bool ResourceManager::isDrawableTexture(std::string textureName) {
	if (textureName.find("tool_") != -1 || textureName.find("spritesheet") != -1)
		return false;

	return true;
}