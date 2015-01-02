#pragma once

#include "ofMain.h"



class petal {
    
public:
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
    float damping;
    
    petal();
    
    void setup(ofImage &IMAGE,ofImage &ImageHovered, float x, float y, float Angle, bool NotTouch);
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
    ofImage *imageHovered;
    
    int ImageHovered;
    
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
    
    ofSoundPlayer  whisper;
    bool playOnce; 

    
};
