//
//  Shadows.h
//  arlequinoPromo01
//
//  Created by euGs on 08/05/2016.
//
//

#pragma once

#include <memory>
#include "ofMain.h"
#include "Agents.h"
#include "Blur.h"
#include "Camera.h"

class Shadows {
public:
    void setup(shared_ptr<Agents> agents, float desiredCamDistance);
    void draw();
    
protected:
    ofVec3f shadowPosition = {0.f, -750.f, 0.f};
    ofVec3f shadowOrientation = {90.f, 0.f, 0.f};
    float shadowWidth = 1600.f;
    float shadowHeight = 1600.f;
    float shadowResolutionFactor = .25f;
    const int ProportionOfAgentsInShadow = 5;   // Only every x agent is rendered.
    float desiredCamDistance;
    
    shared_ptr<Agents> agents;
    Camera shadowCam;
    Blur shadowBlur;
    ofPlanePrimitive shadowPlane;
    ofShader shadowsShader;
};