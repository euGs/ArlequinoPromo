#pragma once

#include "ofMain.h"

class Visualisation {
public:
    virtual void draw(ofVec3f position, ofVec3f orientationEuler, float normalisedSpeed) = 0;
};

class SphereVisualisation : public Visualisation {
public:
    SphereVisualisation(){
        sphere.setRadius(10.f);
    }
    
    virtual void draw(ofVec3f position, ofVec3f orientationEuler, float normalisedSpeed){
        ofPushStyle();
        sphere.setPosition(position);
        sphere.setOrientation(orientationEuler);
        ofSetColor(ofMap(normalisedSpeed, 0.f, 1.f, 255.f, 100.f), 100, ofMap(normalisedSpeed, 0.f, 1.f, 100.f, 255.f), 255);
        sphere.draw();
        ofPopStyle();
    }
    
protected:
    ofSpherePrimitive sphere;
};

class SpriteVisualisation : public Visualisation {
public:
    virtual void setup(ofPlanePrimitive plane, ofImage texture){
        this->plane = plane;
        this->texture = texture;
    }

    virtual void draw(ofVec3f position, ofVec3f orientationEuler, float normalisedSpeed){
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        texture.getTexture().bind();
        plane.draw();
        texture.getTexture().unbind();
    }

protected:
    ofImage texture;
    ofPlanePrimitive plane;
};

class TornPaperVisualisation : public SpriteVisualisation {
public:
    virtual void setup(ofPlanePrimitive plane, ofImage texture){
        SpriteVisualisation::setup(plane, texture);
        
        ofMesh & mesh = this->plane.getMesh();
        float maxDisplacement = plane.getWidth();

        for (size_t i=0; i<mesh.getNumVertices(); i++){
            ofVec3f displacement(ofRandom(maxDisplacement), ofRandom(maxDisplacement), ofRandom(maxDisplacement));
            ofVec3f vertex = mesh.getVertex(i);
            vertex += displacement;

            mesh.setVertex(i, vertex);
        }
    }
};