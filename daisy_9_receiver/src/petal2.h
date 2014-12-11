//
//  petal2.h
//  daisy_prototype_5
//
//  Created by Witek, Kasia on 9/23/14.
//
//

#ifndef daisy_prototype_5_petal2_h
#define daisy_prototype_5_petal2_h

#include "ofMain.h"

class petal2 {
    
public:
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
    float damping;
    
    petal2();
    
    void setup(ofImage &IMAGE,ofImage &ImageHovered2, float x, float y, float Angle, bool NotTouch);
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void resetForce();
    void addForce(float x, float y);
    void addDampingForce();
    void setInitialCondition(float px, float py, float vx, float vy);
    void addRepulsionForce(float x, float y, float radius, float scale);
    
    void resetAngle(float Angle);
    
    
    ofImage *image;
    ofImage *imageHovered2;
    float angle;
    float rotateSpeed;
    ofPoint repulsionPos;
    float repulsionRadius;
    float repulsionScale;
    ofPoint gravity;
    float diff;
    bool bFly;
    bool bSelected;
    bool isNotTouch;
    
};


#endif
