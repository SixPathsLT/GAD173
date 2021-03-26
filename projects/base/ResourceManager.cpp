#include "ResourceManager.h"
#include "kage2dutil/texture_manager.h"
#include "Grid.h"
#include "example.h"

#define TOTAL_FILES 50

std::map<std::string, sf::Texture*> ResourceManager::TEXTURES;


std::string files[TOTAL_FILES][2] = {
	{ "Water1", "data/MapEditorData/Water1.png" },
	{ "Water2", "data/MapEditorData/Water2.png" },
	{ "Bricks1", "data/MapEditorData/Bricks1.png" },
	{ "Bricks2", "data/MapEditorData/Bricks2.png" },
	{ "Lava1", "data/MapEditorData/Lava1.png" },
	{ "Lava2", "data/MapEditorData/Lava2.png" },
	{ "Grass1", "data/MapEditorData/Grass1.png" },
	{ "Wood", "data/MapEditorData/Wood.png" },

};


void ResourceManager::init(Grid &grid) {
	for (int i = 0; i < TOTAL_FILES; i++) {
		load(files[i][0], files[i][1]);
	}

	//sets the loaded textures for the tool grid
	for (int i = 0; i < TOTAL_FILES; i++) {
		std::string key = files[i][0];
		if (key.empty())
			break;

		grid.tiles[i].setTexture(key);
	}
}

//loads the texture from the engine and saves it in our TEXTURES map
void ResourceManager::load(std::string name, std::string path) {
	if (name.length() < 1)
		return;

	TEXTURES[name] = kage::TextureManager::getTexture(path);
}

void ResourceManager::saveMap(std::string fileName, Grid &grid) {
	std::string mapDetails = ResourceManager::getMapDetails(grid);
	std::ofstream file("data/MapSaves/" + fileName + ".txt");
	file << mapDetails;
	file.close();
}


void ResourceManager::loadMap(std::string fileName, Grid &grid) {
	std::ifstream file("data/MapSaves/" + fileName + ".txt");
	if (!file.good()) { // checks if file exists
		std::cout << "File '" << fileName << "' does not exist." << std::endl;
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
	std::istringstream iss(data);
	std::string word;
	std::string textureName;

	while (iss >> word) {
		if (textureName.length() < 1) {
			textureName = word;
		} else if (word != "-") {
			//convert string word to int
			std::stringstream ss(word);
			int tileId = 0;
			ss >> tileId;

			//sets the desired texture to the specified index on the map grid.
			grid.tiles[tileId].setTexture(textureName);
		}
	}
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



