#pragma once

#include "ofMain.h"

class Blur {
public:
    void setup(float x, float y, float width, float height);
    void begin();
    void end();
    
    float x, y;
    float backgroundColor;
    float distribution;
    float kernelSize;
    float brightness;
    
private:
    ofShader blurShader;
    ofFbo buffer1, buffer2;
};