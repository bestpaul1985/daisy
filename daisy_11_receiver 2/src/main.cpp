#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(768/4*3,1024/4*3,OF_WINDOW);
    ofSetupOpenGL(1024,683, OF_FULLSCREEN);			// <-------- setup the GL context

   // <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
