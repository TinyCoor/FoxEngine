#include<fox/wsi.hpp>
#include<GLFW/glfw3.h>
void keyboardPreProcess(Keyboard* keyboard)
{
    keyboard->unicodeChar = 0;
    keyboard->repeatChar = 0 ;
    keyboard->pressKeys.clear();
    keyboard->releaseKeys.clear();
}

void keyCallback(Keyboard* keyboard,int key,int scancode,int action,int mods)
{
  if (action ==GLFW_PRESS) {
        keyboard->pressKeys.insert(key);
        keyboard->holdKeys.insert(key);
    } else if (action == GLFW_REPEAT) {
       keyboard->repeatChar = key;
    } else if (action == GLFW_RELEASE) {
        keyboard->releaseKeys.insert(key);
        keyboard->holdKeys.erase(key);
    }
}

void charCallback(Keyboard* keyboard, unsigned int codepoint)
{
   keyboard->unicodeChar = codepoint;
}
