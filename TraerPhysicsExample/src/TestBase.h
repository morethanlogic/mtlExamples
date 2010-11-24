#pragma once

/*
 *  BaseTest.h
 *  TraerPhysicsExample
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ofMain.h"
#include "mtlTraerPhysics.h"
using namespace mtl;

//========================================================================
class TestBase {
    
public:
    virtual         ~TestBase() {}
    virtual void    update()    {}
    virtual void    draw()      {}
    
    ParticleSystem* physics;
    
};