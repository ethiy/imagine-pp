#include "Imagine/Graphics/Interface.h"
#include "GraphicsApplication.h"

namespace Imagine {

GraphicsThread::GraphicsThread(int& argc, char** argv)
: app(new GraphicsApplication(argc, argv)) {
    app->userThread.registerUserMain(__main, argc, argv);
    app->userThread.start();
}

GraphicsThread::~GraphicsThread() {
    delete app;
}

int GraphicsThread::exec() {
    return app->exec();
}

}
