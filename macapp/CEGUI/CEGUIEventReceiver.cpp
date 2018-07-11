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

void CEGUIEventReceiver::initialize(){
    
    _eventReceiver = new NXEventReceiver(NXEV_MODULE_APPMAIN);
    NXEV_FUNC_CALLBACK render_cb = NxEventCallbind(&CEGUIEventReceiver::onRenderEvent, this);
    _eventReceiver->Subscribe(NXEV_EVENT_APPMAIN_RENDER, render_cb);
    
//    NXEV_FUNC_CALLBACK multitouch_cb = NxEventCallbind(&CEGUIEventReceiver::onMultiTouchEvent, this);
//    _eventReceiver->Subscribe(NXEV_EVENT_WINDOWSYSTEM_TOUCH, multitouch_cb);
    
    _eventReceiver->StartReceive();
}

void CEGUIEventReceiver::onRenderEvent(void* msg) {
    
    CEGUIView::getInstance()->render();
}
