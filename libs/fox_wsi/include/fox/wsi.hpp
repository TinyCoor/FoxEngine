#pragma once
#include<cstdint>
#include<set>
struct Keyboard
{
    uint32_t unicodeChar;

    //only the last pressed key can be repeated 
    uint32_t repeatChar;

    std::set<uint32_t> pressKeys;
    std::set<uint32_t> releaseKeys;
    std::set<uint32_t> holdKeys;
};
// mouse
struct Mouse
{
    struct Vec2
    {
        double x;
        double y;
    };

    bool inWindow;
    bool oldInWindow;
    
    Vec2 position;
    Vec2 oldPosition;

    Vec2 scroll;

    std::set<uint32_t> pressButtons{};
    std::set<uint32_t> releaseButtons{};
    std::set<uint32_t> heldButtons{};

};

bool foxCreateWindow(int width,int height,const char* title);
bool foxWindowShouldClosed();
void foxWindowEventsProcess();
void foxDestroyWindow();
Mouse* getMouseData();
Keyboard* getKeyboardData();


