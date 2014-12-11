#pragma once

#include "ofMain.h"
#include "followerBig.h"
#include "followerSmall.h"

#define PORT 12345
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void oscReceive();
        void cleaner();
        void setupArduino(const int & version);
        void updateArduino();
        void updateSound();
		
    ofImage             daisyImage;
    ofImage             petalImage;
    ofImage             followerImage;
    ofImage             petalImageHovered;
        ofImage             petalImageHovered2;
    ofImage             BGimage;
    vector<followerBig> myFlws;
    vector<followerSmall> myFlwSmall;

    
    int                 flwCounter;
    bool                bEmit;
    
    int                 petal_Image_number_1, petal_Image_number_2;//added by Paul 10/21 - petal_Image_number 2 is now "lovesmenot", petal_Image_number 1 is "loves me"
    
    //--osc
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    int mouseX[4], mouseY[4];
    
    ofImage bee;
    
    //--ard
    ofArduino	ard;
    bool		bSetupArduino;
    bool        ardButtonPressed;
    
    //sound
    ofSoundPlayer  whisper;
    
    //clean
    bool bClean;
};
