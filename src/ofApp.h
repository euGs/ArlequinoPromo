#pragma once

#include "ofMain.h"

#include "Agents.h"
#include "AgentSource.h"
#include "Agent.h"
#include "VisualisationSource.h"
#include "Visualisation.h"
#include "Music.h"
//#include "Blur.h"
#include "Animator.h"
#include "Text.h"
#include "Poster.h"
#include "Camera.h"
//#include "Shadows.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void drawText();
    
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
    
protected:
    const int Cols = 32;
    const int Rows = 18;
    const int MaxAgents = 1000;
    const float DesiredCamDistance = 2000;
    const float DefaultCamDistance = 650;
    
    Camera cam;
    shared_ptr<Agents> agents;
    CrumpledPaperVisualisationSource visualisationSource;
    SphereRovingAgentSource sphereRovingAgentSource;
    TextRovingAgentSource textRovingAgentSource;
    BasicBoundAgentSource basicBoundAgentSource;
    SimplerTextRovingAgentSource simplerTextRovingAgentSource;
    GridAgentSource gridAgentSource;
    Music music;
    Texts texts;
    Poster poster;
    ofShader agentsShader;
//    Shadows shadows;
};
