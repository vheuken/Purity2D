#include "texturemanager.h"

bool Purity::TextureManager::sIsEnabled = true;

Purity::TextureManager::TextureManager()
{
}

const sf::Texture* Purity::TextureManager::getTexture(const boost::filesystem::path& texturePath)
{
    if (sIsEnabled == true)
    {
        if (!isTextureUsed(texturePath))
        {
            addTexture(texturePath);
        }

        return textureMap[texturePath].get();
    }

    return nullptr;
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
