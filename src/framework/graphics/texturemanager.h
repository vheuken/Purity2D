#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <map>
#include <string>

#include "texture.h"

namespace Purity
{
class TextureManager
{
public:
    Texture* getTexture(const std::string& texturePath);
    static bool sIsEnabled;

private:
    std::map<std::string, std::unique_ptr<Texture>> textureMap;

    bool isTextureUsed(const std::string& texturePath) const;
    void addTexture(const std::string& texturePath);
};
}

#endif // TEXTURE_MANAGER_H
