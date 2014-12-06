#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <memory>

#include "../framework/scene.h"

class b2World;

namespace Purity
{
const std::string DEFAULT_SCENE_DIR = "scenes/";
const std::string DEFAULT_STARTING_SCENE = "init";

class SceneManager
{
public:
    SceneManager(b2World* world);
    Scene* getCurrentScene() const;

private:
    b2World* mWorld;
    std::unique_ptr<Scene> mScene;
    Scene* mCurrentScene;
};
}

#endif // SCENE_MANAGER_H
