#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    ofEnableAlphaBlending();
    
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(127,127,127);
    
    flip  = true;
    transition = mtlSceneTransitionNone;
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
	
}

//--------------------------------------------------------------
void testApp::exit() {

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch) {
    // create and display a new color scene
    mtlSceneManager* sceneManager = mtlSceneManager::getInstance();
    mtlScene* nextScene;
    if (flip) {
        nextScene = new BouncingBallsScene(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    } else {
        nextScene = new SineWaveScene();
    }
    sceneManager->addAndSwitchToScene("Scene " + ofToString(ofGetFrameNum()), nextScene, (mtlSceneTransition)transition, true);
    
    flip = !flip;
    transition = (transition + 1)%10;
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

