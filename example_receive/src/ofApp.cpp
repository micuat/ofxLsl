#include "ofApp.h"

// example based on
// https://github.com/sccn/labstreaminglayer/blob/master/LSL/liblsl/examples/C%2B%2B/ReceiveDataSimple/ReceiveDataSimple.cpp

using namespace lsl;

//--------------------------------------------------------------
void ofApp::setup() {
    // resolve the stream of interest & make an inlet to get data from the first result
    std::vector<stream_info> results = resolve_stream("type", "EEG");
    inlet = make_shared<stream_inlet>(results[0]);
    buffers.resize(inlet->info().channel_count());
    for (auto& b : buffers) {
        b.resize(ofGetWidth());
    }
    curBuffer = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    try {
        // receive data
        vector<vector<double> > chunk;
        inlet->pull_chunk(chunk);

        for (auto& c : chunk) {
            int count = 0;
            for (auto& buffer : buffers) {
                buffer.at(curBuffer) = c.at(count);
                count++;
            }
            curBuffer = (curBuffer + 1) % buffers.at(0).size();
        }
    }
    catch (std::exception &e) {
        cerr << "Got an exception: " << e.what() << endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);

    ofTranslate(0, ofGetHeight() * 0.5f);
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(255, 128);

    for (auto& buffer : buffers) {
        ofBeginShape();
        int count = 0;
        for (auto& b : buffer) {
            ofVertex(count, ofMap(b, -1000, 1000, 100, -100));
            count++;
        }
        ofEndShape();
    }
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
