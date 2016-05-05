#pragma once

#include "ofMain.h"

class Visualisation {
public:
    virtual void draw(ofVec3f position, ofVec3f orientationEuler) = 0;
    virtual void drawUntextured(ofVec3f position, ofVec3f orientationEuler) {
    };
    virtual void bringItHome(float durationSeconds) {
    };
};

class SphereVisualisation : public Visualisation {
public:
    SphereVisualisation(){
        sphere.setRadius(10.f);
    }
    
    virtual void draw(ofVec3f position, ofVec3f orientationEuler){
        ofPushStyle();
        sphere.setPosition(position);
        sphere.setOrientation(orientationEuler);
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

    virtual void draw(ofVec3f position, ofVec3f orientationEuler) override{
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        texture.getTexture().bind();
        plane.draw();
        texture.getTexture().unbind();
    }
    
    virtual void drawUntextured(ofVec3f position, ofVec3f orientationEuler) override{
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        plane.draw();
    }

protected:
    ofImage texture;
    ofPlanePrimitive plane;
};

class TornPaperVisualisation : public SpriteVisualisation {
public:
    virtual void setup(ofPlanePrimitive plane, ofImage texture) override{
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
    virtual void setup(ofPlanePrimitive plane, ofImage texture) override{
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
    
    virtual void draw(ofVec3f position, ofVec3f orientationEuler) override{
        TornPaperVisualisation::draw(position, orientationEuler);
        
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

// A visualisation that is like crumpled paper in its normal state but
// can uncrumple back to flat paper on command.
class UncrumplingPaperVisualisation : public TornPaperVisualisation {
public:
    virtual void setup(ofPlanePrimitive plane, ofImage texture) override{
        // Cache the original flat mesh.
        ofMesh & mesh = plane.getMesh();
        flatMesh = mesh;
        
        for (size_t i=0; i<mesh.getNumVertices(); i++){
            flatMesh.setVertex(i, mesh.getVertex(i));
        }
        
        // Let TornPaperVisualisation do the crumpling.
        TornPaperVisualisation::setup(plane, texture);
        
        // Cache the crumpled mesh.
        mesh = this->plane.getMesh();
        crumpledMesh = mesh;

        for (size_t i=0; i<mesh.getNumVertices(); i++){
            crumpledMesh.setVertex(i, mesh.getVertex(i));
        }
    }
    
    virtual void bringItHome(float normalisedHomeness) override{
        ofMesh & mesh = plane.getMesh();
        
        for (int i=0; i<mesh.getNumVertices(); i++){
            ofVec3f vertex = flatMesh.getVertex(i) - crumpledMesh.getVertex(i);

            mesh.setVertex(i, crumpledMesh.getVertex(i) + vertex*normalisedHomeness);
        }
    }
    
protected:
    ofMesh flatMesh, crumpledMesh;
};