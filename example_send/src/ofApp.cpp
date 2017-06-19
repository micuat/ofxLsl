#include "ofApp.h"

// example based on
// https://github.com/sccn/labstreaminglayer/blob/master/LSL/liblsl/examples/C%2B%2B/SendDataSimple/SendDataSimple.cpp

using namespace lsl;

//--------------------------------------------------------------
void ofApp::setup() {
    info = make_shared<stream_info>("SimpleStream", "EEG", 8);
    outlet = make_shared<stream_outlet>(*info);
}

//--------------------------------------------------------------
void ofApp::update() {
    float sample[8];
    // generate random data
    for (int c = 0; c < 8; c++)
        sample[c] = (rand() % 1500) - 750;
    // send it
    outlet->push_sample(sample);
}

//--------------------------------------------------------------
void ofApp::draw() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
