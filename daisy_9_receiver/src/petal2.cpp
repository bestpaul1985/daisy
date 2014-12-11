//
//  petal2.cpp
//  daisy_prototype_5
//
//  Created by Witek, Kasia on 9/23/14.
//
//

#include "petal2.h"


petal2::petal2(){
	damping = 0.005f;
    gravity.set(0,0);
    rotateSpeed = 0;
    diff = ofRandom(-0.2, 0.2);
    bFly = false;
    bSelected = false;
}

//--------------------------------------------------------------
void petal2::setup(ofImage &IMAGE, ofImage &ImageHovered2,float x, float y, float Angle, bool NotTouch){
    
    image = &IMAGE;
    imageHovered2 = &ImageHovered2;
    setInitialCondition(x, y, 0, 0);
    angle =  Angle*RAD_TO_DEG;
    isNotTouch = NotTouch;
    
    
}

//--------------------------------------------------------------
void petal2::update(){
    
    vel = vel + frc;
	pos = pos + vel;
    
    if (bFly) {
        angle +=  rotateSpeed * vel.length() * diff;
        
        ofPoint mouse(ofGetMouseX(),ofGetMouseY());
        
        if (!isNotTouch) {
            if (mouse.distance(pos)<40) {
                bSelected = true;
            }else{
                bSelected = false;
            }
        }
        
    }
    
}

//--------------------------------------------------------------
void petal2::draw(){
    
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotateZ(angle);
    if (bSelected) {
        ofSetColor(255);
        imageHovered2->draw( -image->getWidth()/2, -image->getHeight()/2);
        
    }else{
        ofSetColor(255);
        image->draw( -image->getWidth()/2, -image->getHeight()/2);
        
    }
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void petal2::keyPressed(int key){
    
}

//--------------------------------------------------------------
void petal2::keyReleased(int key){
    
}

//--------------------------------------------------------------
void petal2::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void petal2::mouseDragged(int x, int y, int petal){
    
}

//--------------------------------------------------------------
void petal2::mousePressed(int x, int y, int petal){
    
}

//--------------------------------------------------------------
void petal2::mouseReleased(int x, int y, int petal){
    
}
//--------------------------------------------------------------
void petal2::resetForce(){
    
    frc.set(0,0);
}
//--------------------------------------------------------------
void petal2::addForce(float x, float y){
    
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}
//--------------------------------------------------------------
void petal2::addDampingForce(){
    
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
    
}
//--------------------------------------------------------------
void petal2::setInitialCondition(float px, float py, float vx, float vy){
    
    pos.set(px,py);
	vel.set(vx,vy);
}
//--------------------------------------------------------------
void petal2::addRepulsionForce(float x, float y, float radius, float scale){
	
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
void petal2::resetAngle(float Angle){
    
    angle =Angle*RAD_TO_DEG;
}
























