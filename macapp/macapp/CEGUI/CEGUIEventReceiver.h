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
#include <NXEventReceiver.h>
#include "../CEGUIView.h"

class CEGUIEventReceiver {
public:
    void initializeWithView(CEGUIView* view);
    void onRenderEvent(void* msg);
    void onMultiTouchEvent(void* msg);
    
private:
    CEGUIView* _ceguiView;
    NXEventReceiver* _eventReceiver;
    
};

#endif /* CEGUIEventReceiver_hpp */
