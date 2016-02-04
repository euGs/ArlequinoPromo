#pragma once

#include "Animator.h"

class Camera : public ofCamera {
public:
    void startRotateUp(){
        xAnimator.setup(0.f, 90.f, 2.f);
        xAnimator.animate(Animator::Direction::In);
    }
    
    void update(){
        setOrientation(ofVec3f(xAnimator.getValue(), yAnimator.getValue(), 0.f));
    }
    
protected:
    Animator xAnimator, yAnimator;
};