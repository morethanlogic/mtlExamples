#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(255, 255, 255);
    
    // init the capture and pixel arrays
    capture.initGrabber(CAPTURE_WIDTH, CAPTURE_HEIGHT);
    feed.allocate(CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    
    start.allocate(CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    stop.allocate( CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    curr.allocate( CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    
    startPix.allocate(CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    stopPix.allocate( CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    currPix.allocate( CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    
    bSetStart = false;
    bSetStop  = true;
}

//--------------------------------------------------------------
void testApp::update() {
    capture.grabFrame();
	if (capture.isFrameNew()) {
        // save the new frame
        feed.loadData(capture.getPixels(), CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
        
        if (bSetStart) {
            // set the start frame
            startPix.set(capture.getPixels());
            bSetStart = false;
        }
        if (bSetStop) {
            // set the stop frame
            stopPix.set(capture.getPixels());
            bSetStop = false;
        }
        
        // perform interpolation: curr = start + (stop - start) * ratio
        currPix = stopPix;
        currPix -= startPix;
        currPix *= lerpRatio;
        currPix += startPix;
        
        // load the images for display
        start.loadData(startPix.getUnsignedPixels(), CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
        stop.loadData( stopPix.getUnsignedPixels(),  CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
        curr.loadData( currPix.getUnsignedPixels(),  CAPTURE_WIDTH, CAPTURE_HEIGHT, GL_RGB);
    }
}

//--------------------------------------------------------------
void testApp::draw() {
    // draw the feeds
    ofSetColor(255, 255, 255);
    feed.draw( MARGIN*2 + CAPTURE_WIDTH,   MARGIN);
    start.draw(MARGIN,                     MARGIN*2 + CAPTURE_HEIGHT);
    curr.draw( MARGIN*2 + CAPTURE_WIDTH,   MARGIN*2 + CAPTURE_HEIGHT);
    stop.draw( MARGIN*3 + CAPTURE_WIDTH*2, MARGIN*2 + CAPTURE_HEIGHT);
    
    // draw the debug info
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 2), MARGIN, MARGIN*2);
    ofDrawBitmapString("START (1): " + ofToString(100-lerpRatio*100, 0) + "%", MARGIN, MARGIN + CAPTURE_HEIGHT);
    ofDrawBitmapString("STOP (2): " + ofToString(lerpRatio*100, 0) + "%", MARGIN*3 + CAPTURE_WIDTH*2, MARGIN + CAPTURE_HEIGHT);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    if (key == '1') {
        bSetStart = true;
    }
    else if (key == '2') {
        bSetStop = true;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
    lerpRatio = ofMap(mouseX, 0, ofGetWidth(), 0.f, 1.f);
}

