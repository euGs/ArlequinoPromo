#pragma once

#include "ofShader.h"
#include "ofFbo.h"

class Blur {
public:
    Blur();
    virtual void setup(float width = 0.f, float height = 0.f);
    virtual void setBlurStrength(float normalisedStrength);
    virtual void begin();
    virtual void end();
    virtual void draw(float x, float y);
    virtual bool isSetup();
    virtual void resize(float width, float height);
    virtual ofTexture & getTexture();
    
protected:
    float left, top, width, height;
    float distribution;
    float kernelSize;
    
    float minDistribution, maxDistribution, minKernelSize, maxKernelSize;
    ofShader blurShader;
    ofFbo buffer1, buffer2;
};

class RandomBlur : public Blur {
public:
    virtual void setup(float width = 0.f, float height = 0.f);
    virtual void begin();
    virtual void end();
    virtual void draw(float width, float height);
    
protected:
    float blurOnMin, blurOnMax, blurOffMin, blurOffMax, blurEnd;
    float lastBlurEndTime, thisBlurStartTime;
    bool isBlurring;
};