#include "application.h"
#include "config.h"

int main() {
    Application app;

    Object* falcon = new Object("falcon");
    falcon->load(INTRO_SOURCE_DIR "/models/falcon/millenium-falcon.obj");
    app.scene()->addObject(falcon);

    return app.run();
}
