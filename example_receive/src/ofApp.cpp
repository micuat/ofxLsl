#include "ofApp.h"

using namespace lsl;

//--------------------------------------------------------------
void ofApp::setup() {
    auto inlet = LslInlet::addStream("type", "EEG", (function<void(LslInlet::InletPtr)>)[&](LslInlet::InletPtr inlet) {
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
    });

    buffers.resize(inlet->info().channel_count());
    for (auto& b : buffers) {
        b.resize(ofGetWidth());
    }
    curBuffer = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
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
