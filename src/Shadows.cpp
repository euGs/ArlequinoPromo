//
//  Shadows.cpp
//  arlequinoPromo01
//
//  Created by euGs on 08/05/2016.
//
//

#include "Shadows.h"

void Shadows::setup(shared_ptr<Agents> agents, float desiredCamDistance){
    this->agents = agents;
    
    shadowsShader.load("shaders_gl3/floorShadows");
    shadowBlur.setup(shadowWidth*shadowResolutionFactor, shadowHeight*shadowResolutionFactor);
    shadowBlur.setBlurStrength(1.f);
    shadowCam.setPosition(0.f, -desiredCamDistance, 0.f);
    shadowCam.setOrientation({90.f, 0.f, 0.f});
    shadowPlane.set(shadowWidth, shadowHeight);
    shadowPlane.setPosition(shadowPosition);
    shadowPlane.setOrientation(shadowOrientation);
    shadowPlane.mapTexCoords(0, 0, shadowWidth*shadowResolutionFactor, shadowHeight*shadowResolutionFactor);
    fbo.allocate(shadowWidth, shadowHeight, GL_RGBA);
}

void Shadows::draw(float alpha){
    if (agents == nullptr){
        ofLogError() << "ShadowRenderer::draw - can't draw - agents == nullptr" << endl;
        return;
    }
    
    // Render agents into fbo.
    fbo.begin();
    ofClear(255.f, 0.f);
    shadowBlur.begin();
    shadowCam.begin();
    shadowsShader.begin();
    shadowsShader.setUniform1f("alpha", alpha);
    agents->drawUntextured(ProportionOfAgentsInShadow);
    shadowsShader.end();
    shadowCam.end();
    shadowBlur.end();
    shadowBlur.draw(0.f, 0.f);
    fbo.end();
    
    // Draw shadow from shadow blur.
    fbo.getTexture().bind();
    shadowPlane.draw();
    fbo.getTexture().unbind();
}