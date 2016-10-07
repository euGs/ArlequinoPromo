#pragma once
#include "Animator.h"
#include "Poster.h"

// A single text item, including its font.
class Text {
public:
    void setup(string text, string fontName, int fontSize, string dropShadowFilename, ofVec2f dropShadowScaling){
        this->text = text;
        this->font.load(fontName, fontSize, true, false, true);
        calculateDrawPosition();
        this->dropShadowFilename = dropShadowFilename;
        auto bb = getBoundingBox();
        this->dropShadowSize.x = bb.getWidth() * dropShadowScaling.x;
        this->dropShadowSize.y = bb.getHeight() * dropShadowScaling.y;
    }
    
    ofVec2f getDrawPosition() const{
        return textDrawPosition;
    }
    
    ofRectangle getBoundingBox() const{
        auto boundingBox = font.getStringBoundingBox(text, 0.f, 0.f);
//        boundingBox.setWidth(boundingBox.getWidth() * 1.2f);
        boundingBox.setPosition(textDrawPosition);//.x - boundingBox.getWidth() * .083f, textDrawPosition.y - 90);
        
        return boundingBox;
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
    
    string getDropShadowFilename() const{
        return dropShadowFilename;
    }
    
    ofVec2f getDropShadowSize() const{
        return dropShadowSize;
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
    string dropShadowFilename;
    ofVec2f dropShadowSize;
};

// A class to manage all text items.
class Texts {
public:
    void setup(){
        animator.setup(0.f, MaximumAlpha, DefaultAnimationDuration);
    }
    
    void addText(string text, string fontName, int fontSize, string dropShadowFilename, ofVec2f dropShadowScaling){
        unique_ptr<Text> textItem = make_unique<Text>();
        textItem->setup(text, fontName, fontSize, dropShadowFilename, dropShadowScaling);
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
        textDropShadow.setup((*textIt)->getDropShadowFilename());
        textDropShadow.setOrientation(ofVec3f(180.f, 0, 0));
        textDropShadow.setWidth((*textIt)->getDropShadowSize().x);
        textDropShadow.setHeight((*textIt)->getDropShadowSize().y);
        
        animator.animate(Animator::Direction::In);
        textDropShadow.animate(Animator::Direction::In);
    }
    
    void animateOutIfVisible(){
        if (isVisible()){
            animator.animate(Animator::Direction::Out);
        }
    }
    
    void draw(){
        if (isVisible()){
            textDropShadow.draw();
            ofPushStyle();
            ofSetColor(255, animator.getValue());
            (*textIt)->draw();
            ofPopStyle();
        }
    }
    
    vector<ofTTFCharacter> getLetterPaths(){
        auto paths = (*textIt)->getLetterPaths();
        
        return paths;
    }
    
    ofVec2f getDrawPosition(){
        return (*textIt)->getDrawPosition();
    }
    
    ofRectangle getBoundingBox(){
        return (*textIt)->getBoundingBox();
    }
    
    ofVec2f getCenterPosition(){
        auto cp = getDrawPosition() + ofVec2f(getBoundingBox().getWidth() * .5f, getBoundingBox().getHeight() * .5f);
    }
    
    bool isVisible(){
        return !animator.isAnimatedOut();
    }
    
protected:
    const float MaximumAlpha = 255;
    const float DefaultAnimationDuration = .1f;
    
    vector< unique_ptr<Text> > texts;
    vector< unique_ptr<Text> >::const_iterator textIt;
    Animator animator;
    Poster textDropShadow;
};