#pragma once

class Animator {
public:
    enum class Direction { In, Out };

    void setup(float startValue, float endValue, float duration){
        this->startValue = startValue;
        this->endValue = endValue;
        this->duration = duration;
        
        isOut = true;
    }
    
    void animate(Direction direction){
        startTime = ofGetElapsedTimef();
        endTime = startTime + duration;
        this->direction = direction;
        isOut = false;
    }
    
    float getValue(){
        if (direction == Direction::In){
            return ofMap(ofGetElapsedTimef(), startTime, endTime, startValue, endValue, true);
        } else {
            if (ofGetElapsedTimef() > endTime){
                isOut = true;
            }
            return ofMap(ofGetElapsedTimef(), startTime, endTime, endValue, startValue, true);
        }
    }
    
    bool isAnimatedOut(){
        return isOut;
    }
    
protected:
    float startValue, endValue, duration;
    float startTime, endTime;
    Direction direction;
    bool isOut;
};