#include "ofApp.h"
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) // this is the macro that defines constrain()

//--------------------------------------------------------------
void ofApp::setup(){
    
    fbo.allocate(MONITORWIDTH, MONITORHEIGHT, GL_RGBA);

    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    ofBackground(255);
    
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        ofxOscMessage inMessage;
        receiver.getNextMessage(inMessage);
        
        if(inMessage.getAddress() == "/vecPoints"){
            float xPoint = inMessage.getArgAsFloat(0);
            float yPoint = inMessage.getArgAsFloat(1);
            float zPoint = inMessage.getArgAsFloat(2);
            ofVec3f addPoint(xPoint, yPoint, zPoint);
            faceMesh.addVertex(addPoint);
            cout << "received x y z " << xPoint << yPoint << zPoint << endl;
        }
        
        if(inMessage.getAddress() == "/clearMsg"){
            if (inMessage.getArgAsBool(0) == true) faceMesh.clearVertices();
        }
        
    }
    
    fbo.begin();
    ofClear(255,255,255, 0); // writes over previous vertices so they don't leave trails forever when drawing
    easyCam.begin();
    drawReceivedPoints();
    
    easyCam.orbit(longitude, 0, radius);
    if (longitude > 70) longitudeAdder = -0.5;
    else if (longitude < -70) longitudeAdder = 0.5;
    
    longitude = longitude + longitudeAdder;
    
    easyCam.end();
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);
    
    ofSetBackgroundColor(0);
    
    // data will be drawn white on white; change font color to make visible
    ofSetColor(255,0,0);
    stringstream numReport;
    numReport << faceMesh.getNumVertices() << " vertices drawn";
    ofDrawBitmapString(numReport.str(), 10, 10);
    ofDrawBitmapString(longitude, 10, 20);
}

void ofApp::drawReceivedPoints(){
    
    glPointSize(8);

    ofScale(1, -1, -1); // the projected points are 'upside down' and 'backwards'
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    faceMesh.addColor(ofColor::red);
//    faceMesh.addColor(ofFloatColor(0.5,0,0,0.9)); // experimental
    faceMesh.drawVertices();
    ofDisableAlphaBlending();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '=':
            radius += 5;
            break;
            
        case '-':
            radius -= 5;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
