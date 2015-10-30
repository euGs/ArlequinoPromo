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

class TornPaperWithParticlesVisualisation : public TornPaperVisualisation {
public:
    virtual void setup(ofPlanePrimitive plane, ofImage texture){
        TornPaperVisualisation::setup(plane, texture);
        
        color = texture.getColor(0, 0);
        
        for (int i=0; i<1; i++){
            ofSpherePrimitive particle;
            particle.setRadius(1);
            // Random positions for all particles within a bounding rect.
            particlesRelativePositions.push_back(ofVec3f(ofRandom(-10, 10), ofRandom(-200, 10), 0));
            
            particles.push_back(particle);
        }
    }
    
    virtual void draw(ofVec3f position, ofVec3f orientationEuler, float normalisedSpeed){
        TornPaperVisualisation::draw(position, orientationEuler, normalisedSpeed);
        
        if (plane.getPosition().y > ofGetHeight()/2){
            return;
        }
        
        float noiseScale = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1.f);
        float noiseVel = ofGetElapsedTimef();

        for (int i=0; i<particles.size(); i++){
            float noiseValue1 = ofNoise(i * noiseScale, 200 * noiseScale, noiseVel) - .5f;
            float noiseValue2 = ofNoise(i * noiseScale, 1200 * noiseScale, noiseVel);
            
            particlesRelativePositions[i] += ofVec3f(noiseValue1, 1.f + noiseValue2, 0);
            
            if (particlesRelativePositions[i].y > upperLimit){
                particlesRelativePositions[i] = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), 0);
            }

            ofPushStyle();
            ofSetColor(color, ofMap(particlesRelativePositions[i].y, upperLimit, 0, 0, 255));
            if (particlesRelativePositions[i].y < 0){
                ofSetColor(color, 0);
            }
            particles[i].setPosition(plane.getPosition() + particlesRelativePositions[i]);
            particles[i].draw();
            ofPopStyle();
        }
    }
    
protected:
    vector<ofVec3f> particlesRelativePositions;
    vector<ofSpherePrimitive> particles;
    ofColor color;
    float upperLimit = 100;
};