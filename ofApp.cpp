#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (int i = this->particles.size() - 1; i > -1; i--) {
		delete this->particles[i];
		this->particles.erase(this->particles.begin() + i);
	}

	for (int i = this->cleators.size() - 1; i > -1; i--) {
		delete this->cleators[i];
		this->cleators.erase(this->cleators.begin() + i);
	}
}


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	for (int i = 0; i < 3; i++) {
		this->cleators.push_back(new Cleator());
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor body_color;
	for (int i = 0; i < this->cleators.size(); i++) {

		ofVec2f location = this->cleators[i]->get_location();
		ofVec2f velocity = this->cleators[i]->get_velocity();

		if (velocity.length() > 5) {
			body_color.setHsb((ofGetFrameNum() + i * 90) % 255, 255, 255);
			this->particles.push_back(new Particle(location, velocity * 0.3, body_color));
		}
	}
	
	if (ofGetMousePressed()) {
		ofVec2f location = ofVec2f(ofGetMouseX() - ofGetWidth() / 2, ofGetMouseY() - ofGetHeight() / 2);
		ofVec2f prev_location = ofVec2f(ofGetPreviousMouseX() - ofGetWidth() / 2, ofGetPreviousMouseY() - ofGetHeight() / 2);
		ofVec2f velocity = prev_location - location;

		if (velocity.length() > 5) {
			body_color.setHsb(ofRandom(255), 255, 255);
			this->particles.push_back(new Particle(location, velocity * 0.3, body_color));
		}
	}

	for (int i = this->particles.size() - 1; i > -1; i--) {
		this->particles[i]->update();

		if (this->particles[i]->isDead()) {
			delete this->particles[i];
			this->particles.erase(this->particles.begin() + i);
		}
	}

	for (int i = 0; i < this->cleators.size(); i++) {
		this->cleators[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	float distance;
	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->draw();
		for (int j = i; j < this->particles.size(); j++) {
			distance = this->particles[i]->get_location().distance(this->particles[j]->get_location());
			if (distance < 100) {
				ofDrawLine(this->particles[i]->get_location(), this->particles[j]->get_location());
			}
		}
	}

	for (int i = 0; i < this->cleators.size(); i++) {
		this->cleators[i]->draw();
	}
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(1080, 1080, OF_WINDOW);
	ofRunApp(new ofApp());
}