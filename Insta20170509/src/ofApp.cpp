#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (ofxBulletBox* tmp : this->obs) { delete tmp; }
	this->obs.clear();

	for (ofxBulletBox* tmp : this->boxes) { delete tmp; }
	this->boxes.clear();
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofEnableDepthTest();
	ofBackground(255);
	ofSetWindowTitle("box shot!");

	this->world.setup();
	this->world.setGravity(ofVec3f(0.0, -1024.0, 0));

	ofxBulletBox* obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(0, -ofGetHeight() / 2, -512), 0.0f, 1024, 64, 1024);
	obstacle->setProperties(0.8, 0.5);
	obstacle->add();
	this->obs.push_back(obstacle);

	obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(ofGetWidth() / 2, 0, -512), 0.0f, 64, 1024, 1024);
	obstacle->setProperties(0.8, 0.5);
	obstacle->add();
	this->obs.push_back(obstacle);

	obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(-ofGetWidth() / 2, 0, -512), 0.0f, 64, 1024, 1024);
	obstacle->setProperties(0.8, 0.5);
	obstacle->add();
	this->obs.push_back(obstacle);

	obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(0, 0, -1024), 0.0f, 1024, 1024, 64);
	obstacle->setProperties(0.8, 0.5);
	obstacle->add();
	this->obs.push_back(obstacle);

	obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(0, ofGetHeight() / 2, -512), 0.0f, 1024, 64, 1024);
	obstacle->setProperties(0.8, 0.5);
	obstacle->add();
	this->obs.push_back(obstacle);

	obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(0, 0, cam.getPosition().z), 0.0f, 1024, 1024, 64);
	obstacle->setProperties(0.8, 0.5);
	obstacle->add();
	this->obs.push_back(obstacle);

	for (int i = 0; i < 512; i++) {
		ofxBulletBox* box = new ofxBulletBox();
		float size = ofRandom(20.0, 30.0);
		box->create(this->world.world, ofVec3f(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2), ofRandom(-512, 512), ofRandom(-1000, size)), 1.0, size, size, size);
		box->setRestitution(1.0);
		box->add();

		this->boxes.push_back(box);

		ofColor color;
		color.setHsb(ofRandom(255), 255, 255);
		this->box_colors.push_back(color);
	}

	this->light.setPosition(ofVec3f(0, 0, 512));

}

//--------------------------------------------------------------
void ofApp::update() {
	this->world.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();

	ofEnableLighting();
	this->light.enable();

	for (int i = 0; i < this->obs.size() - 1; i++) {
		ofSetColor(128);
		this->obs[i]->draw();
	}

	for (int i = 0; i < this->boxes.size(); i++) {
		ofSetColor(this->box_colors[i]);
		this->boxes[i]->draw();
	}

	Leap::Frame frame = leap.frame();
	Leap::HandList hands = frame.hands();
	for (int i = 0; i < hands.count(); i++) {
		float r = 0;
		float g = 0;
		float b = ofMap(hands[i].pinchStrength(), 0, 1, 0.0f, 255.0f);

		ofSetColor(r, g, b, 255);

		this->drawHand(hands[i]);

		if (hands[i].isRight() && hands[i].grabStrength() > 0.7) {
			for (auto& box : this->boxes) {
				box->applyCentralForce(ofVec3f(hands[i].palmVelocity().x, hands[i].palmVelocity().y, hands[i].palmVelocity().z) * 8);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::drawHand(Leap::Hand hand) {
	Leap::FingerList fingers = hand.fingers();
	for (int j = 0; j < fingers.count(); j++) {
		this->drawFinger(fingers[j]);
	}

	ofPushMatrix();
	ofVec3f palm_point = ofVec3f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 3, hand.palmPosition().z);
	ofTranslate(palm_point);
	ofSphere(10);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFinger(Leap::Finger finger) {

	ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 3, finger.tipPosition().z);
	ofPushMatrix();
	ofTranslate(tip_point);
	ofSphere(5);
	ofPopMatrix();

	ofVec3f base_point = ofVec3f(tip_point.x + finger.direction().x * finger.length(),// * -1,
		tip_point.y + finger.direction().y * finger.length() - 1,
		tip_point.z + finger.direction().z * finger.length() - 1);
	ofPushMatrix();
	ofTranslate(base_point);
	ofSphere(5);
	ofPopMatrix();

	ofLine(tip_point, base_point);
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