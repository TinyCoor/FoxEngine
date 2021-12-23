#include<GLFW/glfw3.h>
#include<fox/wsi.hpp>
void mousePreProcess(Mouse* mouse)
{
    mouse->oldPosition = mouse->position;
    mouse->oldInWindow  =mouse-> inWindow;

    mouse-> scroll={0,0};
    mouse->pressButtons.clear();
    mouse->releaseButtons.clear();
}
void positionCallback(Mouse* mouse,double xPos,double yPos)
{
   mouse->position ={xPos,yPos};
}

void scrollCallback(Mouse* mouse,double xOffset,double yOffset)
{
    mouse->scroll = {xOffset,yOffset};
}

void cursorEnterCallback(Mouse* mouse, int entered)
{
    mouse->inWindow = entered;
}

void mouseButtonCallback(Mouse* mouse,int button,int action,int mods)
{
    if(action == GLFW_PRESS){
        mouse->pressButtons.insert(button);
        mouse->heldButtons.insert(button);
    } else if (action == GLFW_RELEASE){
        mouse->releaseButtons.insert(button);
        mouse->heldButtons.erase(button);
    }
}