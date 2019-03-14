#include "application.h"

int main() {
    Application app;

    Object* falcon = new Object("falcon");
    app.scene()->addObject(falcon);

    return app.run();
}
