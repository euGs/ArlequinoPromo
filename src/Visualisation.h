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

//class Sprite : public Visualisation {
//public:
//    void setTear(ofPlanePrimitive tear){
//        this->tear = tear;
//    }
//
//    void setTexture(ofImage texture){
//        this->texture = texture;
//    }
//
//    virtual void drawGeometry(ofVec3f position){
//        tear.setPosition(position);
//        texture.getTexture().bind();
//        tear.draw();
//        texture.getTexture().unbind();
//    }
//
//private:
//    ofImage texture;
//    ofPlanePrimitive tear;
//};

/*
 void setup(){
 int rows = 10;
 int cols = 10;
 images.reserve(cols * rows);
 tears.reserve(cols * rows);
 
 for (int x=0; x<cols; x++){
 for (int y=0; y<rows; y++){
 shared_ptr<ofPlanePrimitive> tear = make_shared<ofPlanePrimitive>();
 tear->set(80, 60, 2, 2);
 
 shared_ptr<ofImage> image = make_shared<ofImage>();
 image->load("section_" + to_string(x) + "_" + to_string(y) + ".png");
 tear->mapTexCoords(0, 0, image->getWidth(), image->getHeight());
 tear->setPosition((x-cols/2.f) * image->getWidth(), (y-rows/2.f) * image->getHeight(), 0);
 images.push_back(image);
 
 tears.push_back(tear);
 }
 }
 
 resetGetter();
 }
*/