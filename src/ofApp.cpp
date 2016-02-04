#include "ofApp.h"

/*
 *** Now (Poster and final grid are not properly aligned. Calculate their positions 
 accurately - know where both of their origins are - and position them for the moving
 camera):
 Camera if not doing wind
 ------------------------
 As agents switch from sphere roving to text roving and back, they always move
 to a new location and the camera has to pan to follow. Finally when they
 move into position for the poster the camera has to tilt.
 
 More impressive/professional visuals
 ------------------------------------
 Give agents random orientations: it looks like they are all aligned to the same plane.
 
 Get agents following text even better.

 Get particles back in - try outside of camera rendering (always view oriented)

 Glitch, incl. just changing seeding on movements
 
 Glitch: make it look like the camera has accidentally moved on the horizontal -
 not an orbit but a short translation on the horizontal - and back again - gives
 the sense of a camera actually being there

 Add easing to transitions
 
 Wind etc
 --------
 Wind effects: Have the paper respond to wind. The strength and direction of the wind
 is driven by noise. Each tear would then need to respond to both wind and music,
 which probably means a force-based system (which is difficult, because the response
 to music isn't so).
 
 Agent type for one that gets pushed along as if by wind: can accept a force
 that pushes it forward and up a bit, while a second force (due to gravity) is
 pulling it down.
 
 Script/control from ofApp / create a Director class / just do it live for
 starting with one agent that gets pushed along as if by wind. It flies out
 of frame and camera pans to follow / get back in frame. Then we see that
 it's heading to a particular location and many other agents are going too.
 When they all arrive they start following the music (SphereRovingAgent with
 sphere radius set to music sound intensity). As the animation goes on and
 agents switch from sphere roving to text roving and back, they always move
 to a new location and the camera has to pan to follow. Finally when they 
 move into position for the poster the camera has to tilt.
 
 Visual test
 -----------
 Check speed of paper tears (also on text)
 
 Mastering
 ---------
 Colorisation options
 
 Fade in from white to sphere-based at start
 
 Redo image so you can see his legs.
 
 Rendering
 ---------
 Try export to 3D
 
 Try import to Blender and render there
 
 Extras
 -----
 Flapping paper tears, like birds. First try didn't work. Killed frame rate. But I
 had timing values/calculations in each of the 100 tears. With only one calculation
 leading to a normalised value (in Agents class), it might ease the load a bit. Flapping
 could also be binary-state/basic animation, i.e. only have 2 frames.
 
 Nicer
 ----
 Use time literals for animations: 1s or 1.s whatever C++14 will allow
 
 Make it explicit that transitions are non-interruptable. Interrupting one now will
 result in a null pointer exception.
 
 Have state on Animator instead of bool - reads better
 
 */

//--------------------------------------------------------------
void ofApp::setup(){
    const int Cols = 32;
    const int Rows = 18;
    const int MaxAgents = 1000;
    const float DesiredCamDistance = 2000;
    const float DefaultCamDistance = 650;
    const ofVec3f PosterPosition {35, -50, 1100};
    const ofVec3f PosterOrientation {180, 0, 0};
    
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(Cols, Rows);
    visualisationSource.setup();
    sphereRovingAgentSource.setup();

    agents.setup(sphereRovingAgentSource, visualisationSource, MaxAgents);
    music.setup("ArTeaser_Edit04.wav");
    
    textRovingAgentSource.setup();
    gridAgentSource.setDimensions(Cols, Rows, visualisationSource.getColWidth(), visualisationSource.getRowHeight());
    gridAgentSource.setPosition(PosterPosition);
    gridAgentSource.setup();
    
    poster.setup("Cover01.jpg", PosterPosition, PosterOrientation, "www.arlequino.com", "Ubuntu-R.ttf", 100, {0, 0, 0});
    
    ofBackground(255);
    
    blur.setup(ofGetWidth()*DesiredCamDistance/DefaultCamDistance, ofGetHeight()*DesiredCamDistance/DefaultCamDistance);
    blur.setBlurStrength(1.f);

    texts.setup();
    texts.addText("ARLEQUINO", "Ubuntu-R.ttf", 380);
    texts.addText("DEBUT EP\nOUT NOW", "Ubuntu-R.ttf", 450);
    texts.addText("WWW.ARLEQUINO.BAND", "Ubuntu-R.ttf", 200);

    cam.setDistance(DesiredCamDistance);
}

//--------------------------------------------------------------
void ofApp::update(){
    music.update();
    agents.update(music.getLevel());
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    agents.draw();
    texts.draw();
    poster.draw();
    ofPopStyle();
    cam.end();
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 't'){
        texts.cycleText();
        textRovingAgentSource.setLetterPaths(texts.getLetterPaths(), texts.getDrawPosition());
        agents.transitionAgents(textRovingAgentSource, 1.f);
        texts.animateIn();
    }else if (key == 's'){
        agents.transitionAgents(sphereRovingAgentSource, 1.f);
    }else if (key == 'p'){
        gridAgentSource.reset();
        agents.transitionAgents(gridAgentSource, 1.f);
    }else if (key == 'v'){
        agents.bringVisualisationsHome(1.f);
    }else if (key == 'a'){
        poster.animateIn();
    }
    
    if (key != 't'){
        texts.animateOutIfVisible();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
