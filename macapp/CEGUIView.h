#ifndef CEGUIVIEW_H
#define CEGUIVIEW_H

#include "NXCEGUISystem.h"
#include "GLFW/glfw3.h"

class CEGUIView {
public:
    static CEGUIView *getInstance(GLFWwindow* Gwindow = NULL);
    void render();
    GLFWwindow* getWindow(){
        return window;
    }
    NXCEGUISystem* getRenderSystem() {
        return renderSystem;
    }
    
    
private:
    void init(GLFWwindow* Gwindow);
    void initRenderSystem();
    void initReceiver();
    
    GLFWwindow *window;
    NXCEGUISystem *renderSystem;
    static CEGUIView *_CEGUIView;
};

#endif
