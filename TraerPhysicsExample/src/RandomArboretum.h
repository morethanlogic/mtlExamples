#pragma once

/*
 *  RandomArboretum.h
 *  TraerPhysicsExample
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "TestBase.h"
#include <limits>

//========================================================================
class RandomArboretum : public TestBase {
    
public:
    //--------------------------------------------------------------
    RandomArboretum() {
        ofSetWindowTitle("Random Arboretum");
        
        ofAddListener(ofEvents.mousePressed,  this, &RandomArboretum::mousePressed);
        ofAddListener(ofEvents.mouseDragged,  this, &RandomArboretum::mouseDragged);
        ofAddListener(ofEvents.keyPressed,    this, &RandomArboretum::keyPressed);
        
        physics = new ParticleSystem( 0, 0.1 );
        
        // Runge-Kutta, the default integrator is stable and snappy,
        // but slows down quickly as you add particles.
        // 500 particles = 7 fps on my machine
        
        // Try this to see how Euler is faster, but borderline unstable.
        // 500 particles = 24 fps on my machine
        physics->setIntegrator(kModifiedEuler); 
        
        // Now try this to see make it more damped, but stable.
        physics->setDrag(.2f);
        
        scale     = 1;
        centroidX = 0;
        centroidY = 0;
        
        initialize();
    }
    
    //--------------------------------------------------------------
    ~RandomArboretum() {
        ofRemoveListener(ofEvents.mousePressed,  this, &RandomArboretum::mousePressed);
        ofRemoveListener(ofEvents.mouseDragged,  this, &RandomArboretum::mouseDragged);
        ofRemoveListener(ofEvents.keyPressed,    this, &RandomArboretum::keyPressed);
        
        delete physics;
    }
    
    //--------------------------------------------------------------
    void update() {
        physics->step();
    }

    //--------------------------------------------------------------
    void draw() {
        if (physics->getNumParticles() > 1) {
            updateCentroid();
        }

        ofSetColor(0, 0, 0);
        ofDrawBitmapString(ofToString(physics->getNumParticles()) + " PARTICLES\n" + ofToString(ofGetFrameRate(), 2) + " FPS", 10, 20);
        
        glPushMatrix();
        {
            glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
            glScalef(scale, scale, 1);
            glTranslatef(-centroidX, -centroidY, 0);
            
            // draw the network
            // draw the vertices
            ofSetColor(160, 160, 160);
            for (int i=0; i < physics->getNumParticles(); i++) {
                Particle* p = physics->getParticleAt(i);
                ofCircle(p->getPosition().x, p->getPosition().y, NODE_SIZE);
            }
            
            // draw edges
            ofNoFill();
            ofSetColor(0, 0, 0);
            ofSetLineWidth(2);
            glBegin(GL_LINES);
            for (int i=0; i < physics->getNumSprings(); i++) {
                Spring* s = physics->getSpringAt(i);
                Particle* a = s->getA();
                Particle* b = s->getB();
                glVertex2f(a->getPosition().x, a->getPosition().y);
                glVertex2f(b->getPosition().x, b->getPosition().y);
            }
            glEnd();
            ofSetLineWidth(1);
            ofFill();
        }
        glPopMatrix();
    }
    
    //--------------------------------------------------------------
    void mousePressed(ofMouseEventArgs& args) {
        mouseDragged(args);
    }
    
    //--------------------------------------------------------------
    void mouseDragged(ofMouseEventArgs& args) {
        addNode();
    }
    
    //--------------------------------------------------------------
    void keyPressed(ofKeyEventArgs& args) {
        if (args.key == ' ') {
            initialize();
        }
    }
    
    //--------------------------------------------------------------
    void updateCentroid() {
        float xMax = numeric_limits<float>::min();
        float xMin = numeric_limits<float>::max(); 
        float yMin = numeric_limits<float>::max();
        float yMax = numeric_limits<float>::min();
        
        for (int i=0; i < physics->getNumParticles(); i++) {
            Particle* p = physics->getParticleAt(i);
            xMax = MAX(xMax, p->getPosition().x);
            xMin = MIN(xMin, p->getPosition().x);
            yMin = MIN(yMin, p->getPosition().y);
            yMax = MAX(yMax, p->getPosition().y);
        }
        float deltaX = xMax - xMin;
        float deltaY = yMax - yMin;
        
        centroidX = xMin + .5f * deltaX;
        centroidY = yMin + .5f * deltaY;
        
        if (deltaY > deltaX)
            scale = ofGetHeight() / (deltaY + 50);
        else
            scale = ofGetWidth()  / (deltaX + 50);
    }
    
    //--------------------------------------------------------------
    void addSpacersToNode(Particle* _p, Particle* _r) {
        for (int i=0; i < physics->getNumParticles(); i++) {
            Particle* q = physics->getParticleAt(i);
            if (_p != q && _p != _r)
                physics->makeAttraction(_p, q, -1000.f, 20);
        }
    }
    
    //--------------------------------------------------------------
    void makeEdgeBetween(Particle* _a, Particle* _b) {
        physics->makeSpring(_a, _b, EDGE_STRENGTH, EDGE_STRENGTH, EDGE_LENGTH);
    }
    
    //--------------------------------------------------------------
    void initialize() {
        physics->clear();
        physics->makeParticle();
    }
    
    //--------------------------------------------------------------
    void addNode() { 
        Particle* p = physics->makeParticle();
        Particle* q;
        do {
            q = physics->getParticleAt((int)ofRandom(0, physics->getNumParticles() - 1));
        } while (q == p);
        addSpacersToNode(p, q);
        makeEdgeBetween(p, q);
        p->getPosition().set(q->getPosition().x + ofRandom(-1, 1), q->getPosition().y + ofRandom(-1, 1), 0);
    }
    
    //--------------------------------------------------------------
    static const int    NODE_SIZE       = 5;
    static const float  EDGE_LENGTH     = 20.f;
    static const float  EDGE_STRENGTH   = .2f;
    //static const float  SPACER_STRENGTH = 1000.f;
    
    //--------------------------------------------------------------
    float scale;
    float centroidX;
    float centroidY;

};