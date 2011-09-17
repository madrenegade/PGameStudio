#include "Game/Application.h"
#include <google/profiler.h>

using namespace Game;

int main(int argc, char** argv)
{
    //ProfilerStart("Demo.profile");
    
    Application app(argc, argv);
    app.initialize();
    app.run();
    
    //ProfilerStop();

    return 0;
}