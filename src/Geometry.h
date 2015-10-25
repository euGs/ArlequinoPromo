#pragma once

#include "ofMain.h"

class GeometrySource {
public:
    virtual void setup() = 0;
    virtual void resetGetter() = 0;
    virtual shared_ptr<ofNode> getCurrentElement() = 0;
    virtual shared_ptr<ofImage> getCurrentTexture() = 0;
    virtual void next() = 0;
    virtual bool areMoreElements() = 0;
};

class EpCoverTears : public GeometrySource {
public:
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
    
    void resetGetter(){
        index = 0;
    }
    
    shared_ptr<ofNode> getCurrentElement(){
        return tears[index];
    }
    
    shared_ptr<ofImage> getCurrentTexture(){
        return images[index];
    }
    
    void next(){
        index++;
    }

    bool areMoreElements(){
        return index < tears.size();
    }
    
    size_t index;
    vector< shared_ptr<ofImage> > images;
    vector< shared_ptr<ofPlanePrimitive> > tears;
};