#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"

namespace Purity
{
    class SceneManager
    {
    public:
        const Scene* getCurrentScene() const;

    private:
        const Scene* mCurrentScene;
    };
}

#endif // SCENE_MANAGER_H