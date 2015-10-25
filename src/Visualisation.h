#pragma once

#include "ofMain.h"

class Visualisation {
public:
    virtual void draw(ofVec3f position, float normalisedSpeed) = 0;
};

class SphereVisualisation : public Visualisation {
public:
    SphereVisualisation(){
        sphere.setRadius(10.f);
    }
    
    void draw(ofVec3f position, float normalisedSpeed){
        ofPushStyle();
        sphere.setPosition(position);
        ofSetColor(ofMap(normalisedSpeed, 0.f, 1.f, 255.f, 100.f), 100, ofMap(normalisedSpeed, 0.f, 1.f, 100.f, 255.f), 255);
        sphere.draw();
        ofPopStyle();
    }
    
private:
    ofSpherePrimitive sphere;
};

class SpriteVisualisation : public Visualisation {
public:
    void setup(ofPlanePrimitive plane, ofImage texture){
        this->plane = plane;
        this->texture = texture;
    }

    void draw(ofVec3f position, float normalisedSpeed){
        plane.setPosition(position);
        texture.getTexture().bind();
        plane.draw();
        texture.getTexture().unbind();
    }

private:
    ofImage texture;
    ofPlanePrimitive plane;
};