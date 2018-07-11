#include "CEGUIView.h"
#include "CEGUI/Window.h"
#include "GLFW/glfw3.h"

#include <pthread.h>
#include <string>

#include "NX_Base.h"
#include "NXEventSystemIF.h"
#include "CEGUI/CEGUIEventReceiver.h"
#include "NXCEGUISystem.h"
#include "CEGUI/CEGUI.h"

#include "NXEventSender.h"
#include "nxevent/WindowSystem/touch.pb.h"

#include "PreviewLauncher.h"
#include "AppLayerManager.h"

CEGUIView* CEGUIView::_CEGUIView = NULL;
CEGUIView *CEGUIView::getInstance(GLFWwindow* Gwindow) {
    if (_CEGUIView == NULL) {
        _CEGUIView = new CEGUIView(Gwindow);
    }
    return _CEGUIView;
}

CEGUIView::CEGUIView(GLFWwindow* Gwindow) {
    
    window = Gwindow;
    
	InitNXBase("apple");

    NXEventConfigure cfg;
    NXEventSystemIF::Instance()->Initialize("apple", cfg);
    NXEventSystemIF::Instance()->Start();
    
    initReceiver();
    
    initRenderSystem();
    
    NXEventSystemIF::Instance()->enterLoop();
}

void CEGUIView::initReceiver() {
	CEGUIEventReceiver *receiver = new CEGUIEventReceiver();
	receiver->initialize();
}

void CEGUIView::initRenderSystem() {
	renderSystem = new NXCEGUISystem();
    
    const int pathLen = 250;
    char subPath[pathLen];
    getcwd(subPath, pathLen);
    std::string path = subPath;
    path += "/Core";
    
    
    renderSystem->initialize(path.c_str());
    
    CEGUI::ImageManager::getSingleton().loadImageset("Sketch.imageset");
    
    CEGUI::Window* appwin = CEGUI::WindowManager::getSingleton().createWindow("Generic/Image", "appleWindow");
    appwin->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));
    appwin->setVisible(true);
    renderSystem->setRootWindow(appwin);
    
    CEGUI::Window* previewRoot = CEGUI::WindowManager::getSingleton().createWindow("Generic/Image", "preViewRoot");
    previewRoot->setProperty("Image", "Sketch/SKE_BGD");
    previewRoot->setSize(CEGUI::USize(CEGUI::UDim(0, 960), CEGUI::UDim(0, 540)));
    previewRoot->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5, -480), CEGUI::UDim(0, 40)));
    previewRoot->setID(3003);
    appwin->addChild(previewRoot);
    
    sierra::AppLayerManager* previewLayerManager = new sierra::AppLayerManager();
    previewLayerManager->initialize(previewRoot);
    
    PreviewLauncher launcher;
    launcher.initializePreview(appwin, previewLayerManager, path.c_str());
    launcher.startPreview();
}

void CEGUIView::render() {
    if (!renderSystem) {
        return;
    }
    
    PreviewLauncher launcher;
    launcher.update();
    if (renderSystem->drawFrame()) {
        glfwSwapBuffers(window);
    }
    glfwPollEvents();

}
