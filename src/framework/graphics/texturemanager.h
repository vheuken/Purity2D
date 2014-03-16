#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <map>
#include <boost/filesystem.hpp>

#include "texture.h"

namespace Purity
{
    class TextureManager
    {
    public:
        const Texture* getTexture(const boost::filesystem::path& texturePath);
        static bool sIsEnabled;

    private:
        std::map<boost::filesystem::path, std::unique_ptr<Texture>> textureMap;

        bool isTextureUsed(const boost::filesystem::path& texturePath) const;
        void addTexture(const boost::filesystem::path& texturePath);
    };
}

#endif // TEXTURE_MANAGER_H
