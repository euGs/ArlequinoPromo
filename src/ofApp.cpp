#include "ofApp.h"
ofTrueTypeFont font;

/*
 Preliminary
 1.____
 ***** In the middle of this, then doing GridAgentSource (with same dimensions
 passed to TPVizSrc) - I have my changes stashed but was getting crashes so have
 been working back to the stashed version from the previous commit. Keep doing
 this and diffing with the stashed version.
 TPVizSrc shouldn't have the image filename internally. Get it out, also
 because ofApp needs to know the dimensions of the image. And ofApp should
 be the one to pass it in. Refactor.
 
 Need
 1.____
 
 AnimatedTornPaperVisualisation (or similar name), that is capable of
 animating between crumpled paper and flat paper. Why? This is how each
 tear will animate back into the flat poster.
 
 OR
 
 Just do the same for the visualisation as for the agent. Make a lerping
 visualisation. Need to take into account VisualisationSource::hasMoreVisualisations
 in case you're lerping using a VisualisationSource that's already been used.
 I.E. you need to reset the VisualisationSource and consider whether to stop
 using unique_ptr's for visualisations all over the place. Otherwise we'll
 be into VisualisationSourceSource territory.
 
 2.____
 
 StaticAgent
 
 n.____
 Get particles back in
 
 Extras
 
 1.____
 
 Animated torn paper visualisation: so the mesh itself keeps distorting. This could
 replace the lerping visualisation if it can be in different states: animate randomly
 vs animate to original (flat). But how would ofApp call in to this? Something like
 visualisation->revertToOriginal would work fine but that means you have this method
 in the abstract base class when it's an animation-specific concept. You can move the
 responsibility of telling visualisations specific animation stuff to do, to the Agents
 class but should Agents be aware of animation stuff when it's really a visualisation
 concept? Isn't it more a case that the user is manually controlling the switching of
 Agent's and Visualisation's and that switching should somehow also control mesh
 animations?
 
 I'm thinking...there is only one type of Visualisation, it's nice that the code is
 SOLID and everything but I've got a promo video to release here. Time to get priorities
 straight. This is what we need:
 ofApp::keyReleased
 ...agents.transitionsAgents(Static...
 agents.completeVisualisations/restoreVisualisations
 
 Nicer
 
 1.____
 
 Use time literals for animations: 1s or 1.s whatever C++14 will allow
 
 */

//--------------------------------------------------------------
void ofApp::setup(){
    TornPaperVisualisationSource visualisationSource;
    sphereRovingAgentSource.setup();
    visualisationSource.setImageFilename("Cover01.jpg");
    visualisationSource.setGridDimensions(20, 15);
    visualisationSource.setup();
    int maxAgents = 1000;

    agents.setup(sphereRovingAgentSource, visualisationSource, maxAgents);
//    music.setup("ArTeaser_Edit04.wav");
    
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
