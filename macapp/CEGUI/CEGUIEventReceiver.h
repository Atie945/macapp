//
//  CEGUIEventReceiver.hpp
//  SierraApp
//
//  Created by AirMachen on 2018/6/8.
//  Copyright © 2018年 Suntec. All rights reserved.
//

#ifndef CEGUIEventReceiver_hpp
#define CEGUIEventReceiver_hpp

#include <stdio.h>
#include "GLFW/glfw3.h"
#include <NXEventReceiver.h>
#include "CEGUI/CEGUI.h"

class CEGUIEventReceiver {
public:
    void initialize();
    void onRenderEvent(void* msg);
    void onMultiTouchEvent(void* msg);
    static void glfwWindowCloseCallback(GLFWwindow* window);
    static void glfwWindowResizeCallback(GLFWwindow* window);
    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    
private:
    NXEventReceiver* _eventReceiver;
    
    
    
};

#endif /* CEGUIEventReceiver_hpp */
