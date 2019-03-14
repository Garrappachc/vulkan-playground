#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include <memory>
#include <vector>

class ScenePrivate;

class Scene {
public:
    Scene();
    virtual ~Scene();

    void addObject(Object* object);

    std::vector<const Object*> objects() const;

private:
    std::unique_ptr<ScenePrivate> d;

};

#endif // SCENE_H
