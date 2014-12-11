#include "petal.h"
#include "ofApp.h"

petal::petal(){
	damping = 0.005f; //-- added by Paul 10/21 damping may need to be adjusted with other changes -- also change in petal2.cpp if you change here
    gravity.set(0,0);
    rotateSpeed = 0;
    diff = ofRandom(-0.2, 0.2);
    bFly = false;
    bSelected = false;
    
}

//--------------------------------------------------------------
void petal::setup(ofImage &IMAGE, ofImage &ImageHovered,float x, float y, float Angle, bool NotTouch){
    
    image = &IMAGE;
    imageHovered = &ImageHovered;
    setInitialCondition(x, y, 0, 0);
    angle =  Angle*RAD_TO_DEG;
    isNotTouch = NotTouch;
    
    //sound K add
    
 
    
    //--ARD K add
    ard.connect("/dev/tty.usbmodem1411", 57600);
    ofAddListener(ard.EInitialized, this, &petal::setupArduino);
	bSetupArduino	= false;

    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    

    
    
}

//--------------------------------------------------------------
void petal::update(){
    
    //- sound
    ofSoundUpdate();
    //--ARD
    updateArduino();

    
    vel = vel + frc;
	pos = pos + vel;
    
    if (bFly) {
        angle +=  rotateSpeed * vel.length() * diff;
        for (int i=0; i<4; i++) {
            ofApp * app = (ofApp *)ofGetAppPtr();
            ofPoint mouse(app->mouseX[i],app->mouseY[i]);
            if (!isNotTouch) {
           if (mouse.distance(pos)<40) {
               
               //kasia add
               //can't get the sound to play once
               
               //adding arduino as receiver - same situation it keeps on turning on the fan
               ard.sendDigital(13, ARD_HIGH);

               
                    bSelected = true;
                    break;
                }else{
                    bSelected = false;
                    
                    //kasia add
                    ard.sendDigital(13, ARD_LOW);

                }
            }
        }
       
    }
    
}

//--------------------------------------------------------------
void petal::draw(){
    
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotateZ(angle);
    if (bSelected) {
        ofSetColor(255);
        imageHovered->draw( -image->getWidth()/2, -image->getHeight()/2);

    }else{
        ofSetColor(255);
        image->draw( -image->getWidth()/2, -image->getHeight()/2);

    }
    ofPopMatrix();

    
}

//--------------------------------------------------------------
void petal::setupArduino(const int & version) {
	
    
	ofRemoveListener(ard.EInitialized, this, &petal::setupArduino);
	//ard.sendDigitalPinMode(2, ARD_INPUT);
    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    
	bSetupArduino = true;
    
    
    
}

//--------------------------------------------------------------
void petal::updateArduino(){
    
    
	ard.update();
    
    
}
//------------------------------

void petal::keyPressed(int key){
    
}

//--------------------------------------------------------------
void petal::keyReleased(int key){
    
}

//--------------------------------------------------------------
void petal::mouseMoved(int x, int y ){
  
}

//--------------------------------------------------------------
void petal::mouseDragged(int x, int y, int petal){
    
}

//--------------------------------------------------------------
void petal::mousePressed(int x, int y, int petal){
    
}

//--------------------------------------------------------------
void petal::mouseReleased(int x, int y, int petal){
    
}
//--------------------------------------------------------------
void petal::resetForce(){
    
    frc.set(0,0);
}
//--------------------------------------------------------------
void petal::addForce(float x, float y){
    
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}
//--------------------------------------------------------------
void petal::addDampingForce(){
    
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
    
}
//--------------------------------------------------------------
void petal::setInitialCondition(float px, float py, float vx, float vy){
    
    pos.set(px,py);
	vel.set(vx,vy);
}
//--------------------------------------------------------------
void petal::addRepulsionForce(float x, float y, float radius, float scale){
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
    
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
    
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
    
    
}

//--------------------------------------------------------------
void petal::resetAngle(float Angle){
    
    angle =Angle*RAD_TO_DEG;
}
























