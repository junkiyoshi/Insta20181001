#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofEnableDepthTest();

	for (int i = 0; i < 50; i++) { 
		
		std::unique_ptr<Particle> particle(new Particle());
		this->particles.push_back(std::move(particle));
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	for (std::unique_ptr<Particle>& particle : this->particles)	{ particle->Upate(this->particles); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (std::unique_ptr<Particle>& particle : this->particles) { particle->Draw(); }

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}