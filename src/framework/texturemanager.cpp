#include "texturemanager.h"

Purity::TextureManager::TextureManager()
{
}

const sf::Texture* Purity::TextureManager::getTexture(const boost::filesystem::path& texturePath)
{
    if (!isTextureUsed(texturePath))
    {
        addTexture(texturePath);
    }

    return textureMap[texturePath].get();
}

bool Purity::TextureManager::isTextureUsed(const boost::filesystem::path& texturePath) const
{
    auto found = textureMap.find(texturePath);

    if (found == textureMap.end())
    {
        return false;
    }

    return true;
}

void Purity::TextureManager::addTexture(const boost::filesystem::path& texturePath)
{
    textureMap[texturePath] = std::unique_ptr<sf::Texture>(new sf::Texture());
    textureMap[texturePath]->loadFromFile(texturePath.string());
}