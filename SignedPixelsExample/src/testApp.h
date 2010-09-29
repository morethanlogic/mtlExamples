#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "mtlSignedPixels.h"

class testApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		
        static const int    CAPTURE_WIDTH   = 320;
        static const int    CAPTURE_HEIGHT  = 240;
    
        static const int    MARGIN          =  10;
    
    private:
        ofVideoGrabber  capture;
        ofTexture       feed;
    
        ofTexture       start;
        ofTexture       stop;
        ofTexture       curr;
    
        mtlSignedPixels startPix;
        mtlSignedPixels stopPix;
        mtlSignedPixels currPix;
        
        bool            bSetStart;
        bool            bSetStop;
        
        float           lerpRatio;

};

#endif
