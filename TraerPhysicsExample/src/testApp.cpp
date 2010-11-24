#include "testApp.h"

#include "BouncyBalls.h"
#include "Cloth.h"
#include "RandomArboretum.h"
#include "SimplePendulum.h"
#include "Tendrils.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(255, 255, 255);
    ofSetColor(0, 0, 0);
    ofSetFrameRate(60);
    
    curr = 0;
    physicsApp = new BouncyBalls();
}

//--------------------------------------------------------------
void testApp::update() {
    physicsApp->update();
}

//--------------------------------------------------------------
void testApp::draw() {
    physicsApp->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT || key == OF_KEY_RIGHT) {
        // delete the current app
        delete physicsApp;
        
        if (key == OF_KEY_LEFT) {
            // load the previous app
            curr = (curr - 1 + 5)%5;
        } else {
            // load the next app
            curr = (curr + 1)%5;
        }
        
        switch (curr) {
            case 0:
                physicsApp = new BouncyBalls();
                break;
                
            case 1:
                physicsApp = new Cloth();
                break;
                
            case 2:
                physicsApp = new RandomArboretum();
                break;
                
            case 3:
                physicsApp = new SimplePendulum();
                break;
                
            case 4:
                physicsApp = new Tendrils();
                break;
                
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

