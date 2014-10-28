#ifndef SUB_SYSTEMABLE_H
#define SUB_SYSTEMABLE_H

namespace Purity
{
class Scene;

class SubSystemable
{
public:
    SubSystemable();

    virtual void update(Scene* scene) = 0;

protected:
    Scene* mCurrentScene;
};
}

#endif // SUB_SYSTEMABLE_H
