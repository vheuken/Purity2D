#include "actionmanager.h"

#include <algorithm>

bool Purity::ActionManager::getActionState(const std::string& actionName) const
{
    return mActionMap.at(actionName);
}

void Purity::ActionManager::enableAction(const std::string &actionName)
{
    mActionMap.at(actionName) = true;
}

void Purity::ActionManager::disableAction(const std::string &actionName)
{
    mActionMap.at(actionName) = false;
}

void Purity::ActionManager::disableAll()
{
    for (auto& action : mActionMap)
    {
        action.second = false;
    }
}
