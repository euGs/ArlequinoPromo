#pragma once

#include "ofMain.h"
#include "Visualisation.h"

// Move data for agents to use as they wish.
struct MoveData {
    float normalisedValue1;
    float normalisedValue2;
    float globalScaling = 1.f;
};

// Agent base class. Owns a visualisation and position, orientation and speed values.
// Derived classes define calculations for position and orientation based on
// values input to update function.
class Agent {
public:
    virtual void setup(){
        orientationEuler = ofVec3f(0, 0, 0);
        position = ofVec3f(0, 0, 0);
    }
    
    virtual void setVisualisation(unique_ptr<Visualisation> visualisation){
        this->visualisation = std::move(visualisation);
    }
    
    virtual unique_ptr<Visualisation> getVisualisation(){
        return std::move(this->visualisation);
    }
    
    virtual void update(MoveData &moveData) = 0;
    
    virtual void setSpeed(float normalisedValue){
        speed = ofMap(normalisedValue, 0.f, 1.f, MinSpeed, MaxSpeed);
    }

    virtual void draw(){
        visualisation->draw(position, orientationEuler);
    }
    
    ofVec3f getPosition() const{
        return position;
    }
    
    ofVec3f getOrientationEuler() const{
        return orientationEuler;
    }
    
protected:
    constexpr static float MinSpeed = .5f;
    constexpr static float MaxSpeed = 10.f;

    unique_ptr<Visualisation> visualisation;
    float minSpeed, maxSpeed, speed;
    ofVec3f position, orientationEuler;
};

// Roves around a plane.
class PlaneRovingAgent : public Agent {
public:
    virtual void setup() override{
        ori = 0.f;
        float margin = 120.f;
        pos.x = ofRandom(-ofGetWidth()/2 + margin, ofGetWidth()/2 - margin);
        pos.y = ofRandom(-ofGetHeight()/2 + margin, ofGetHeight()/2 - margin);
        minSpeed = 0.5f;
        maxSpeed = 10.f;
    }
    
    virtual void update(MoveData &moveData) override{
        // Adjust orientation to noise value
        ori += (moveData.normalisedValue1 - .5f) * PI / 32;
        speed = ofMap(moveData.normalisedValue2, 0.f, 1.f, minSpeed, maxSpeed);
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
    
    virtual void draw() override{
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
    virtual void setup() override{
        Agent::setup();
        
        angleZ = 0.f;
        angleY = 0.f;
        directionalAngle = ofRandom(TWO_PI);
        sphereRadius = 200.f;
    }
    
    virtual void update(MoveData &moveData) override{
        setSpeed(moveData.normalisedValue2);
        directionalAngle += (moveData.normalisedValue1 - .5f) * PI / 32;
        angleZ += sin(directionalAngle) * PI / 16.f * speed;
        angleY += cos(directionalAngle) * PI / 16.f * speed;
        sphereRadius = 200.f * moveData.globalScaling + moveData.normalisedValue2 * 20.f;
        calculatePosition();
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
};

// As SphereRovingAgent but also orients towards the direction of motion.
class PivotingSphereRovingAgent : public SphereRovingAgent {
    virtual void setup() override{
        SphereRovingAgent::setup();
    }
    
    virtual void update(MoveData &moveData) override{
        SphereRovingAgent::update(moveData);
        orientationEuler.x += (moveData.normalisedValue1 - .5f) * PI / 32;
        orientationEuler.y = angleY;
        orientationEuler.z = angleZ;
    }
};

// An agent that roves around the vertices in a mesh.
class MeshRovingAgent : public Agent {
public:
    void setMinimumDistance(const float minimumDistance){
        this->MinimumDistance = minimumDistance;
    }
    
    void setMesh(shared_ptr<const ofMesh> mesh){
        this->mesh = mesh;
    }
    
    virtual void setup() override{
        Agent::setup();
        
        position = getRandomVertex();
        target = getRandomVertex();
    }
    
    virtual void update(MoveData &moveData) override{
        if (mesh == nullptr){
            return;
        }
        
        setSpeed(moveData.normalisedValue2);

        float distance = position.distance(target);
        
        if (distance < MinimumDistance){
            target = getRandomVertex();
        }
        
        position = position + speed * (target - position).getNormalized();
    }
    
protected:
    ofVec3f getRandomVertex(){
        auto numVertices = mesh->getNumVertices();
        auto randomIndex = ofRandom(numVertices);
        return mesh->getVertex(randomIndex);
    }
    
    shared_ptr<const ofMesh> mesh;
    float MinimumDistance;
    ofVec3f target;
};

// Linearly interpolates position from a start position to an end position.
// Expects the normalised lerp value to be MoveData::normalisedValue1
class LerpingAgent : public Agent {
public:
    void setStartPosition(ofVec3f startPosition){
        this->startPosition = startPosition;
    }
    
    void setEndPosition(ofVec3f endPosition){
        this->endPosition = endPosition;
    }
    
    virtual void update(MoveData &moveData) override{
        position = startPosition + (endPosition - startPosition) * moveData.normalisedValue1;
    }
    
protected:
    ofVec3f startPosition;
    ofVec3f endPosition;
    float startTime, endTime;
};

class StaticAgent : public Agent {
    void setPosition(ofVec3f position){
        this->position = position;
    }
    
    void setOrientationEuler(ofVec3f orientationEuler){
        this->orientationEuler = orientationEuler;
    }
    
    virtual void setup() override{
    }
    
    virtual void update(MoveData &moveData) override{
    }
    
    virtual void draw() override{
    }
};