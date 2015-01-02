#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    daisyImage.loadImage("images/center90.png");
    petalImage.loadImage("images/plasticW.png");
  //petalImageHovered.loadImage("images/petal1cLovesMeNot.png");
      //petalImageHovered2.loadImage("images/petal0cLovesMe.png");
    petalImageHovered.loadImage("images/plasticCloves.png");
    petalImageHovered2.loadImage("images/plasticCnot.png");

       //petalImageHovered.loadImage("images/petal01.png");
    followerImage.loadImage("images/daisy_mj_product.png");
    bEmit = false;
    
    BGimage.loadImage("images/sky1280.jpg");

    
  
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
   
    for (int i=0; i<myFlws.size(); i++) {
        myFlws[i].resetForce();
    }
    
    for (int i=0; i<myFlws.size(); i++) {
        myFlws[i].addRepulsionForce(myFlws[i].pos.x, 0, 30, 1);
        
    }
    
    for (int i=0; i<myFlws.size(); i++) {
        myFlws[i].bounceOffWalls();
        myFlws[i].update();
    }
    
    
    for (int i=0; i<myFlwSmall.size(); i++) {
        myFlwSmall[i].resetForce();
        myFlwSmall[i].bounceOffWalls();
        myFlwSmall[i].addDampingForce();
        myFlwSmall[i].update();
    }
    
    if (bEmit) {
        float velX = -4.5;
        for (int i=0; i< 4; i++) {
           
            followerBig tempFlw;
            myFlws.push_back(tempFlw);
            myFlws.back().setInitialCondition( daisyImage, petalImage,petalImageHovered,
                                              ofGetWidth()/2, ofGetHeight()-1,
                                              0, -ofRandom(4,7));
            
            myFlws.back().setInitialCondition( daisyImage, petalImage,petalImageHovered2,
                                              ofGetWidth()/2, ofGetHeight()-1,
                                              0, -ofRandom(4,7));

        }

        for (int i=0; i<40; i++) {
            
            followerSmall tempFlw;
            myFlwSmall.push_back(tempFlw);
            myFlwSmall.back().setInitialCondition(followerImage,
                                                  ofGetWidth()/2, ofGetHeight()-1,
                                                  0, -ofRandom(3,14));
            if(i%2 == 0){
                myFlwSmall.back().bFixed = true;
            }
        }
        
        bEmit = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    BGimage.draw(0,0, ofGetWidth(), ofGetHeight());                                        
    //imageHovered->draw( -image->getWidth()/2, -image->getHeight()/2);

    

    
    for (int i=0; i<myFlwSmall.size(); i++) {
        myFlwSmall[i].draw();
    }
    
    for (int i=0; i<myFlws.size(); i++) {
        myFlws[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ' ) {
        bEmit = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    for (int i=0; i<myFlws.size(); i++) {
        myFlws[i].mouseMoved(x, y);
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
