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
    orgScale = 1;
    scalePct = 0;
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
    
  
    
    
}

//--------------------------------------------------------------
void petal::draw(){
    
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotateZ(angle);
    ofScale(scale, scale);
    if (bSelected) {
        ofSetColor(255);
        imageHovered->draw(-50,-40, 100, 80);//put in exact number (100,100)

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
void petal::addAttractionForce(float x, float y, float radius, float scale){
    
    // ----------- (1) make a vector of where this position is:
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

//--------------------------------------------------------------
void petal::resetAngle(float Angle){
    
    angle =Angle*RAD_TO_DEG;
}




//--------------------------------------------------------------
void petal::scaleUpdate(){

    float endScale, speed;
    endScale = 3.5;//how big petal grows
    speed = 0.005;//how fast petal increases
    
    if (bSelected && bIsLovesMe) {
        scalePct+=speed;
        if(scalePct>1){
            scalePct = 1;
        }
        float temPct;
        temPct = powf(scalePct, 0.7);
        scale = (1-temPct)*orgScale + temPct*endScale;
    }
    
    
}




















