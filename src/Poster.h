#pragma once

class Poster {
public:
    void setup(string imagePath){
        texture.load(imagePath);

        plane.set(texture.getWidth(), texture.getHeight());
        plane.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());
        animator.setup(0.f, FinalAlpha, AnimationTime);
    }
    
    void setPosition(ofVec3f position){
        plane.setPosition(position);
    }
    
    void setOrientation(ofVec3f orientationEuler){
        plane.setOrientation(orientationEuler);
    }
    
    void draw(){
        ofPushStyle();
        ofSetColor(255, 255, 255, animator.getValue());
        texture.getTexture().bind();
        plane.draw();
        texture.getTexture().unbind();
        ofPopStyle();
    }
    
    void animate(Animator::Direction direction){
        animator.animate(direction);
    }

    ofVec3f getPosition(){
        return plane.getPosition();
    }
    
    float getWidth(){
        return plane.getWidth();
    }
    
    float getHeight(){
        return plane.getHeight();
    }
    
protected:
    const float FinalAlpha = 255.f;
    const float AnimationTime = .8f;
    
    ofTrueTypeFont font;
    ofImage texture;
    ofPlanePrimitive plane;
    Animator animator;
};