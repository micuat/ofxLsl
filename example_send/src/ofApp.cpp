#include "ofApp.h"

// example based on
// https://github.com/sccn/labstreaminglayer/blob/master/LSL/liblsl/examples/C%2B%2B/SendDataSimple/SendDataSimple.cpp

using namespace lsl;

//--------------------------------------------------------------
void ofApp::setup() {
    sample.resize(8);
    LslOutlet::addStream(make_shared<stream_info>("SimpleStream", "EEG", sample.size()), sample);
}

//--------------------------------------------------------------
void ofApp::update() {
    // generate random data
    for (int c = 0; c < sample.size(); c++)
        sample.at(c) = (rand() % 1500) - 750;
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
