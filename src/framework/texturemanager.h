#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <map>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>

namespace Purity
{
    class TextureManager
    {
    public:
        TextureManager();
        const sf::Texture* getTexture(const boost::filesystem::path& texturePath);

    private:
        std::map<boost::filesystem::path, std::unique_ptr<sf::Texture>> textureMap;

        bool isTextureUsed(const boost::filesystem::path& texturePath) const;
        void addTexture(const boost::filesystem::path& texturePath);
    };
}

#endif // TEXTURE_MANAGER_H