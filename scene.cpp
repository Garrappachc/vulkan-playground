#include "scene.h"

class ScenePrivate {
public:
    std::vector<std::unique_ptr<Object>> objects;

};

Scene::Scene() : d(new ScenePrivate)
{

}

Scene::~Scene()
{

}

void Scene::addObject(Object* object)
{
    d->objects.emplace_back(object);
}

std::vector<const Object*> Scene::objects() const
{
    std::vector<const Object*> ret(d->objects.size());
    for (size_t i = 0; i < d->objects.size(); ++i)
        ret[i] = d->objects.at(i).get();

    return ret;
}
