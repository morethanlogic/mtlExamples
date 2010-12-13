#pragma once

/*
 *  Tendrils.h
 *  TraerPhysicsExample
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "TestBase.h"

//========================================================================
class T3ndril {

public:
	//--------------------------------------------------------------
    T3ndril(ParticleSystem* _system, float _x, float _y, float _z, Particle* _followPoint) {
		system = _system;
		Particle* firstParticle = system->makeParticle(1.f, _x, _y, _z);
		particles.push_back(firstParticle);
		system->makeSpring(_followPoint, firstParticle, .1f, .1f, 5);
	}
    
	//--------------------------------------------------------------
	void addPoint(float _x, float _y, float _z) {
		Particle* p = system->makeParticle(1.f, _x, _y, _z);
        Spring* s = system->makeSpring(particles.back(), p, 1.f, 1.f, particles.back()->distanceTo(p));
		springs.push_back(s);
		particles.push_back(p);
	}
    
    //--------------------------------------------------------------
	ParticleSystem*     system;
    vector<Particle*>   particles;
	vector<Spring*>     springs;
    
};

//========================================================================
class Tendrils : public TestBase {
    
public:
    //--------------------------------------------------------------
    Tendrils() {
        ofSetWindowTitle("Tendrils");
        
        ofAddListener(ofEvents.mouseMoved,    this, &Tendrils::mouseMoved);
        ofAddListener(ofEvents.mousePressed,  this, &Tendrils::mousePressed);
        ofAddListener(ofEvents.mouseDragged,  this, &Tendrils::mouseDragged);
        ofAddListener(ofEvents.mouseReleased, this, &Tendrils::mouseReleased);
        ofAddListener(ofEvents.keyPressed,    this, &Tendrils::keyPressed);
        
        physics = new ParticleSystem(-.1f, .05f);
        
        mouse = physics->makeParticle();
        mouse->makeFixed();
        
        drawing = false;
        greyer  = 255;
    }
    
    //--------------------------------------------------------------
    ~Tendrils() {
        ofRemoveListener(ofEvents.mouseMoved,    this, &Tendrils::mouseMoved);
        ofRemoveListener(ofEvents.mousePressed,  this, &Tendrils::mousePressed);
        ofRemoveListener(ofEvents.mouseDragged,  this, &Tendrils::mouseDragged);
        ofRemoveListener(ofEvents.mouseReleased, this, &Tendrils::mouseReleased);
        ofRemoveListener(ofEvents.keyPressed,    this, &Tendrils::keyPressed);
        
        delete physics;
    }
    
    //--------------------------------------------------------------
    void update() {
        if (!drawing) {
            physics->step();
        }
    }
    
    //--------------------------------------------------------------
    void draw() {
        if (!drawing) {
            if (greyer < 255) greyer *= 1.11111f;
            if (greyer > 255) greyer = 255;
        } else {
            if (greyer >= 64) greyer *= .9f;
        }
        
        ofNoFill();
        ofSetColor(255 - greyer, 255 - greyer, 255 - greyer);
        for (int i=0; i < tendrils.size(); i++) {
            drawElastic(tendrils[i]);
        }
        
        ofSetColor(0, 0, 0);
        if (!tendrils.empty()) {
            drawElastic(tendrils.back());
        }
        ofFill();
    }
    
    //--------------------------------------------------------------
    void drawElastic(T3ndril* _tendril) {
        float lastStretch = 1.f;
        for (int i=0; i < _tendril->particles.size() - 1; i++) {
            ofxVec3f firstPoint   = _tendril->particles[i]->getPosition();
            ofxVec3f firstAnchor  = (i < 1)? firstPoint : _tendril->particles[i-1]->getPosition();
            ofxVec3f secondPoint  = (i+1 < _tendril->particles.size())? _tendril->particles[i+1]->getPosition() : firstPoint;
            ofxVec3f secondAnchor = (i+2 < _tendril->particles.size())? _tendril->particles[i+1]->getPosition() : secondPoint;
			
            //float springStretch = 2.5f/((Spring)t.springs.get( i )).stretch();
            Spring* s = _tendril->springs[i];
            float springStretch = 2.5 * s->getRestLength() / s->getCurrentLength();
            
            ofSetLineWidth((springStretch + lastStretch) / 2.f);
            lastStretch = springStretch;
			
            ofCurve(firstAnchor.x,  firstAnchor.y,
                    firstPoint.x,   firstPoint.y,
                    secondPoint.x,  secondPoint.y,
                    secondAnchor.x, secondAnchor.y);
            
            ofSetLineWidth(1);
        }
    }
    
    //--------------------------------------------------------------
    void mouseMoved(ofMouseEventArgs& args) {
        mouse->getPosition().set(args.x, args.y, 0);
    }
    
    //--------------------------------------------------------------
    void mousePressed(ofMouseEventArgs& args) {
        drawing = true;
        tendrils.push_back(new T3ndril(physics, args.x, args.y, 0, mouse));
    }
    
    //--------------------------------------------------------------
    void mouseDragged(ofMouseEventArgs& args) {
        tendrils.back()->addPoint(args.x, args.y, 0);
    }
    
    //--------------------------------------------------------------
    void mouseReleased(ofMouseEventArgs& args) {
        drawing = false;
    }
    
    //--------------------------------------------------------------
    void keyPressed(ofKeyEventArgs& args) {
        if (args.key == ' ') {
            tendrils.clear();
            physics->clear();
        }
    }
    
    //--------------------------------------------------------------
	vector<T3ndril*>    tendrils;
    Particle*           mouse;
    float               greyer;
    bool                drawing;
    bool                nothingDrawn;

};