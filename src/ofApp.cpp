#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(Cols, Rows);
    visualisationSource.setup();
    sphereRovingAgentSource.setup();

    agents = make_shared<Agents>();
    agents->setup(sphereRovingAgentSource, visualisationSource, MaxAgents);
    music.setup("ArTeaser_LoudTest.wav");
    agentsShader.load("shaders_gl3/topLighting");
    
    textRovingAgentSource.setup();
    gridAgentSource.setDimensions(Cols, Rows, visualisationSource.getColWidth(), visualisationSource.getRowHeight());
    
    poster.setup("Cover01.jpg");
    
    shadows.setup(agents, DesiredCamDistance);

    texts.setup();
    texts.addText("ARLEQUINO", "Ubuntu-R.ttf", 380);
    texts.addText("DEBUT EP\nOUT NOW", "Ubuntu-R.ttf", 450);
    texts.addText("WWW.ARLEQUINO.BAND", "Ubuntu-R.ttf", 200);

    cam.setPosition(0.f, 0.f, DesiredCamDistance);
    
    ofBackground(255.f);
}

//--------------------------------------------------------------
void ofApp::update(){
    music.update();
    float visualScaling = music.getLevel() * 25.f;
    agents->update(visualScaling);
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    // Draw agents.
    agentsShader.begin();
    agentsShader.setUniform1f("alpha", ofMap(music.getLevel(), 0.f, 0.15f, 0.f, .4f, true));
    agentsShader.setUniform1f("toplightStartY", 800.f);
    agentsShader.setUniform1f("toplightIntensity", .45f);
    agentsShader.setUniform1f("topLightEndY", -800.f);
    agentsShader.setUniform1f("ambientLight", .8f);
    agents->draw();
    agentsShader.end();
    
    texts.draw();
    poster.draw();

    shadows.draw(ofMap(music.getLevel(), 0.f, 0.05f, 0.3f, 1.f, true));

    cam.end();

    // Draw debug.
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofDrawBitmapString(ofGetMouseX(), 20, 40);
    ofDrawBitmapString(ofGetMouseY(), 20, 60);
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
        agents->transitionAgents(textRovingAgentSource, 1.f);
        texts.animateIn();
    }else if (key == 's'){
        agents->transitionAgents(sphereRovingAgentSource, 1.f);
    }else if (key == 'p'){
        float posterDistanceFromCamera = poster.getWidth() / tan(ofDegToRad(cam.getFov()));

        ofVec3f posterPosition = cam.getPosition() + cam.getLookAtDir() * posterDistanceFromCamera;
        ofVec3f posterOrientationEuler = cam.getOrientationEuler();
        
        gridAgentSource.setPosition(posterPosition);
        gridAgentSource.setOrientationEuler(posterOrientationEuler);
        poster.setPosition(posterPosition);
        poster.setOrientation(posterOrientationEuler + ofVec3f(180.f, 0, 0));
        gridAgentSource.reset();

        agents->transitionAgents(gridAgentSource, 1.f);
    }else if (key == 'v'){
        agents->animateVisualisations(1.f, 0.f, 1.f);
    }else if (key == 'c'){
        agents->animateVisualisations(1.f, 1.f, 0.f);
    }else if (key == 'i'){
        poster.animate(Animator::Direction::In);
    }else if (key == 'o'){
        poster.animate(Animator::Direction::Out);
    }else if (key == 'u'){
        cam.startRotateUp();
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
