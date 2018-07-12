//
//  CEGUIEventReceiver.cpp
//  SierraApp
//
//  Created by AirMachen on 2018/6/8.
//  Copyright © 2018年 Suntec. All rights reserved.
//

#include "CEGUIEventReceiver.h"
#include "../CEGUIView.h"
#include "NXEventReceiver.h"
#include "nxevent/WindowSystem/touch.pb.h"
#include "InputDispatcherDef.h"
#include "NXEventSystemIF.h"
#include "NXCEGUISystem.h"

void CEGUIEventReceiver::initialize(){
    
    _eventReceiver = new NXEventReceiver(NXEV_MODULE_APPMAIN);
    NXEV_FUNC_CALLBACK render_cb = NxEventCallbind(&CEGUIEventReceiver::onRenderEvent, this);
    _eventReceiver->Subscribe(NXEV_EVENT_APPMAIN_RENDER, render_cb);
    
    glfwSetWindowCloseCallback(CEGUIView::getInstance()->getWindow(), CEGUIEventReceiver::glfwWindowCloseCallback);
    //glfwSetWindowSizeCallback(CEGUIView::instance(NULL)->getWindow(), CEGUIEventReceiver::glfwWindowResizeCallback);
    
    glfwSetMouseButtonCallback(CEGUIView::getInstance()->getWindow(), glfwMouseButtonCallback);
    glfwSetCursorPosCallback(CEGUIView::getInstance()->getWindow(), glfwCursorPosCallback);
    
    _eventReceiver->StartReceive();
}

void CEGUIEventReceiver::onRenderEvent(void* msg) {
    CEGUIView::getInstance()->render();
}

void CEGUIEventReceiver::glfwWindowCloseCallback(GLFWwindow* window)
{
    NXEventSystemIF::Instance()->Stop();
}

void CEGUIEventReceiver::glfwWindowResizeCallback(GLFWwindow* window)
{

}

void CEGUIEventReceiver::glfwMouseButtonCallback
(GLFWwindow* window, int button, int action, int /*mods*/)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT)
        return;
    
    double x,y;
    glfwGetCursorPos(window, &x, &y);
    if (action == GLFW_PRESS)
        CEGUIView::getInstance()->getRenderSystem()->injectTouchDown(x, y);
    else if (action == GLFW_RELEASE)
        CEGUIView::getInstance()->getRenderSystem()->injectTouchUp(x, y);
}

void CEGUIEventReceiver::glfwCursorPosCallback
(GLFWwindow* window, double x, double y)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS )
        return;
    
    CEGUIView::getInstance()->getRenderSystem()->injectTouchMove(x, y);
}
