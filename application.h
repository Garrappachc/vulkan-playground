#ifndef APPLICATION_H
#define APPLICATION_H

#include "scene.h"
#include <memory>

class ApplicationPrivate;

class Application {
public:
    Application();
    virtual ~Application();

    int run();

    const Scene* scene() const;
    Scene* scene();

private:
    std::unique_ptr<ApplicationPrivate> d;

};

#endif // APPLICATION_H
