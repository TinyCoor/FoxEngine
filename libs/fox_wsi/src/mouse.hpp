#pragma once
#include<fox/wsi.hpp>

void mousePreProcess(Mouse* mouse);
void positionCallback(Mouse* mouse,double xPos,double yPos);

void scrollCallback(Mouse* mouse,double xOffset,double yOffset);

void cursorEnterCallback(Mouse* mouse, int entered);

void mouseButtonCallback(Mouse* mouse,int button,int action,int mods);