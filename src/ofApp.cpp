#include "ofApp.h"
ofTrueTypeFont font;

/*
 Need
 1.____
 Get positions of text and poster right
 - Pull hardcoded text out of MeshRovingAgentSource and set it as text changes
 
 2.____
 Get camera movements looking good, either manual or scripted
 
 3.____
 Glitch, incl. just changing seeding on movements
 
 4.____
 Check speed of paper tears
 
 5.____
 Colorisation options
 
 n-2.___
 Try export to 3D
 
 n-2.___
 Try import to Blender and render there
 
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
 leading to a normalised value (in Agents class), it might ease the load a bit. Flapping
 could also be binary-state/basic animation, i.e. only have 2 frames.
 
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

    font.load("Ubuntu-R.ttf", 250, true, false, true);
    setText("ARLEQUINO");
    isDrawingText = false;
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
    if (isDrawingText){
        drawText();
    }
    cam.end();
    
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::setText(string text){
    this->text = text;
    auto boundingBox = font.getStringBoundingBox(text, 0.f, 0.f);
    textDrawPosition.x = -(boundingBox.width)/2.f;
    textDrawPosition.y = -(boundingBox.height)/2.f;
}

//--------------------------------------------------------------
void ofApp::drawText(){
    ofPushStyle();
    ofSetColor(126, 46, 23, 200);
//    blur.begin();
    font.drawString(text, textDrawPosition.x, textDrawPosition.y);
    ofNoFill();
//    blur.end();
//    blur.draw(0, 0);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    isDrawingText = false;
    
    if (key == 't'){
        agents.transitionAgents(textRovingAgentSource, 1.f);
        isDrawingText = true;
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
