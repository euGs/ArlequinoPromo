#pragma once
#include "Animator.h"

// A single text item, including its font.
class Text {
public:
    void setup(string text, string fontName, int fontSize){
        this->text = text;
        this->font.load(fontName, fontSize, true, false, true);
        calculateDrawPosition();
    }
    
    ofVec2f getDrawPosition() const{
        return textDrawPosition;
    }
    
    vector<ofTTFCharacter> getLetterPaths() const{
        return font.getStringAsPoints(text, false);
    }
    
    string getText() const{
        return text;
    }
    
    void draw() const{
        font.drawString(text, textDrawPosition.x, textDrawPosition.y);
    }
    
protected:
    void calculateDrawPosition(){
        auto boundingBox = font.getStringBoundingBox(text, 0.f, 0.f);
        textDrawPosition.x = -(boundingBox.width)/2.f;
        textDrawPosition.y = -(boundingBox.height)/2.f;
        
        auto numExtraLines = std::count(text.cbegin(), text.cend(), '\n');
        textDrawPosition.y += (boundingBox.height * numExtraLines / 2.f);
    }
    
    string text;
    ofTrueTypeFont font;
    ofVec2f textDrawPosition;
};

// A class to manage all text items.
class Texts {
public:
    void setup(){
        animator.setup(0.f, MaximumAlpha, DefaultAnimationDuration);
    }
    
    void addText(string text, string fontName, int fontSize){
        unique_ptr<Text> textItem = make_unique<Text>();
        textItem->setup(text, fontName, fontSize);
        texts.emplace_back(move(textItem));
        textIt = this->texts.cend();
    }
    
    void cycleText(){
        if (textIt == texts.cend()){
            textIt = texts.cbegin();
        } else {
            textIt++;
            
            if (textIt == texts.cend()){
                textIt = texts.cbegin();
            }
        }
    }
    
    void animateIn(){
        animator.animate(Animator::Direction::In);
    }
    
    void animateOutIfVisible(){
        if (isVisible()){
            animator.animate(Animator::Direction::Out);
        }
    }
    
    void draw(){
        if (isVisible()){
            ofPushStyle();
            ofSetColor(255, animator.getValue());
            (*textIt)->draw();
            ofPopStyle();
        }
    }
    
    vector<ofTTFCharacter> getLetterPaths(){
        return (*textIt)->getLetterPaths();
    }
    
    ofVec2f getDrawPosition(){
        return (*textIt)->getDrawPosition();
    }
    
    bool isVisible(){
        return !animator.isAnimatedOut();
    }
    
protected:
    const float MaximumAlpha = 255;
    const float DefaultAnimationDuration = 1.f;
    
    vector< unique_ptr<Text> > texts;
    vector< unique_ptr<Text> >::const_iterator textIt;
    Animator animator;
};