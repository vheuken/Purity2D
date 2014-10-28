#ifndef ABSTRACT_SYSTEM_H
#define ABSTRACT_SYSTEM_H

namespace Purity
{
class Scene;

class AbstractSystem
{
public:
    AbstractSystem();

    virtual void update(Scene* scene) = 0;

protected:
    Scene* mCurrentScene;
};
}

#endif // ABSTRACT_SYSTEM_H
