#include "actionmanager.h"

#include <algorithm>

bool Purity::ActionManager::getActionState(const std::string& actionName) const
{
    if (mActionMap.find(actionName) == mActionMap.end())
    {
        return false;
    }

    return mActionMap.at(actionName);
}

void Purity::ActionManager::enableAction(const std::string &actionName)
{
    if (mActionMap.find(actionName) == mActionMap.end())
    {
        mActionMap.insert(std::pair<std::string, bool>(actionName, true));
    }

    mActionMap.at(actionName) = true;
}

void Purity::ActionManager::disableAction(const std::string &actionName)
{
    if (mActionMap.find(actionName) == mActionMap.end())
    {
        mActionMap.insert(std::pair<std::string, bool>(actionName, false));
    }

    mActionMap.at(actionName) = false;
}

void Purity::ActionManager::disableAll()
{
    for (auto& action : mActionMap)
    {
        action.second = false;
    }
}
