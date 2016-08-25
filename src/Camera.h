#pragma once

#include "Animator.h"

class Camera : public ofCamera {
public:
    void update(){
        auto position = ofVec3f(
            ofMap(ofGetMouseX(), 0, ofGetWidth(), 1000, -1000),
                                0.f,
                                2000.f + ofMap(ofGetMouseY(), 0, ofGetHeight(), 1000, -1000));
        setPosition(position);
    }
};