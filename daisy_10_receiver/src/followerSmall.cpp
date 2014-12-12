#include "followerSmall.h"
#include "ofMain.h"

//------------------------------------------------------------
followerSmall::followerSmall(){
	damping = 0.001f;
    scale = ofRandom(0.2,0.8);
    angle = ofRandom(0,360);
    angleSpeed = ofRandom(-0.2,0.2);
    bFixed = false;
    isAlive = true;
    isFirstBuncing = true;

}

//------------------------------------------------------------
void followerSmall::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void followerSmall::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void followerSmall::addRepulsionForce(float x, float y, float radius, float scale){
    
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
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void followerSmall::addAttractionForce(float x, float y, float radius, float scale){
    
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

//------------------------------------------------------------
void followerSmall::addRepulsionForce(followerSmall &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this followerSmall p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
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
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void followerSmall::addAttractionForce(followerSmall & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this followerSmall p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
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
		p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
	
}

//------------------------------------------------------------
void followerSmall::addClockwiseForce(followerSmall &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this followerSmall p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
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
		frc.x = frc.x - diff.y * scale * pct;
        frc.y = frc.y + diff.x * scale * pct;
		p.frc.x = p.frc.x + diff.y * scale * pct;
        p.frc.y = p.frc.y - diff.x * scale * pct;
    }
}

//------------------------------------------------------------
void followerSmall::addCounterClockwiseForce(followerSmall &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this followerSmall p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
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
		frc.x = frc.x + diff.y * scale * pct;
        frc.y = frc.y - diff.x * scale * pct;
		p.frc.x = p.frc.x - diff.y * scale * pct;
        p.frc.y = p.frc.y + diff.x * scale * pct;
		
    }
}


//------------------------------------------------------------
void followerSmall::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void followerSmall::setInitialCondition(ofImage &IMG,float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);

    img = &IMG;
}

//------------------------------------------------------------
void followerSmall::update(){	
	vel = vel + frc;
	pos = pos + vel;
    angle += angleSpeed;
}

//------------------------------------------------------------
void followerSmall::draw(){
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(angle);
    ofScale(scale,scale);
    img->draw(-img->getWidth()/2, -img->getHeight()/2);
    ofPopMatrix();
}


//------------------------------------------------------------
void followerSmall::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
    if (bFixed) {
        if (pos.x > maxx){
            pos.x = maxx; // move to the edge, (important!)
            vel.x *= -1;
            bDidICollide = true;
        } else if (pos.x < minx){
            pos.x = minx; // move to the edge, (important!)
            vel.x *= -1;
            bDidICollide = true;
        }
        
        if (pos.y > maxy){
            pos.y = maxy; // move to the edge, (important!)
            vel.y *= -1;
            bDidICollide = true;
        } else if (pos.y < miny){
            pos.y = miny; // move to the edge, (important!)
            vel.y *= -1;
            bDidICollide = true;
            if(isFirstBuncing){
                vel.x = ofRandom(-20,20);
            }
        }
        
        
        if (bDidICollide == true && bDampedOnCollision == true && isFirstBuncing){
            vel *= 0.3;
            isFirstBuncing = false;
        }
       
    }else{
        
        if (pos.x > maxx){
            isAlive = false;
            
        } else if (pos.x < minx){
            isAlive = false;

        }
        
        if (pos.y > maxy){
            isAlive = false;

        } else if (pos.y < miny){
            pos.y = miny; // move to the edge, (important!)
            vel.y *= -1;
            vel.x = ofRandom(-20,20);
            bDidICollide = true;
        }
        
        if (bDidICollide == true && bDampedOnCollision == true){
            vel *= 0.3;
        }
    }
		
}
