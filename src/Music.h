#pragma once

#include "ofMain.h"

class Music {
public:
    void setup(string musicFile){
        soundPlayer.load(musicFile);
        soundPlayer.play();
        level = 0.f;
        smoothing = .95f;
    }
    
    void update(){
        float newLevel = *(ofSoundGetSpectrum(1));
        level = level * smoothing + (1-smoothing) * newLevel;
    }
    
    float getLevel(){
        return level;
    }
    
private:
    ofSoundPlayer soundPlayer;
    float level, smoothing;
};