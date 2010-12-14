#pragma once

#include "ofMain.h"
#include "mtlBox2d.h"
#include "mtlBox2dCircle.h"
#include "mtlBox2dBox.h"

//========================================================================
class testApp : public ofBaseApp {
	
	public:
		void                setup();
		void                update();
		void                draw();
		
		void                keyPressed(int key);
		void                keyReleased(int key);
		void                mouseMoved(int x, int y);
		void                mouseDragged(int x, int y, int button);
		void                mousePressed(int x, int y, int button);
		void                mouseReleased();
    
        mtlBox2d            physics;
        b2World*            world;
        vector<mtlBox2dBaseShape*>   bodies;
    
        bool                debug;
        bool                info;
		
};
