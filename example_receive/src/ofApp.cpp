#include "ofApp.h"

using namespace lsl;

float sample[8];

//--------------------------------------------------------------
void ofApp::setup(){
    // resolve the stream of interest & make an inlet to get data from the first result
    std::vector<stream_info> results = resolve_stream("type", "EEG");
    inlet = make_shared<stream_inlet>(results[0]);
}

//--------------------------------------------------------------
void ofApp::update(){
    // receive data & time stamps forever (not displaying them here)
    double ts = inlet->pull_sample(&sample[0], 8);
    ofLogError() << sample[0];
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
