#include "ofApp.h"

/*
 Need
 -----
 Correct dimensions for HD video
 
 Cycle through the final text
 
 Text + sphere agents
 
 Fade single-texture poster over "constructed" poster
 
 Get camera movements looking good, either manual or scripted
 
 Glitch, incl. just changing seeding on movements
 
 Check speed of paper tears (also on text)
 
 Colorisation options
 
 Try export to 3D
 
 Try import to Blender and render there
 
 Get particles back in
 
 Extras
 -----
 
 Wind effects: Have the paper respond to wind. The strength and direction of the wind
 is driven by noise. Each tear would then need to respond to both wind and music, 
 which probably means a force-based system (which is difficult, because the response
 to music isn't so).
 
 Flapping paper tears, like birds. First try didn't work. Killed frame rate. But I
 had timing values/calculations in each of the 100 tears. With only one calculation
 leading to a normalised value (in Agents class), it might ease the load a bit. Flapping
 could also be binary-state/basic animation, i.e. only have 2 frames.
 
 Add easing to transitions
 
 Nicer
 ----
 
 Use time literals for animations: 1s or 1.s whatever C++14 will allow
 
 Make it explicit that transitions are non-interruptable. Interrupting one now will
 result in a null pointer exception.
 
 Have state on Animator instead of bool - reads better
 
 */

//--------------------------------------------------------------
void ofApp::setup(){
    const int Cols = 40;
    const int Rows = 30;
    const int MaxAgents = 1000;
    const float DesiredCamDistance = 1500;
    const float DefaultCamDistance = 650;
    const int FontSize = 250;
    
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(Cols, Rows);
    visualisationSource.setup();
    sphereRovingAgentSource.setup();

    agents.setup(sphereRovingAgentSource, visualisationSource, MaxAgents);
    music.setup("ArTeaser_Edit04.wav");
    
    textRovingAgentSource.setup();
    gridAgentSource.setDimensions(Cols, Rows, visualisationSource.getColWidth(), visualisationSource.getRowHeight());
    gridAgentSource.setup();
    
    ofBackground(255);
    
    blur.setup(ofGetWidth()*DesiredCamDistance/DefaultCamDistance, ofGetHeight()*DesiredCamDistance/DefaultCamDistance);
    blur.setBlurStrength(1.f);

    font.load("Ubuntu-R.ttf", FontSize, true, false, true);
    textAnimator.setup(0.f, 200.f, 1.f);
    texts = { "ARLEQUINO", "DEBUT EP\nOUT NOW", "WWW.ARLEQUINO.BAND" };
    textIt = texts.cend();
    
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
    agents.draw();
    if (!textAnimator.getIsOut()){
        drawText();
    }
    cam.end();
    
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::cycleText(){
    if (textIt == texts.cend()){
        textIt = texts.cbegin();
    } else {
        textIt++;
    }

    auto boundingBox = font.getStringBoundingBox(*textIt, 0.f, 0.f);
    textDrawPosition.x = -(boundingBox.width)/2.f;
    textDrawPosition.y = -(boundingBox.height)/2.f;

    auto numExtraLines = std::count(textIt->cbegin(), textIt->cend(), '\n');
    textDrawPosition.y += (boundingBox.height * numExtraLines / 2.f);

    textRovingAgentSource.setLetterPaths(font.getStringAsPoints(*textIt, false), textDrawPosition);
}

//--------------------------------------------------------------
void ofApp::drawText(){
    ofPushStyle();
    ofSetColor(126, 46, 23, textAnimator.getValue());
//    blur.begin();
    font.drawString(*textIt, textDrawPosition.x, textDrawPosition.y);
    ofNoFill();
//    blur.end();
//    blur.draw(-ofGetWidth()*1500/650/2.f, -ofGetHeight()*1500/650/2.f);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (!textAnimator.getIsOut()){
        textAnimator.animate(Animator::Direction::Out);
    }
    
    if (key == 't'){
        cycleText();
        agents.transitionAgents(textRovingAgentSource, 1.f);
        textAnimator.animate(Animator::Direction::In);
    }else if (key == 's'){
        agents.transitionAgents(sphereRovingAgentSource, 1.f);
    }else if (key == 'p'){
        gridAgentSource.reset();
        agents.transitionAgents(gridAgentSource, 1.f);
    }else if (key == 'v'){
        agents.bringVisualisationsHome(1.f);
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
