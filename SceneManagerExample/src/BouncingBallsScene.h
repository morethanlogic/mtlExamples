#pragma once

/*
 *  BouncingBallsScene.h
 *  SceneManagerExample
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "mtlColorScene.h"

//========================================================================
class Ball {
    
    public:
        Ball(float _x, float _y) {
            x    = _x;
            y    = _y;
            xDir = ofRandom(-5, 5);
            yDir = ofRandom(-5, 5);
        }
        
        //--------------------------------------
        // Moves and changes direction if it hits a wall.
        void update() {
            if (x - size/2 < 0 || x + size/2 > ofGetWidth())  xDir *= -1;
            if (y - size/2 < 0 || y + size/2 > ofGetHeight()) yDir *= -1;
            x += xDir;
            y += yDir;
        }
        
        //--------------------------------------
        void draw(float _alphaScale) {
            ofSetColor(0, 0, 0, 100 * _alphaScale);
            ofFill();
            ofCircle(x, y, size);
        }
        
        float x; 
        float y; 
        float xDir;
        float yDir;
    
        static float size;
    
};

//========================================================================
class BouncingBallsScene : public mtlColorScene {
    
    public:
                BouncingBallsScene(int _r, int _g, int _b);
                ~BouncingBallsScene();
    
        void    enter();
        void    exit();
    
        void    update();
        void	draw();
    
        void    addBall(int _x, int _y);
    
        void    touchDown(ofTouchEventArgs& _touch);
    
    private:
        bool            entering;
        bool            exiting;
    
        vector<Ball*>   balls;
    
};

