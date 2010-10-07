/*
 *  SineWaveScene.cpp
 *  SceneManagerExample
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "SineWaveScene.h"

//--------------------------------------------------------------
SineWaveScene::SineWaveScene() : mtlColorScene(0) {
    offset = 0;
    step   = .1f;
}

//--------------------------------------------------------------
void SineWaveScene::update() {
    offset += step;
}

//--------------------------------------------------------------
void SineWaveScene::draw() {
    mtlColorScene::draw();
    
    ofSetColor(255, 255, 255, alpha);
    for (int i=0; i < height; i+=5) {
        ofLine(width/2, i, width/2 + sin(offset+i*step) * 100, i);
    }
}