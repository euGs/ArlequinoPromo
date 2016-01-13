#include "ofApp.h"
ofTrueTypeFont font;

/*
 Need
 n.____
 Get particles back in
 
 Extras
 
 1.____
 Wind effects: Have the paper respond to wind. The strength and direction of the wind
 is driven by noise. Each tear would then need to respond to both wind and music, 
 which probably means a force-based system (which is difficult, because the response
 to music isn't so).
 
 2.____
 Flapping paper tears, like birds. First try didn't work. Killed frame rate. But I 
 had timing values/calculations in each of the 100 tears. With only one calculation
 leading to a normalised value (in Agents class), it might ease the load a bit.
 
 3.____
 Add easing to transitions
 
 Nicer
 
 1.____
 
 Use time literals for animations: 1s or 1.s whatever C++14 will allow
 
 2.____
 Make it explicit that transitions are non-interruptable. Interrupting one now will
 result in a null pointer exception.
 
 */

//--------------------------------------------------------------
void ofApp::setup(){
    int cols = 20;
    int rows = 15;
    
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(cols, rows);
    visualisationSource.setup();
    sphereRovingAgentSource.setup();
    int maxAgents = 1000;

    agents.setup(sphereRovingAgentSource, visualisationSource, maxAgents);
    music.setup("ArTeaser_Edit04.wav");
    
    textRovingAgentSource.setup();
    gridAgentSource.setDimensions(cols, rows, visualisationSource.getColWidth(), visualisationSource.getRowHeight());
    gridAgentSource.setup();
    
    ofBackground(255);
    
    blur.setup(ofGetWidth(), ofGetHeight());
    blur.setBlurStrength(1.f);

    font.load("Ubuntu-R.ttf", 600, true, false, true);
    cam.setDistance(1500);
}

//--------------------------------------------------------------
void ofApp::update(){
    music.update();
    agents.update(music.getLevel());
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    agents.draw();
    ofPushStyle();
    ofSetColor(126, 46, 23, 200);
    blur.begin();
    font.drawString("ARLEQUINO", 0.f, 0.f);
    blur.end();
    ofPopStyle();
    blur.draw(0, 0);
    cam.end();
    
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
        agents.transitionAgents(textRovingAgentSource, 1);
    }else if (key == 's'){
        agents.transitionAgents(sphereRovingAgentSource, 1);
    }else if (key == 'p'){
        gridAgentSource.reset();
        agents.transitionAgents(gridAgentSource, 1);
    }else if (key == 'v'){
        agents.bringVisualisationsHome(5.f);
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
