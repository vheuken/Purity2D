#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <memory>
#include "scene.h"

namespace Purity
{
    const std::string DEFAULT_SCENE_DIR = "scenes/";
    const std::string DEFAULT_STARTING_SCENE = "init";

    class SceneManager
    {
    public:
        SceneManager();
        const Scene* getCurrentScene() const;

    private:
        std::unique_ptr<Scene> mScene;
        Scene* mCurrentScene;
    };
}

#endif // SCENE_MANAGER_H