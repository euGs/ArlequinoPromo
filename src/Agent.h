#pragma once

#include "ofMain.h"
#include "Visualisation.h"

class Agent {
public:
    virtual void setup() = 0;
    virtual void setVisualisation(unique_ptr<Visualisation> visualisation){
        this->visualisation = std::move(visualisation);
    }
    
    virtual void update(float noiseValue1, float noiseValue2, float noiseValue3, float globalScaling = 1.f) = 0;
    virtual void draw() = 0;
    
protected:
    unique_ptr<Visualisation> visualisation;
};

class StationaryRotatingAgentOnPlane : public Agent {
public:
    void setup(){
        ori = 0.f;
        float margin = 120.f;
        pos.x = ofRandom(-ofGetWidth()/2 + margin, ofGetWidth()/2 - margin);
        pos.y = ofRandom(-ofGetHeight()/2 + margin, ofGetHeight()/2 - margin);
    }
    
    void update(float noiseValue1, float noiseValue2, float noiseValue3, float globalScaling = 1.f){
        // Adjust orientation to noise value
        ori += (noiseValue1 - .5f) * PI / 16;
    }
    
    void draw(){
        float arrowLength = 100.f;
        
        ofPoint arrow(sin(ori), cos(ori));
        arrow *= arrowLength;
        
        ofPoint arrowTip(pos + arrow);
        ofDrawLine(pos.x, pos.y, pos.z, arrowTip.x, arrowTip.y, arrowTip.z);
    }
    
    float ori;
    ofPoint pos;
};

class PlaneRovingAgent : public Agent {
public:
    void setup(){
        ori = 0.f;
        float margin = 120.f;
        pos.x = ofRandom(-ofGetWidth()/2 + margin, ofGetWidth()/2 - margin);
        pos.y = ofRandom(-ofGetHeight()/2 + margin, ofGetHeight()/2 - margin);
        minSpeed = 0.5f;
        maxSpeed = 10.f;
    }
    
    void update(float noiseValue1, float noiseValue2, float noiseValue3, float globalScaling = 1.f){
        // Adjust orientation to noise value
        ori += (noiseValue1 - .5f) * PI / 32;
        speed = ofMap(noiseValue2, 0.f, 1.f, minSpeed, maxSpeed);
        pos += ofPoint(sin(ori), cos(ori)) * speed;
        
        if (pos.x < -ofGetWidth()/2){
            pos.x = ofGetWidth()/2;
        } else if (pos.x > ofGetWidth()/2){
            pos.x = -ofGetWidth()/2;
        }
        if (pos.y < -ofGetHeight()/2){
            pos.y = ofGetHeight()/2;
        } else if (pos.y > ofGetHeight()/2){
            pos.y = -ofGetHeight()/2;
        }
    }
    
    void draw(){
        ofPushStyle();
        float arrowLength = 30.f;
        
        ofPoint arrow(sin(ori), cos(ori));
        arrow *= arrowLength;
        
        ofPoint arrowTip(pos + arrow);
        ofSetColor(ofMap(speed, minSpeed, maxSpeed, 255, 100), 100, ofMap(speed, minSpeed, maxSpeed, 100, 255));
        ofFill();
        ofDrawLine(pos.x, pos.y, arrowTip.x, arrowTip.y);
        ofPopStyle();
    }
    
    float ori;
    ofPoint pos;
    float minSpeed, maxSpeed, speed;
};

// An agent that roves on a sphere, e.g. globe.
// angleZ and angleY give the position on the surface of the sphere.
// directionalAngle gives the orientation of the point on the surface
// of the sphere, i.e. the direction in which it is moving. Equivalent
// to ori in RovingAgent above.
class SphereRovingAgent : public Agent {
public:
    virtual void setup(){
        angleZ = 0.f;
        angleY = 0.f;
        directionalAngle = ofRandom(TWO_PI);
        sphereRadius = 200.f;
        minSpeed = 0.5f;
        maxSpeed = 10.f;
        orientationEuler = ofVec3f(0, 0, 0);
    }
    
    virtual void update(float noiseValue1, float noiseValue2, float noiseValue3, float globalScaling = 1.f){
        speed = ofMap(noiseValue2, 0.f, 1.f, minSpeed, maxSpeed);
        directionalAngle += (noiseValue1 - .5f) * PI / 32;
        angleZ += sin(directionalAngle) * PI / 16.f * speed;
        angleY += cos(directionalAngle) * PI / 16.f * speed;
        sphereRadius = 200.f * globalScaling + noiseValue2 * 20.f;
        calculatePosition();
    }
    
    virtual void draw(){
        visualisation->draw(position, orientationEuler, ofMap(speed, minSpeed, maxSpeed, 0.f, 1.f));
    }
    
    virtual ofVec3f calculatePosition(){
        ofVec3f v(1, 0, 0);
        
        v.rotate(angleZ, ofVec3f(0, 0, 1));
        v.rotate(angleY, ofVec3f(0, 1, 0));
        v.scale(sphereRadius);
        
        position = v;
    }
    
protected:
    float angleZ, angleY, directionalAngle, sphereRadius;
    float minSpeed, maxSpeed, speed;
    ofVec3f position, orientationEuler;
};

class PivotingSphereRovingAgent : public SphereRovingAgent {
    virtual void setup(){
        SphereRovingAgent::setup();
    }
    virtual void update(float noiseValue1, float noiseValue2, float noiseValue3, float globalScaling = 1.f){
        SphereRovingAgent::update(noiseValue1, noiseValue2, noiseValue3, globalScaling);
        orientationEuler.x += (noiseValue1 - .5f) * PI / 32;
        orientationEuler.y = angleY;
        orientationEuler.z = angleZ;
    }
};