#include "renderer.h"

Purity::Renderer::Renderer(sf::RenderWindow* window)
{
    mWindow = window;
}

void Purity::Renderer::update(const sf::Drawable* drawable)
{
    mWindow->clear();
    mWindow->draw(*drawable);
    mWindow->display();
}