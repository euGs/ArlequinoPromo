#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(Cols, Rows);
    visualisationSource.setup();
    sphereRovingAgentSource.setup();

    agents.setup(sphereRovingAgentSource, visualisationSource, MaxAgents);
    music.setup("ArTeaser_Edit04.wav");
    agentsShader.load("shaders_gl3/topLighting");
    shadowsShader.load("shaders_gl3/floorShadows");
    
    textRovingAgentSource.setup();
    gridAgentSource.setDimensions(Cols, Rows, visualisationSource.getColWidth(), visualisationSource.getRowHeight());
    
    poster.setup("Cover01.jpg");
    
//    blur.setup(ofGetWidth(), ofGetHeight());
//    blur.setBlurStrength(1.f);

    texts.setup();
    texts.addText("ARLEQUINO", "Ubuntu-R.ttf", 380);
    texts.addText("DEBUT EP\nOUT NOW", "Ubuntu-R.ttf", 450);
    texts.addText("WWW.ARLEQUINO.BAND", "Ubuntu-R.ttf", 200);

    cam.setPosition(0.f, 0.f, DesiredCamDistance);
    shadowCam.setPosition(0.f, -DesiredCamDistance, 0.f);
    shadowCam.setOrientation({90.f, 0.f, 0.f});
    shadowFbo.allocate(shadowWidth, shadowHeight, GL_RGBA);
    shadowPlane.set(shadowWidth, shadowHeight);
    shadowPlane.setPosition(shadowPosition);
    shadowPlane.setOrientation(shadowOrientation);
    shadowPlane.mapTexCoords(0, 0, shadowWidth, shadowHeight);
    
    ofBackground(255.f);
}

//--------------------------------------------------------------
void ofApp::update(){
    music.update();
    float visualScaling = music.getLevel() * 25.f;
    agents.update(visualScaling);
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Render agents into shadow FBO.
    shadowFbo.begin();
    ofClear(255.f, 0.f);
//    blur.begin();
    shadowCam.begin();
    shadowsShader.begin();
    shadowsShader.setUniform1f("alpha", 1);//ofMap(music.getLevel(), 0.f, 0.15f, 0.f, 1.f, true));
    agents.drawUntextured(ProportionOfAgentsInShadow);
    shadowsShader.end();
    shadowCam.end();
//    blur.end();
//    blur.draw(-ofGetWidth()/2, -ofGetHeight()/2);
    shadowFbo.end();
    
    cam.begin();

    // Draw agents.
    agentsShader.begin();
    agentsShader.setUniform1f("alpha", ofMap(music.getLevel(), 0.f, 0.15f, 0.f, 1.f, true));
    agentsShader.setUniform1f("toplightStartY", 800.f);
    agentsShader.setUniform1f("toplightIntensity", .45f);
    agentsShader.setUniform1f("topLightEndY", -800.f);
    agentsShader.setUniform1f("ambientLight", .8f);
    agents.draw();
    agentsShader.end();
    
    texts.draw();
    poster.draw();
    
    // Draw shadow.
    shadowFbo.getTexture().bind();
    shadowPlane.draw();
    shadowFbo.getTexture().unbind();
    
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
        agents.transitionAgents(textRovingAgentSource, 1.f);
        texts.animateIn();
    }else if (key == 's'){
        agents.transitionAgents(sphereRovingAgentSource, 1.f);
    }else if (key == 'p'){
        float posterDistanceFromCamera = poster.getWidth() / tan(ofDegToRad(cam.getFov()));

        ofVec3f posterPosition = cam.getPosition() + cam.getLookAtDir() * posterDistanceFromCamera;
        ofVec3f posterOrientationEuler = cam.getOrientationEuler();
        
        gridAgentSource.setPosition(posterPosition);
        gridAgentSource.setOrientationEuler(posterOrientationEuler);
        poster.setPosition(posterPosition);
        poster.setOrientation(posterOrientationEuler + ofVec3f(180.f, 0, 0));
        gridAgentSource.reset();

        agents.transitionAgents(gridAgentSource, 1.f);
    }else if (key == 'v'){
        agents.animateVisualisations(1.f, 0.f, 1.f);
    }else if (key == 'c'){
        agents.animateVisualisations(1.f, 1.f, 0.f);
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
