#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetColor(111);
    ofSetLineWidth(60);
    
    int numAgents = 200;
    
    for (int i=0; i<numAgents; i++){
        unique_ptr<Agent> agent = make_unique<RovingAgentOnSphere>();
        agent->setup();
        agents.push_back(std::move(agent));
    }
    
    music.setup("ArTeaser_Edit02.wav");
}

//--------------------------------------------------------------
void ofApp::update(){
    music.update();

    float noiseScale = ofMap(mouseX, 0, ofGetWidth(), 0, 1.f);
    float noiseVel = ofGetElapsedTimef();
    float globalScaling = ofMap(mouseY, 0, ofGetHeight(), 1.f, 2.f);
    
    for (int i=0; i<agents.size(); i++){
        float noiseValue1 = ofNoise(i * noiseScale, 1 * noiseScale, noiseVel);
        float noiseValue2 = ofNoise(i * noiseScale, 1000 * noiseScale, noiseVel);
        agents[i]->update(noiseValue1, noiseValue2, .1f + music.getLevel() * 8.f);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    for (int i=0; i<agents.size(); i++){
        agents[i]->draw();
    }
    
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
