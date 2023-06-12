#include "TextureCache.h"

std::unordered_map<std::string, sf::Texture> TextureCache::textureCache;

sf::Texture& TextureCache::getTexture(const std::string& fileName)
{
	// 如果texture還沒被載入
	if (textureCache.find(fileName) == textureCache.end()) {
		// 建立texture
		sf::Texture texture = sf::Texture();

		// 載入texture
		std::cout << "Texture: " << fileName << " is loading..." << std::endl;

		try {
			if (texture.loadFromFile(fileName)) {
				textureCache[fileName] = texture;
				std::cout << "Texture: " << fileName << " loaded." << std::endl;
				return textureCache[fileName];
			}
			else {
				throw("failed to load");
			}
		}
		catch (std::exception e) {
			std::cout << "Texture: " << fileName << " failed to load." << std::endl;
		}

	}

	return textureCache[fileName];
}
