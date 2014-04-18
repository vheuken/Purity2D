#include "scenemanager.h"

Purity::SceneManager::SceneManager()
{
    std::string sceneDirPath(DEFAULT_SCENE_DIR + DEFAULT_STARTING_SCENE + "/");

    mScene = std::unique_ptr<Scene>(new Scene(sceneDirPath));

    mCurrentScene = mScene.get();
}

Purity::Scene* Purity::SceneManager::getCurrentScene() const
{
    return mCurrentScene;
}
