#pragma once

/*
 *  BouncyBalls.h
 *  TraerPhysicsExample
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "TestBase.h"

//========================================================================
class BouncyBalls : public TestBase {
    
public:
    //--------------------------------------------------------------
    BouncyBalls() {
        ofSetWindowTitle("Bouncy Balls");
        
        ofAddListener(ofEvents.mouseMoved, this, &BouncyBalls::mouseMoved);
        
        physics = new ParticleSystem();
        mouse = physics->makeParticle();
        mouse->makeFixed();
        b = physics->makeParticle(1.f, ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0);
        c = physics->makeParticle(1.f, ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0);
        
        physics->makeAttraction(mouse, b, 10000, 10);
        physics->makeAttraction(mouse, c, 10000, 10);
        physics->makeAttraction(b, c, -10000, 5);
    }
    
    //--------------------------------------------------------------
    ~BouncyBalls() {
        ofRemoveListener(ofEvents.mouseMoved, this, &BouncyBalls::mouseMoved);
        
        delete physics;
    }
    
    //--------------------------------------------------------------
    void update() {
        physics->step();
        handleBoundaryCollisions(b);
        handleBoundaryCollisions(c);
    }
    
    //--------------------------------------------------------------
    void draw() {
        ofNoFill();
        ofCircle(mouse->getPosition().x, mouse->getPosition().y, 17.5f);
        ofFill();
        ofCircle(b->getPosition().x, b->getPosition().y, 17.5f);
        ofCircle(c->getPosition().x, c->getPosition().y, 17.5f);
    }
    
    //--------------------------------------------------------------
    // really basic collision strategy:
    // sides of the window are walls
    // if it hits a wall pull it outside the wall and flip the direction of the velocity
    // the collisions aren't perfect so we take them down a notch too
    void handleBoundaryCollisions(Particle* p) {
        if (p->getPosition().x < 0 || p->getPosition().x > ofGetWidth())
            p->getVelocity().x *= -.9f;
        
        if (p->getPosition().y < 0 || p->getPosition().y > ofGetHeight())
            p->getVelocity().y *= -.9f;
        
        p->getPosition().set(MIN(MAX(p->getPosition().x, 0), ofGetWidth()), MIN(MAX(p->getPosition().y, 0), ofGetHeight()), 0); 
    }
    
    //--------------------------------------------------------------
    void mouseMoved(ofMouseEventArgs& args) {
        mouse->getPosition().set(args.x, args.y, 0);
    }
    
    //--------------------------------------------------------------
    Particle*   mouse;
    Particle*   b;
    Particle*   c;
    
};