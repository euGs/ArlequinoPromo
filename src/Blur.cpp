#include "Blur.h"

void Blur::setup(float x, float y, float width, float height){
    if(ofIsGLProgrammableRenderer()){
        blurShader.load("shaders_gl3/passThrough.vert", "shaders_gl3/gaussianBlur.frag");
    }
    else{
        blurShader.load("", "shaders/gaussianBlur.frag");
    }
    
    this->x = x;
    this->y = y;
    
    buffer1.allocate(width, height);
    buffer2.allocate(width, height);
    
    distribution = 1.f;
    kernelSize = 9.f;
    brightness = 1.f;
}

void Blur::begin(){
    if (!blurShader.isLoaded()){
        ofLogWarning() << "Blur::begin(): shader isn't loaded. Blur::setup() needs to be called before Blur::begin()" << endl;
        return;
    }
    
    // Source geometry will be drawn into buffer1.
//    buffer1.begin();
    blurShader.begin();
    blurShader.setUniform2f("direction", 0.f, 1.f);
    blurShader.setUniform1f("kernelSize", kernelSize);
    blurShader.setUniform1f("distribution", distribution);
    blurShader.setUniform1f("brightness", brightness);

    ofClear(0);
    ofBackground(0, 0, 255);
}

void Blur::end(){
    if (!blurShader.isLoaded()){
        ofLogWarning() << "Blur::end(): shader isn't loaded. Blur::setup() and Blur::begin() need to be called before Blur::end()" << endl;
        return;
    }
    
//    buffer1.end();
    
    // buffer2 will store the results of the vertical pass of the blur shader.
//    buffer2.begin();
    ofClear(0, 0, 255);
    // Draw buffer1 one through the blur shader with a vertical pass.
//    blurShader.begin();
//    blurShader.setUniform2f("direction", 0.f, 1.f);
//    blurShader.setUniform1f("kernelSize", kernelSize);
//    blurShader.setUniform1f("distribution", distribution);
//    blurShader.setUniform1f("brightness", brightness);
//    buffer1.draw(0, 0);
    blurShader.end();
//    buffer2.end();
    
    // Draw buffer2 through the blur shader with a horizontal pass.
//    blurShader.begin();
//    blurShader.setUniform2f("direction", 1.f, 0.f);
//    blurShader.setUniform1f("kernelSize", kernelSize);
//    blurShader.setUniform1f("distribution", distribution);
//    blurShader.setUniform1f("brightness", brightness);
//    buffer2.draw(0, 0);
//    blurShader.end();
}