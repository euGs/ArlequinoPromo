#pragma once

#include "ofMain.h"
#include "Agents.h"
#include "AgentSource.h"
#include "Agent.h"
#include "VisualisationSource.h"
#include "Visualisation.h"
#include "Music.h"
#include "Blur.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    Agents agents;
    SphereRovingAgentSource sphereRovingAgentSource;
    TextRovingAgentSource textRovingAgentSource;
    GridAgentSource gridAgentSource;
    Music music;
    unique_ptr<Blur> blur;
};
