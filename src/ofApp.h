#pragma once

#include "ofMain.h"
#include "Agents.h"
#include "AgentSource.h"
#include "Agent.h"
#include "VisualisationSource.h"
#include "Visualisation.h"
#include "Music.h"
#include "Blur.h"
#include "Animator.h"
#include "Text.h"
#include "Poster.h"
#include "Camera.h"

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
    ofVec3f shadowPosition = {0.f, -750.f, 0.f};
    ofVec3f shadowOrientation = {90.f, 0.f, 0.f};
    float shadowWidth = 400.f;
    float shadowHeight = 400.f;
    const int ProportionOfAgentsInShadow = 5;   // Only every x agent is rendered.
    
    Camera cam;
    Agents agents;
    CrumpledPaperVisualisationSource visualisationSource;
    SphereRovingAgentSource sphereRovingAgentSource;
    TextRovingAgentSource textRovingAgentSource;
    GridAgentSource gridAgentSource;
    Music music;
    Blur blur;
    Texts texts;
    Poster poster;
    Camera shadowCam;
    ofFbo shadowFbo;
    ofPlanePrimitive shadowPlane;
    ofShader agentsShader, shadowsShader;
};
