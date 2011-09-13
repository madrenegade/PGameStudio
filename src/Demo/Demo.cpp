#include "Game/Application.h"

using namespace Game;

int main(int argc, char** argv)
{
    Application app(argc, argv);
    app.initialize();
    app.run();

    return 0;
}