#ifndef CEGUIVIEW_H
#define CEGUIVIEW_H

#include "NXCEGUISystem.h"
#include "GLFW/glfw3.h"

class CEGUIView {
public:
    CEGUIView(GLFWwindow* Gwindow);
    void render();
private:
    void initRenderSystem();
    void initReceiver();
    
    NXCEGUISystem *renderSystem;
    GLFWwindow *window;
};

#endif
