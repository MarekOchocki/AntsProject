#include <AntsLib/Visualization/TextureLoader.hpp>

#include <iostream>

bool TextureLoader::areTexturesLoaded = false;
const std::string TextureLoader::relativePathToResources = "../res/";
std::vector<std::shared_ptr<sf::Texture>> TextureLoader::textures = std::vector<std::shared_ptr<sf::Texture>>();

void TextureLoader::loadIfNotLoaded()
{
	if (!areTexturesLoaded)
	{
		loadTexturesFromFiles();
		areTexturesLoaded = true;
	}
}

void TextureLoader::loadTexturesFromFiles()
{
	for (int i = 0; i < numberOfTextures; i++) {
		auto tex = std::make_shared<sf::Texture>();
		tex->loadFromFile(relativePathToResources + std::to_string(i) + ".png");
		textures.push_back(tex);
	}
}

const std::shared_ptr<sf::Texture> TextureLoader::getTexture(TextureLoader::TextureId id)
{
	loadIfNotLoaded();
	return textures[id];
}
