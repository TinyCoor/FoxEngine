#include"fox/wsi.hpp"
#include<GLFW/glfw3.h>
#include<mutex>
#include"mouse.hpp"
#include"keyboard.hpp"

namespace {
    GLFWwindow* pWindow =nullptr;
    bool resized = false;
    Mouse mouse;
    Keyboard keyboard;
    std::once_flag glfwInitFlag;
    void windowResizedCallback(GLFWwindow* window,int width,int height)
    {
        resized = true;
    }

    void positionCallback(GLFWwindow* window,double xPos,double yPos){
        positionCallback(&mouse,xPos,yPos);
    }

    void scrollCallback(GLFWwindow* window,double xOffset,double yOffset){
        scrollCallback(&mouse,xOffset,yOffset);
    }

    void cursorEnterCallback(GLFWwindow* window, int entered){
        cursorEnterCallback(&mouse,entered);
    }

    void mouseButtonCallback(GLFWwindow* window,int button,int action,int mods){
        mouseButtonCallback(&mouse,button,action,mods);
    }

    void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods)
    {
        keyCallback(&keyboard,key,scancode,action,mods);
    }

    void charCallback(GLFWwindow* window, unsigned int codepoint)
    {
        charCallback(&keyboard,codepoint);
    }
} // namespace


bool foxCreateWindow(int width,int height,const char* title){
    std::call_once(glfwInitFlag,[]{glfwInit();});
    pWindow = glfwCreateWindow(width,height,title,nullptr,nullptr);
    if(pWindow ==nullptr){
        return false;
    }

    //Mouse callback
    glfwSetCursorPosCallback(pWindow,positionCallback);
    glfwSetScrollCallback(pWindow,scrollCallback);
    glfwSetMouseButtonCallback(pWindow,mouseButtonCallback);
    glfwSetCursorEnterCallback(pWindow,cursorEnterCallback);
    //Keyboard Callbacks
    glfwSetKeyCallback(pWindow,keyCallback);
    glfwSetCharCallback(pWindow,charCallback);

    //Window Callbacks
    glfwSetWindowSizeCallback(pWindow,windowResizedCallback);
    return true;
}

bool foxWindowShouldClosed()
{
    return glfwWindowShouldClose(pWindow);
}

void foxWindowEventsProcess()
{
    mousePreProcess(&mouse);
    keyboardPreProcess(&keyboard);
    glfwPollEvents();
}

void foxDestroyWindow()
{
    glfwDestroyWindow(pWindow);
    pWindow= nullptr;
}

Mouse* getMouseData(){
    return &mouse;
}

Keyboard* getKeyboardData()
{
    return &keyboard;
}