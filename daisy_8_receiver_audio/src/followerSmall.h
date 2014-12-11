#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class followerSmall
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        followerSmall();
		virtual ~followerSmall(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		
		void addRepulsionForce(followerSmall &p, float radius, float scale);
		void addAttractionForce(followerSmall &p, float radius, float scale);
		void addClockwiseForce(followerSmall &p, float radius, float scale);
		void addCounterClockwiseForce(followerSmall &p, float radius, float scale);
	
		void addDampingForce();
        
		void setInitialCondition(ofImage &IMG, float px, float py, float vx, float vy);
        void update();
        void draw();
	
		void bounceOffWalls();
		float damping;
    
    ofImage *img;
    float scale;
    float angleSpeed;
    float angle;
    bool bFixed;
    bool isAlive;
    bool isFirstBuncing;
    protected:
    private:
};

#endif // PARTICLE_H
