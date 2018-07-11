#ifndef CEGUIVIEW_H
#define CEGUIVIEW_H

#include "NXCEGUISystem.h"
#include "GLFW/glfw3.h"

class CEGUIView {
public:
    static CEGUIView *getInstance(GLFWwindow* Gwindow = NULL);
    void render();
    
    NXCEGUISystem *renderSystem;
    
    
private:
    CEGUIView(GLFWwindow* Gwindow);
    void initRenderSystem();
    void initReceiver();
    
    GLFWwindow *window;
    static CEGUIView *_CEGUIView;
};

#endif
