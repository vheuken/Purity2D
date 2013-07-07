#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "gamemap.h"

namespace Purity
{

    class Engine
    {
    public:
        void initialize();
        void run();
        void cleanup();

    private:
        std::unique_ptr<GameMap > mMap;
    };

}

#endif // ENGINE_H