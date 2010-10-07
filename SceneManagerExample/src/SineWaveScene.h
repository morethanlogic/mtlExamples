#pragma once

/*
 *  SineWaveScene.h
 *  SceneManagerExample
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "mtlColorScene.h"

//========================================================================
class SineWaveScene : public mtlColorScene {
    
    public:
                SineWaveScene();
        
        void    update();
        void	draw();
        
    private:
        float   offset;
        float   step;
    
};
