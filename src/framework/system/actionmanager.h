#ifndef PURITY_ACTION_H
#define PURITY_ACTION_H

#include <string>
#include <map>

namespace Purity
{
class ActionManager
{
public:
    bool getActionState(const std::string& actionName) const;

    void enableAction(const std::string& actionName);
    void disableAction(const std::string& actionName);

    void disableAll();

private:
    std::map<std::string, bool> mActionMap;
};
}

#endif // PURITY_ACTION_H
