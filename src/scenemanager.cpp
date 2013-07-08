#include "scenemanager.h"

Purity::SceneManager::SceneManager()
{
    boost::filesystem::path sceneDirPath(DEFAULT_SCENE_DIR + DEFAULT_STARTING_SCENE + "/");

    mScene = std::unique_ptr<Scene>(new Scene(sceneDirPath));
    mCurrentScene = mScene.get();
}

const Purity::Scene* Purity::SceneManager::getCurrentScene() const
{
    return mCurrentScene;
}