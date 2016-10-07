#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(Cols, Rows);
    visualisationSource.setup();
    sphereRovingAgentSource.setup();

    agents = make_shared<Agents>();
    agents->setup(sphereRovingAgentSource, visualisationSource, MaxAgents);
    agentsShader.load("shaders_gl3/topLighting");
    
    textRovingAgentSource.setup();
    basicBoundAgentSource.setup();
    gridAgentSource.setDimensions(Cols, Rows, visualisationSource.getColWidth(), visualisationSource.getRowHeight());
    simplerTextRovingAgentSource.setup();
    simplerTextRovingAgentSource.setMinimumPointDistance(10.f);
    
    poster.setup("Cover01.jpg");
    
    shadows.setup(agents, DesiredCamDistance);

    texts.setup();
    texts.addText("ARLEQUINO", "Ubuntu-R.ttf", 380, "DropShadow_ARLEQUINO.png", ofVec2f(1.09584664536741, 1.59405940594059));
    texts.addText("DEBUT EP\nOUT NOW", "Ubuntu-R.ttf", 450, "DropShadow_DEBUT.png", ofVec2f(1.0953516090584, 2.23529411764706));
    texts.addText("WWW.ARLEQUINO.BAND", "Ubuntu-R.ttf", 200, "DropShadow_URL.png", ofVec2f(1.05785920925747, 1.75));

    cam.setPosition(0.f, 0.f, DesiredCamDistance);
    
    ofHideCursor();
    
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
    ofPushStyle();
    ofSetColor(255, 255, 0);
    ofSetColor(0, 255, 255);
    ofPopStyle();

//    shadows.draw(ofMap(music.getLevel(), 0.f, 0.05f, 0.3f, 1.f, true));

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
    if (key == 'm'){
        music.setup("ArTeaser_Edit05.wav");
    }else if (key == 't'){
        texts.cycleText();
        textRovingAgentSource.setLetterPaths(texts.getLetterPaths(), texts.getDrawPosition());
        agents->transitionAgents(textRovingAgentSource, 1.f);
        texts.animateIn();
    }else if (key == 'r'){
        texts.cycleText();
        auto h = texts.getBoundingBox().getHeight()*.4f;
        simplerTextRovingAgentSource.setMinimumPointDistance(texts.getBoundingBox().getHeight()*.4f);
        simplerTextRovingAgentSource.setLetterPaths(texts.getLetterPaths(), texts.getDrawPosition());
        agents->transitionAgents(simplerTextRovingAgentSource, 1.f);
        texts.animateIn();
    }else if (key == 'b'){
        texts.cycleText();
        auto bb = texts.getBoundingBox();
        basicBoundAgentSource.setBoundingBox(bb);
        agents->transitionAgents(basicBoundAgentSource, 1.f);
        texts.animateIn();
    }else if (key == 's'){
        agents->transitionAgents(sphereRovingAgentSource, 1.f);
    }else if (key == 'p'){
        float posterDistanceFromCamera = poster.getWidth() / tan(ofDegToRad(cam.getFov()));
        
        // Bring poster right up to camera without a white border.
        posterDistanceFromCamera *= .84f;

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
    }
    
    if (key != 't' && key != 'b' && key != 'r'){
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
