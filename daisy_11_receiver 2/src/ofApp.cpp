#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    daisyImage.loadImage("images/center80.png");
    petalImage.loadImage("images/plasticW.png");
    petalImageHovered.loadImage("images/plasticCloves.png");
    petalImageHovered2.loadImage("images/plasticCnot.png");
    followerImage.loadImage("images/daisy_mj_product.png");
    bEmit = false;
    BGimage.loadImage("images/blue_sky.jpg");
    bee.loadImage("images/bee_small.png");
    
    instructions.loadImage("images/instructions.png");
    end.loadImage("images/end.png");
 

    //--osc
    receiver.setup(PORT);
    
    // we changed to one bee
    
    for(int i=0; i<4; i++){
        mouseX[i] = -100;
        mouseY[i] = -100;
    }
    petal_Image_number_1 = 2;//added by Paul 10/21 -
    petal_Image_number_2 = 12;//added by Paul 10/21
    
    //--ARD
    ard.connect("/dev/tty.usbmodem1411", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino	= false;
    ardButtonPressed = false;
    ard.sendDigitalPinMode(13, ARD_OUTPUT);

    //---clean
    bClean= false;
    cleanerTimer = 0;
    bLovesMe_Selected = false;
    buttonTimer = ofGetElapsedTimeMillis() - 3000;
    bButton = true;
    
    //--sound
    soundPlayer.loadSound("final_daisy_sound.wav");
    soundPlayer.setVolume(0.75f);
    soundPlayer.setMultiPlay(false);
    soundPlayer.setLoop(false);
    
    //sound for background
    Spring.loadSound("spring_forest.wav");
    Spring.setVolume(0.30f);
    Spring.setMultiPlay(false);
    Spring.setLoop(true);
    Spring.play();
    
    //sound for emitter
    blow.loadSound("blow.wav");
    blow.setVolume(1.00f);
    blow.setMultiPlay(false);
    blow.setLoop(false);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
  
    //--ARD
    updateArduino();

    //--osc
    oscReceive();
    
    //--audio background
    ofSoundUpdate();
    
    instructions.draw(350,120);
    
  
    
    //--daisy
    if (!bLovesMe_Selected) {//comment this out and close bracket at end of if-statement
        
        for (int i=0; i<myFlws.size(); i++) {
            myFlws[i].resetForce();
        }
        
        for (int i=0; i<myFlws.size(); i++) {
            myFlws[i].addRepulsionForce(myFlws[i].pos.x, 0, 30, 1);
        }
        
        for (int i=0; i<myFlws.size(); i++) {
            if (bClean) {
                myFlws[i].bClean = true;
                myFlws[i].addAttractionForce(-100, ofGetHeight()/2, 3000, 0.5);
            }else{
                myFlws[i].bounceOffWalls();
            }
            myFlws[i].update();
            
            //clean
            ofRectangle window;
            window.set(-100, -100, ofGetWidth()+100, ofGetHeight()+100);
            
            for (int j=0; j<myFlws[i].myPetals.size(); j++) {
                if (!window.inside(myFlws[i].myPetals[j].pos)&& bClean) {
                    myFlws[i].myPetals.erase(myFlws[i].myPetals.begin()+j);
                }
            }
            
            if (myFlws[i].myPetals.size() == 0) {
                myFlws.erase(myFlws.begin()+i);
                
            }
        }
        
        for (int i=0; i<myFlwSmall.size(); i++) {
            myFlwSmall[i].resetForce();
            if (bClean) {
                myFlwSmall[i].addAttractionForce(-100, ofGetHeight()/2, 3000, 0.5);
            }else{
                myFlwSmall[i].bounceOffWalls();
            }
            myFlwSmall[i].addDampingForce();
            myFlwSmall[i].update();
            
            //clean
            ofRectangle window;
            window.set(-100, -100, ofGetWidth()+100, ofGetHeight()+100);
            if (!window.inside(myFlwSmall[i].pos) && bClean) {
                myFlwSmall.erase(myFlwSmall.begin()+i);
                
            }
        }
    }
    
  
    
    // bee touch loves me
    for (int i=0; i<myFlws.size(); i++) {
        for (int j=0; j<myFlws[i].myPetals.size(); j++) {
            if(  myFlws[i].myPetals[j].bSelected && myFlws[i].myPetals[j].bIsLovesMe && !bClean){
                
                bLovesMe_Selected =true;
                 ard.sendDigital(13,ARD_HIGH);
                 end.draw(350,120);
                 break;
            }
            
        }
    }
    
    //scale change
    for (int i=0; i<myFlws.size(); i++) {
        for(int j=0; j< myFlws[i].myPetals.size(); j++){
            myFlws[i].myPetals[j].scaleUpdate();
        }
    }
    
    
    
    if (bLovesMe_Selected) {
        for (int i=0; i<myFlws.size(); i++) {
            for (int j=0; j<myFlws[i].myPetals.size(); j++) {
                if(myFlws[i].myPetals[j].bSelected){
                    if (myFlws[i].myPetals[j].scalePct == 1) {
                        bClean =true;
                        bLovesMe_Selected = false;
                        (ard.sendDigital(13,ARD_LOW));
                        
//                        ofEnableAlphaBlending();
//                        for (int i=0; i<end.size(); i++)
//                        {
//                            end[i].draw();
//                        }
                        break;
                        
                        
                       
                    }
                    break;
                }
            }
        }
    }
    
    
    
    
    if (myFlws.size() == 0 && myFlwSmall.size() == 0) {
        bClean =false;
        cleanerTimer = 0;
    }
    
    if (ofGetElapsedTimeMillis() -  buttonTimer >= 3000) {
        bButton = true;
        bEmit = false;
        buttonTimer = ofGetElapsedTimeMillis();
    }
    
//  sound----------------
    updateSound();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    BGimage.draw(0,0, ofGetWidth(), ofGetHeight());
    
    instructions.draw(350,120);
    
    for (int i=0; i<myFlwSmall.size(); i++) {
        myFlwSmall[i].draw();
    }
    
    //---------------------------------------------------------
    
    //---petals which are not loves me
    for (int i=0; i<myFlws.size(); i++) {
        for (int j=0; j<myFlws[i].myPetals.size(); j++) {
            
            ofPushMatrix();
            ofTranslate(myFlws[i].pos);
            ofRotateZ(myFlws[i].angle*RAD_TO_DEG);
            ofSetColor(255);
            daisyImage.draw(-daisyImage.getWidth()/2, -daisyImage.getHeight()/2);
            ofPopMatrix();
            
            if (!myFlws[i].myPetals[j].bSelected) {
                myFlws[i].myPetals[j].draw();
            }
        }
        
    }

    
    //---petals which are loves me
    for (int i=0; i<myFlws.size(); i++) {
        for (int j=0; j<myFlws[i].myPetals.size(); j++) {
            if (myFlws[i].myPetals[j].bSelected) {
                myFlws[i].myPetals[j].draw();
            }
        }
    }
    
    
   //------------------------------------
    
    
    //--osc
    string buf;
	buf = "FPS: "+ ofToString(ofGetFrameRate())+"\nListening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
    
    for(int i=0; i<4; i++){
    	buf = "mouse: " + ofToString(mouseX[i], 4) +  " " + ofToString(mouseY[i], 4);
        ofDrawBitmapString(buf, 430, 20 + 20*i);
    }
    
    for (int i=0; i<4; i++) {
        bee.draw(mouseX[i], mouseY[i]);
    }
    
    // we changed to one bee
    
//    for (int i=0; i<4; i++) {
//        bee.draw(mouseX[i], mouseY[i]);
//    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ' ) {
        bEmit = true;
    }
    
    if (key == 'd') {
        bClean = !bClean;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    for (int i=0; i<myFlws.size(); i++) {
        myFlws[i].mouseMoved(x, y);
//        bee[i].mouseMoved(x,y);
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::cleaner(){
 
    myFlws.clear();
    myFlwSmall.clear();
   

}
//--------------------------------------------------------------
void ofApp::oscReceive(){
   
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
        
  if(m.getAddress() == "/mouse0/position"){
            // both the arguments are int32's
            mouseX[0] = m.getArgAsInt32(0);
            mouseY[0] = m.getArgAsInt32(1);
            mouseX[0] = ofMap(mouseX[0], 0, 640, 0, ofGetWidth());
            mouseY[0] = ofMap(mouseY[0], 0, 480, 0, ofGetHeight());
        } else 
        if(m.getAddress() == "/mouse1/position"){
            // both the arguments are int32's
            mouseX[1] = m.getArgAsInt32(0);
            mouseY[1] = m.getArgAsInt32(1);
            mouseX[1] = ofMap(mouseX[1], 0, 640, 0, ofGetWidth());
            mouseY[1] = ofMap(mouseY[1], 0, 480, 0, ofGetHeight());
        } else if(m.getAddress() == "/mouse2/position"){
            // both the arguments are int32's
            mouseX[2] = m.getArgAsInt32(0);
            mouseY[2] = m.getArgAsInt32(1);
            mouseX[2] = ofMap(mouseX[2], 0, 640, 0, ofGetWidth());
            mouseY[2] = ofMap(mouseY[2], 0, 480, 0, ofGetHeight());
        } else if(m.getAddress() == "/mouse3/position"){
            // both the arguments are int32's
            mouseX[3] = m.getArgAsInt32(0);
            mouseY[3] = m.getArgAsInt32(1);
            mouseX[3] = ofMap(mouseX[3], 0, 640, 0, ofGetWidth());
            mouseY[3] = ofMap(mouseY[3], 0, 480, 0, ofGetHeight());
        }
		
    }
    
    mouseX[0] = ofGetMouseX();
    mouseY[0] = ofGetMouseY();
    
 
    
}





//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
	ard.sendDigitalPinMode(2, ARD_INPUT);
    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    //ard.sendDigital(13,ARD_LOW);
	bSetupArduino = true;
  
    
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    
    
	// update the arduino, get any data or messages.
	ard.update();
   
    
    int buttonState = 0;
    if (bButton) {
        buttonState = ard.getDigital(2);
        
    }

    
    if(buttonState == true && ardButtonPressed == false){
        bButton = false;
        bLovesMe_Selected = false;
        
        cleaner();
        float velX = -4.5;
        
        blow.play();
        instructions.clear();
      
       
        
//            for (int i=0; i<255; i++)
//            {
//            ofEnableAlphaBlending();
//            instructions.draw(350,120);
//            ofDisableAlphaBlending();
//        
//            }
        
        
        
        for (int i=0; i< petal_Image_number_2; i++) {
            followerBig tempFlw;
            myFlws.push_back(tempFlw);
            myFlws.back().setInitialCondition( daisyImage, petalImage,petalImageHovered2,
                                              ofGetWidth()/2, ofGetHeight()-1,
                                              0, -ofRandom(4,7), false); //-- added by Paul 10/21 -- change these numbers for emitter thrust for amount of flowers
        }
        
        for (int i=0; i< petal_Image_number_1; i++) {//-- added by Paul 10/21 -- these for loops separate behavior of "lovesmenot" and "lovesme"
            
            followerBig tempFlw;
            myFlws.push_back(tempFlw);
            myFlws.back().setInitialCondition( daisyImage, petalImage,petalImageHovered,
                                              ofGetWidth()/2, ofGetHeight()-1,
                                              0, -ofRandom(4,7), true);
            
            
        }
        
      
        
        for (int i=0; i<25; i++) { //-- added by Paul 10/21 -- change these numbers for emitter thrust for amount of flowers
            followerSmall tempFlw;
            myFlwSmall.push_back(tempFlw);
            myFlwSmall.back().setInitialCondition(followerImage,
                                                  ofGetWidth()/2, ofGetHeight()-1,
                                                  0, -ofRandom(3,14));
            if(i%2 == 0){
                myFlwSmall.back().bFixed = true;
            }
        }

        ardButtonPressed   = true;
        
    } else if(buttonState == false){
       
        ardButtonPressed = false;
        
    }

    

}





//--------------------------------------------------------------
void ofApp::updateSound(){
    
    
    for (int i=0; i<myFlws.size(); i++) {
        for (int j=0; j<myFlws[i].myPetals.size(); j++) {
            if (myFlws[i].myPetals[j].bSoundPlay && myFlws[i].myPetals[j].bIsLovesMe) {
                if (!soundPlayer.getIsPlaying()) {
                    soundPlayer.play();
                    ard.sendDigital(13,ARD_HIGH);
                    
                    
                }else{
                    myFlws[i].myPetals[j].bSoundPlay = false;
                    
                    
                }
            }
        }
    }
    
    
}

