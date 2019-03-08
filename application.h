#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

class ApplicationPrivate;

class Application {
public:
    Application();
    virtual ~Application();

    int run();

private:
    std::unique_ptr<ApplicationPrivate> d;

};

#endif // APPLICATION_H
