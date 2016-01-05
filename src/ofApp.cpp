#include "ofApp.h"
ofTrueTypeFont font;

//--------------------------------------------------------------
void ofApp::setup(){
    TornPaperVisualisationSource visualisationSource;
    sphereRovingAgentSource.setup();
    visualisationSource.setup();
    int maxAgents = 1000;

    agents.setup(sphereRovingAgentSource, visualisationSource, maxAgents);
    music.setup("ArTeaser_Edit04.wav");
    
    textRovingAgentSource.setup();
    
    ofBackground(255);
    
    blur = make_unique<RandomBlur>();
    blur->setup(ofGetWidth(), ofGetHeight());

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
    ofSetColor(126, 46, 23, 30);
    font.drawString("ARLEQUINO", 0.f, 0.f);
    ofPopStyle();
    cam.end();
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
