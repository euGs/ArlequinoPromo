#pragma once

class Poster {
public:
    void setup(string imagePath, ofVec3f position, ofVec3f orientationEuler){
        texture.load("Cover01.jpg");

        plane.set(texture.getWidth(), texture.getHeight());
        plane.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        animator.setup(0.f, FinalAlpha, AnimationTime);
    }
    
    void draw(){
        ofPushStyle();
        ofSetColor(255, 255, 255, animator.getValue());
        texture.getTexture().bind();
        plane.draw();
        texture.getTexture().unbind();
        ofPopStyle();
    }
    
    void animateIn(){
        animator.animate(Animator::Direction::In);
    }
    
protected:
    const float FinalAlpha = 255.f;
    const float AnimationTime = .8f;
    
    ofTrueTypeFont font;
    ofImage texture;
    ofPlanePrimitive plane;
    Animator animator;
};