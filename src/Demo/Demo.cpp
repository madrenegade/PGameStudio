#include "Game/Application.h"

#include <google/profiler.h>
#include <glog/logging.h>

using namespace Game;


int main(int argc, char** argv)
{
    //ProfilerStart("Demo.profile");
#ifdef DEBUG
    //LOG(INFO) << "Running in debug mode...";
#endif

    Application app(argc, argv);
    app.initialize();
    app.run();

    //ProfilerStop();

    return 0;
}
