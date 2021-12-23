#pragma once
#include<fox/wsi.hpp>

void keyboardPreProcess(Keyboard* Keyboard);
void keyCallback(Keyboard* Keyboard,int key,int scancode,int action,int mods);

void charCallback(Keyboard* Keyboard, unsigned int codepoint);