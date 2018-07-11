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

void CEGUIEventReceiver::initializeWithView(CEGUIView* view){
    
    _ceguiView = view;
    _eventReceiver = new NXEventReceiver(NXEV_MODULE_APPMAIN);
    NXEV_FUNC_CALLBACK render_cb = NxEventCallbind(&CEGUIEventReceiver::onRenderEvent, this);
    _eventReceiver->Subscribe(NXEV_EVENT_APPMAIN_RENDER, render_cb);
    
    NXEV_FUNC_CALLBACK multitouch_cb = NxEventCallbind(&CEGUIEventReceiver::onMultiTouchEvent, this);
    _eventReceiver->Subscribe(NXEV_EVENT_WINDOWSYSTEM_TOUCH, multitouch_cb);
    
    _eventReceiver->StartReceive();
}

void CEGUIEventReceiver::onRenderEvent(void* msg) {
    
    _ceguiView->render();
}


void CEGUIEventReceiver::onMultiTouchEvent(void* message)
{
    // LOG_APPINPUT_TRACE("--------- onMultiTouchEvent:%p ------------ ", message);
    
    nxevent::WindowSystem::Touch* data = reinterpret_cast<nxevent::WindowSystem::Touch*>(message);
    if (!data) {
        return;
    }
    
    IDTouchPointsAction action = IDTouchPointsAction_Cancel;
    switch (data->touch_points_action()) {
        case nxevent::WindowSystem::Touch::TouchPointsAction_Press:
            action = IDTouchPointsAction_Press;
            break;
        case nxevent::WindowSystem::Touch::TouchPointsAction_Move:
            action = IDTouchPointsAction_Move;
            break;
        case nxevent::WindowSystem::Touch::TouchPointsAction_Release:
            action = IDTouchPointsAction_Release;
            break;
        case nxevent::WindowSystem::Touch::TouchPointsAction_Cancel:
            action = IDTouchPointsAction_Cancel;
            break;
        case nxevent::WindowSystem::Touch::TouchPointsAction_HoverMove:
            // action = InputTouchDispatcher::IDTouchPointsAction_HoverMove;
            // printf("InputReceiver::receiveTouch hover ignore\n");
            return;
        default:
            break;
    }
    
    IDTouchDevice device = IDTouchDevice_Front;
    switch (data->touch_device()) {
        case nxevent::WindowSystem::Touch::TouchDevice_Front:
            device = IDTouchDevice_Front;
            break;
        case nxevent::WindowSystem::Touch::TouchDevice_Back:
            device = IDTouchDevice_Back;
            break;
        case nxevent::WindowSystem::Touch::TouchDevice_Pad:
            // touchData->deviceId = IDTouchDevice_Pad;
            // printf("InputReceiver::receiveTouch pad error\n");
            return;
        default:
            break;
    }
    
    IDTouchPoints* touchData = new IDTouchPoints;
    if (!touchData) {
        return;
    }
    
    touchData->action = action;
    touchData->deviceId = device;
    touchData->wndId = data->wnd_id();
    // touchData->downTime = data->down_time();
    touchData->eventTime = data->event_time();
    touchData->pointerCount = data->pointer_count();
    
    for (int i = 0; i < touchData->pointerCount; i++) {
        nxevent::WindowSystem::Touch_PointerCoords pointCoords = data->pointer_coords(i);
        switch (pointCoords.touch_point_action()) {
            case nxevent::WindowSystem::Touch::TouchPointAction_Press:
                touchData->pointerCoords[i].action = IDTouchPointsAction_Press;
                break;
            case nxevent::WindowSystem::Touch::TouchPointAction_Move:
                touchData->pointerCoords[i].action = IDTouchPointsAction_Move;
                break;
            case nxevent::WindowSystem::Touch::TouchPointAction_Release:
                touchData->pointerCoords[i].action = IDTouchPointsAction_Release;
                break;
            case nxevent::WindowSystem::Touch::TouchPointAction_Stationary:
                touchData->pointerCoords[i].action = IDTouchPointsAction_Stationary;
                break;
            default:
                break;
        }
        
        touchData->pointerCoords[i].id = pointCoords.id();
        touchData->pointerCoords[i].x = pointCoords.x();
        touchData->pointerCoords[i].y = pointCoords.y();
        touchData->pointerCoords[i].pressure = pointCoords.pressure();
        touchData->pointerCoords[i].size = pointCoords.size();
    }
    
    int x0 = touchData->pointerCoords[0].x;
    int y0 = touchData->pointerCoords[0].y;
    switch(touchData->action) {
        case IDTouchPointsAction_Press:
        {
//            [_ceguiView inijectTouch:TouchDown posX:x0 posY:y0];
        }
            break;
        case IDTouchPointsAction_Move:
        {
//            [_ceguiView inijectTouch:TouchMoved posX:x0 posY:y0];
        }
            break;
        case IDTouchPointsAction_Release:
        default:
        {
//            [_ceguiView inijectTouch:TouchUp posX:x0 posY:y0];
        }
            break;
    }
    
    delete touchData;
}

