#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.setSize(800, 600);
    
    ofCreateWindow(settings);
    ofSetFullscreen(true);
    
	ofRunApp(new ofApp());
}
