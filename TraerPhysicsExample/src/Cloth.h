#pragma once

/*
 *  Cloth.h
 *  TraerPhysicsExample
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "TestBase.h"

//========================================================================
class Cloth : public TestBase {
    
public:
    //--------------------------------------------------------------
    Cloth() {
        ofSetWindowTitle("Cloth");
        
        ofAddListener(ofEvents.mousePressed,  this, &Cloth::mousePressed);
        ofAddListener(ofEvents.mouseDragged,  this, &Cloth::mouseDragged);
        
        physics = new ParticleSystem(.1f, .01f);
        
        float gridStepX = (ofGetWidth()/2) / (float)GRID_SIZE;
        float gridStepY = (ofGetHeight()/2) / (float)GRID_SIZE;
        
        for (int i=0; i < GRID_SIZE; i++) {
            for (int j=0; j < GRID_SIZE; j++) {
                particles[i][j] = physics->makeParticle(.2f, j * gridStepX + (ofGetWidth()/4), i * gridStepY + 20, 0);
                if (j > 0) {
                    physics->makeSpring(particles[i][j-1], particles[i][j], SPRING_STRENGTH, SPRING_DAMPING, gridStepX);
                }
            }
        }
        
        for (int j=0; j < GRID_SIZE; j++) {
            for (int i=1; i < GRID_SIZE; i++) {
                physics->makeSpring(particles[i-1][j], particles[i][j], SPRING_STRENGTH, SPRING_DAMPING, gridStepY);
            }
        }
        
        particles[0][0]->makeFixed();
        particles[0][GRID_SIZE - 1]->makeFixed();
    }
    
    //--------------------------------------------------------------
    ~Cloth() {
        ofRemoveListener(ofEvents.mousePressed,  this, &Cloth::mousePressed);
        ofRemoveListener(ofEvents.mouseDragged,  this, &Cloth::mouseDragged);
        
        delete physics;
    }
    
    //--------------------------------------------------------------
    void update() {
        physics->step();
    }
    
    //--------------------------------------------------------------
    void draw() {
        ofNoFill();
        for (int i=0; i < GRID_SIZE; i++) {
            ofBeginShape();
            ofCurveVertex(particles[i][0]->getPosition().x, particles[i][0]->getPosition().y);
            for (int j=0; j < GRID_SIZE; j++) {
                ofCurveVertex(particles[i][j]->getPosition().x, particles[i][j]->getPosition().y);
            }
            ofCurveVertex(particles[i][GRID_SIZE - 1]->getPosition().x, particles[i][GRID_SIZE - 1]->getPosition().y);
            ofEndShape();
        }
        for (int j=0; j < GRID_SIZE; j++) {
            ofBeginShape();
            ofCurveVertex(particles[0][j]->getPosition().x, particles[0][j]->getPosition().y);
            for (int i=0; i < GRID_SIZE; i++) {
                ofCurveVertex(particles[i][j]->getPosition().x, particles[i][j]->getPosition().y);
            }
            ofCurveVertex(particles[GRID_SIZE - 1][j]->getPosition().x, particles[GRID_SIZE - 1][j]->getPosition().y);
            ofEndShape();
        }
        ofFill();
    }
    
    //--------------------------------------------------------------
    void mousePressed(ofMouseEventArgs& args) {
        mouseDragged(args);
    }
    
    //--------------------------------------------------------------
    void mouseDragged(ofMouseEventArgs& args) {
        particles[0][GRID_SIZE - 1]->getPosition().set(args.x, args.y, 0);
        particles[0][GRID_SIZE - 1]->getVelocity() = 0;
    }
    
    //--------------------------------------------------------------
    static const int    GRID_SIZE       = 10;
    static const float  SPRING_STRENGTH = .2f;
    static const float  SPRING_DAMPING  = .1f;
    
    //--------------------------------------------------------------
    Particle*   particles[GRID_SIZE][GRID_SIZE];
    
};