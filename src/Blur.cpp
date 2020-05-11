#include "Blur.h"

#include "ofGraphics.h"

Blur::Blur(){
    resize(0.f, 0.f);
}

void Blur::setup(float width, float height){
    if(ofIsGLProgrammableRenderer()){
        blurShader.load("shaders_gl3/passThrough.vert", "shaders_gl3/gaussianBlur.frag");
    }
    else{
        blurShader.load("", "shaders/gaussianBlur.frag");
    }
    
    resize(width, height);
    
    distribution = 1.f;
    kernelSize = 5.f;
    
    minDistribution = .2f;
    maxDistribution = 5.f;
    minKernelSize = 1.f;
    maxKernelSize = 15.f;
}

void Blur::setBlurStrength(float normalisedStrength){
    normalisedStrength = ofClamp(normalisedStrength, 0, 1);
    
    // Apply easing.
    normalisedStrength = normalisedStrength * normalisedStrength * normalisedStrength;
    
    distribution = ofMap(normalisedStrength, 0, 1, minDistribution, maxDistribution);
    kernelSize = ofMap(normalisedStrength, 0, 1, minKernelSize, maxKernelSize);
}

void Blur::begin(){
    if (!blurShader.isLoaded()){
        ofLogWarning() << "Blur::begin(): shader isn't loaded. Blur::setup() needs to be called before Blur::begin()" << endl;
        return;
    }
    
    // Source geometry will be drawn into buffer1.
    buffer1.begin();
    ofClear(0);
}

void Blur::end(){
    if (!blurShader.isLoaded()){
        ofLogWarning() << "Blur::end(): shader isn't loaded. Blur::setup() and Blur::begin() need to be called before Blur::end()" << endl;
        return;
    }
    
    buffer1.end();
    
    // buffer2 will store the results of the vertical pass of the blur shader.
    buffer2.begin();
    ofClear(0);
    // Draw buffer1 one through the blur shader with a vertical pass.
    blurShader.begin();
    blurShader.setUniform2f("direction", 0.f, 1.f);
    blurShader.setUniform1f("kernelSize", kernelSize);
    blurShader.setUniform1f("distribution", distribution);
    buffer1.draw(0.f, 0.f);
    blurShader.end();
    buffer2.end();
}

void Blur::draw(float x, float y){
    // Draw buffer2 through the blur shader with a horizontal pass.
    blurShader.begin();
    blurShader.setUniform2f("direction", 1.f, 0.f);
    blurShader.setUniform1f("kernelSize", kernelSize);
    blurShader.setUniform1f("distribution", distribution);
    buffer2.draw(x, y);
    blurShader.end();
}

bool Blur::isSetup(){
    return buffer1.getWidth() != 0.f && buffer1.getHeight() != 0.f;
}

void Blur::resize(float width, float height){
    if (width <= 0.f || height <= 0.f){
        return;
    }
    
    buffer1.allocate(width, height);
    buffer2.allocate(width, height);
}

ofTexture & Blur::getTexture(){
    return buffer1.getTexture();
}

void RandomBlur::setup(float width, float height){
    Blur::setup(width, height);
    
    isBlurring = false;
    setBlurStrength(0.8f);
    blurOffMin = 2.f;
    blurOffMax = 4.f;
    blurOnMin = 2.f;
    blurOffMax = 4.f;
    lastBlurEndTime = ofGetElapsedTimef();
    thisBlurStartTime = ofGetElapsedTimef();
}

void RandomBlur::begin(){
    // if blur not on
    // and it has been a while since blurring
    // with some random time shifting
    // animate blur in for a while, and then out
    
    if (!isBlurring){
        if (ofGetElapsedTimef() - lastBlurEndTime > blurOffMin){
            isBlurring = true;
            thisBlurStartTime = ofGetElapsedTimef();
        }
    } else {
        if (ofGetElapsedTimef() - thisBlurStartTime > blurOnMin){
            isBlurring = false;
            lastBlurEndTime = ofGetElapsedTimef();
        }
    }
    
    if (isBlurring){
        Blur::begin();
    }
}

void RandomBlur::end(){
    if (isBlurring){
        Blur::end();
    }
}

void RandomBlur::draw(float x, float y){
    if (isBlurring){
        Blur::draw(x, y);
    }
}
