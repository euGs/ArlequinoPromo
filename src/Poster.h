#pragma once

class Poster {
public:
    void setup(string imagePath, ofVec3f position, ofVec3f orientationEuler, string text, string fontName, int fontSize, ofVec3f textLocalPosition){
        this->position = position;
        this->orientationEuler = orientationEuler;
        this->text = text;
        this->font.load(fontName, fontSize, true, false, true);
        this->textLocalPosition = textLocalPosition;
        
        texture.load("Cover01.jpg");

        plane.set(texture.getWidth(), texture.getHeight());
        plane.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        animator.setup(0.f, FinalAlpha, AnimationTime);
    }
    
    void draw(){
        ofPushStyle();
        ofSetColor(255, 255, 255, animator.getValue());
        texture.getTexture().bind();
        plane.draw();
        texture.getTexture().unbind();
        font.drawString(text, position.x + textLocalPosition.x, position.y + textLocalPosition.y);
        ofPopStyle();
    }
    
    void animateIn(){
        animator.animate(Animator::Direction::In);
    }
    
    ofVec3f getPosition(){
        return position;
    }
    
protected:
    const float FinalAlpha = 255.f;
    const float AnimationTime = .8f;
    
    SpriteVisualisation poster;
    ofVec3f position;
    ofVec3f orientationEuler;
    ofTrueTypeFont font;
    string text;
    ofVec3f textLocalPosition;
    ofImage texture;
    ofPlanePrimitive plane;
    Animator animator;
};