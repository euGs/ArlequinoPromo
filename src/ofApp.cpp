#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    unique_ptr<AgentSource> agentSource = make_unique<SphereRovingAgentSource>();
    unique_ptr<VisualisationSource> visualisationSource = make_unique<SphereVisualisationSource>();
    int maxAgents = 10;

    agents.setup(move(agentSource), move(visualisationSource), maxAgents);
    music.setup("ArTeaser_Edit03.wav");
}

//--------------------------------------------------------------
void ofApp::update(){
    music.update();

    agents.update(music.getLevel());
}

//--------------------------------------------------------------
void ofApp::draw(){
    agents.draw();
}

//--------------------------------------------------------------
//void ofApp::setup(){
//    ofSetColor(111);
//    ofSetLineWidth(60);
//    
//    loadTears();
//    
////    int numAgents = 200;
//    
//    
//    
////    while (geometry.areMoreElements()){
////        unique_ptr<Agent> agent = make_unique<RovingTearOnSphere>();
////        agent->setup();
////        
////        agents.push_back(move(agent));
////    }
//    
//    music.setup("ArTeaser_Edit03.wav");
//}
//
////--------------------------------------------------------------
//void ofApp::loadTears(){
//    int rows = 10;
//    int cols = 10;
//    
//    for (int x=0; x<cols; x++){
//        for (int y=0; y<rows; y++){
//            ofPlanePrimitive tear;
//            tear.set(80, 60, 2, 2);
//            
//            ofImage image;
//            image.load("section_" + to_string(x) + "_" + to_string(y) + ".png");
//            tear.mapTexCoords(0, 0, image.getWidth(), image.getHeight());
//            tear.setPosition((x-cols/2.f) * image.getWidth(), (y-rows/2.f) * image.getHeight(), 0);
//            
//            unique_ptr<RovingTearOnSphere> agent = make_unique<RovingTearOnSphere>();
//            agent->setTear(tear);
//            agent->setTexture(image);
//            agent->setup();
//            
//            agents.push_back(move(agent));
//        }
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::update(){
//    music.update();
//
//    float noiseScale = ofMap(mouseX, 0, ofGetWidth(), 0, 1.f);
//    float noiseVel = ofGetElapsedTimef();
//    float globalScaling = ofMap(mouseY, 0, ofGetHeight(), 1.f, 2.f);
//    
//    for (int i=0; i<agents.size(); i++){
//        float noiseValue1 = ofNoise(i * noiseScale, 1 * noiseScale, noiseVel);
//        float noiseValue2 = ofNoise(i * noiseScale, 1000 * noiseScale, noiseVel);
//        agents[i]->update(noiseValue1, noiseValue2, .1f + music.getLevel() * 8.f);
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//    cam.begin();
//    for (int i=0; i<agents.size(); i++){
//        agents[i]->draw();
//    }
//    
//    cam.end();
//}

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
