#include "ResourceManager.h"
#include "Tool.h"
#define MS_PER_UPDATE 16
const int DESIRED_FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / DESIRED_FPS;

int main(int argc, char *argv[])
{

    // fps
    int framesRendered;
    int framesPerSecondInt;
    double lag;
    double previous;

    int timeElapsedMs = SDL_GetTicks();

    // init resourcemanager
    ResourceManager &rm = ResourceManager::getInstance();

    Tool *tool = new Tool();

    tool->init("Spatial Partition Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while(tool->isRunning) {

        double current = SDL_GetTicks();
        double elapsed = current - previous;
    
        previous = current;
        lag += elapsed;

        if(lag >= MS_PER_UPDATE) {
            lag -= MS_PER_UPDATE;
            framesRendered++;
            tool->handleEvents();
            tool->update();
            tool->render();
        }
        else {
            SDL_Delay(MS_PER_UPDATE - lag);
        }
        
    }

    // clean
    rm.shutDown();
    tool->clean();

    return 0;
}