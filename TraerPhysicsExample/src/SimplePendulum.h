#pragma once

/*
 *  SimplePendulum.h
 *  TraerPhysicsExample
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "TestBase.h"

//========================================================================
class SimplePendulum : public TestBase {
    
public:
    //--------------------------------------------------------------
    SimplePendulum() {
        ofSetWindowTitle("Simple Pendulum");
        
        ofAddListener(ofEvents.mousePressed,  this, &SimplePendulum::mousePressed);
        ofAddListener(ofEvents.mouseDragged,  this, &SimplePendulum::mouseDragged);
        ofAddListener(ofEvents.mouseReleased, this, &SimplePendulum::mouseReleased);
        
        physics = new ParticleSystem(1, .05f);
        p = physics->makeParticle(1.f, ofGetWidth()/2, ofGetHeight()/2, 0);
        anchor = physics->makeParticle(1.f, ofGetWidth()/2, ofGetHeight()/2, 0);
        anchor->makeFixed();
        s = physics->makeSpring(p, anchor, .5f, .1f, 75);
    }
    
    //--------------------------------------------------------------
    ~SimplePendulum() {
        ofRemoveListener(ofEvents.mousePressed,  this, &SimplePendulum::mousePressed);
        ofRemoveListener(ofEvents.mouseDragged,  this, &SimplePendulum::mouseDragged);
        ofRemoveListener(ofEvents.mouseReleased, this, &SimplePendulum::mouseReleased);
        
        delete physics;
    }
    
    //--------------------------------------------------------------
    void update() {
        physics->step();
    }
    
    //--------------------------------------------------------------
    void draw() {
        ofLine(p->getPosition().x, p->getPosition().y, anchor->getPosition().x, anchor->getPosition().y);
        ofCircle(p->getPosition().x, p->getPosition().y, 10);
        ofCircle(anchor->getPosition().x, anchor->getPosition().y, 2.5f);
    }
    
    //--------------------------------------------------------------
    void mousePressed(ofMouseEventArgs& args) {
        p->makeFixed();
        p->getPosition().set(args.x, args.y, 0);
    }
    
    //--------------------------------------------------------------
    void mouseDragged(ofMouseEventArgs& args) {
        p->getPosition().set(args.x, args.y, 0);
    }
    
    //--------------------------------------------------------------
    void mouseReleased(ofMouseEventArgs& args) {
        p->makeFree();
    }
    
    //--------------------------------------------------------------
    Particle*   p;
    Particle*   anchor;
    Spring*     s;
    
};