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
}

void Shadows::draw(){
    if (agents == nullptr){
        ofLogError() << "ShadowRenderer::draw - can't draw - agents == nullptr" << endl;
        return;
    }
    
    // Render agents into shadow blur.
    shadowBlur.begin();
    shadowCam.begin();
    shadowsShader.begin();
    shadowsShader.setUniform1f("alpha", 1);//ofMap(music.getLevel(), 0.f, 0.15f, 0.f, 1.f, true));
    agents->drawUntextured(ProportionOfAgentsInShadow);
    shadowsShader.end();
    shadowCam.end();
    shadowBlur.end();
    
    // Draw shadow from shadow blur.
    shadowBlur.getTexture().bind();
    shadowPlane.draw();
    shadowBlur.getTexture().unbind();
}