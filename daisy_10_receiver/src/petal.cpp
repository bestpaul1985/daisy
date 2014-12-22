#include "petal.h"
#include "ofApp.h"

petal::petal(){
	damping = 0.005f; //-- added by Paul 10/21 damping may need to be adjusted with other changes -- also change in petal2.cpp if you change here
    gravity.set(0,0);
    rotateSpeed = 0;
    diff = ofRandom(-0.2, 0.2);
    bFly = false;
    bSelected = false;
    bIsLovesMe = false;
    bSoundPlay = false;
    scale = 1;
}

//--------------------------------------------------------------
void petal::setup(ofImage &IMAGE, ofImage &ImageHovered,float x, float y, float Angle, bool NotTouch, bool isLovesMe){
    
    image = &IMAGE;
    imageHovered = &ImageHovered;
    setInitialCondition(x, y, 0, 0);
    angle =  Angle*RAD_TO_DEG;
    isNotTouch = NotTouch;
    bIsLovesMe = isLovesMe;
    
}

//--------------------------------------------------------------
void petal::update(){
    
    vel = vel + frc;
    pos = pos + vel;
    
    
    if (bFly) {
        angle +=  rotateSpeed * vel.length() * diff;
        for (int i=0; i<4; i++) {
            ofApp * app = (ofApp *)ofGetAppPtr();
            ofPoint mouse(app->mouseX[i],app->mouseY[i]);
            if (!isNotTouch) {
           if (mouse.distance(pos)<60) {//40
                    bSelected = true;
                    bSoundPlay = true;
                    break;
                }else{
                    bSelected = false;
                }
            }
        }
    }
    
    if (bSelected && bIsLovesMe) {
        if (scale<4.5) {//2
            scale +=.04;//0.01
        }
    }
    
    if (!bSelected &&bIsLovesMe) {
        if (scale>1) {
            scale -= 0.010;
        }
    }
    
    
    
}

//--------------------------------------------------------------
void petal::draw(){
    
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotateZ(angle);
    ofScale(scale, scale);
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
























