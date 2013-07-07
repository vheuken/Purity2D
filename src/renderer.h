#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include<iostream>
namespace Purity
{
    class Renderer
    {
    public:
        Renderer(sf::RenderWindow* window);

        void update(const sf::Drawable& drawable);

    private:
        sf::RenderWindow* mWindow;
    };
}

#endif // RENDERER_H