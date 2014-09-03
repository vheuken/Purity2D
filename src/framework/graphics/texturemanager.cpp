#include "texturemanager.h"

bool Purity::TextureManager::sIsEnabled = true;

Purity::Texture* Purity::TextureManager::getTexture(const std::string& texturePath)
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

bool Purity::TextureManager::isTextureUsed(const std::string& texturePath) const
{
    auto found = textureMap.find(texturePath);

    if (found == textureMap.end())
    {
        return false;
    }

    return true;
}

void Purity::TextureManager::addTexture(const std::string& texturePath)
{
    textureMap[texturePath] = std::unique_ptr<Texture>(new Texture());
    textureMap[texturePath]->loadFromFile(texturePath);
}
