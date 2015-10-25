#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    unique_ptr<AgentSource> agentSource = make_unique<SphereRovingAgentSource>();
    unique_ptr<VisualisationSource> visualisationSource = make_unique<SphereVisualisationSource>();
    int maxAgents = 100;

    agents.setup(move(agentSource), move(visualisationSource), maxAgents);
    music.setup("ArTeaser_Edit04.wav");
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
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
