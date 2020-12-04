#pragma once
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

class TextureLoader {
public: 
	enum TextureId {
		ANT_115x149,
		ANT_230x297,
		ANT_460x593,
		TILE_20x20,
		ANT_SIMPLIFIED_1x2,
		ANTHILL_50x50,
		NEURON_50x50
	};

private:
	static const int numberOfTextures = 7;
	static const std::string relativePathToResources;

	static bool areTexturesLoaded;
	static std::vector<std::shared_ptr<sf::Texture>> textures;

	static void loadIfNotLoaded();
	static void loadTexturesFromFiles();
public:
	static const std::shared_ptr<sf::Texture> getTexture(TextureId id);
};