/*
 *  BouncingBallsScene.cpp
 *  SceneManagerExample
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "BouncingBallsScene.h"

//--------------------------------------------------------------
float Ball::size = 0;

//--------------------------------------------------------------
BouncingBallsScene::BouncingBallsScene(int _r, int _g, int _b) : mtlColorScene(_r, _g, _b) {
    enableTouchEvents();
    
    entering = false;
    exiting  = false;
    
    // start with some randomly placed balls
    for (int i=0; i < 10; i++) {
        addBall(ofRandom(25, ofGetWidth() - 25), ofRandom(25, ofGetHeight() - 25));\
    }
}

//--------------------------------------------------------------
BouncingBallsScene::~BouncingBallsScene() {
    for (int i=0; i < balls.size(); i++) {
        delete balls[i];
    }
    balls.clear();
}

//--------------------------------------------------------------
void BouncingBallsScene::enter() {
    entering = true;
}

//--------------------------------------------------------------
void BouncingBallsScene::exit() {
    exiting = true;
}

//--------------------------------------------------------------
void BouncingBallsScene::update() {
    if (entering) {
        Ball::size++;
        if (Ball::size >= 25) {
            entering = false;
            ofNotifyEvent(enterCompleted, status, this);
        }
    }
    else if (exiting) {
        Ball::size--;
        if (Ball::size <= 0) {
            exiting = false;
            ofNotifyEvent(exitCompleted, status, this);
        }
    }
}

//--------------------------------------------------------------
void BouncingBallsScene::draw() {
    mtlColorScene::draw();
    
    for (int i=0; i < balls.size(); i++) {
        balls[i]->update();
        balls[i]->draw(alpha / 255.f);
    }
}

//--------------------------------------------------------------
void BouncingBallsScene::addBall(int _x, int _y) {
    Ball* b = new Ball(_x, _y);
    balls.push_back(b);
}

//--------------------------------------------------------------
void BouncingBallsScene::touchDown(ofTouchEventArgs& _touch) {
    addBall(_touch.x, _touch.y);
}
