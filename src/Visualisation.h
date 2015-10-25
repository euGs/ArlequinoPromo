#pragma once

#include "ofMain.h"

class Visualisation {
public:
    virtual void draw() = 0;
};

class SphereVisualisation : public Visualisation {
public:
    virtual void draw(){
        ofDrawEllipse(0, 0, 10, 10);
    }
};