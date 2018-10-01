#include "Particle.h"

Particle::Particle() {

	this->size = 40;
	this->depth = ofGetWidth() > ofGetHeight() ? ofGetWidth() : ofGetHeight();

	int x = (int)(ofRandom(ofGetWidth()) / this->size) * this->size;
	int y = (int)(ofRandom(ofGetHeight()) / this->size) * this->size;
	this->location = ofPoint(x, y);

	this->directions[0] = ofPoint(1, 0);
	this->directions[1] = ofPoint(-1, 0);
	this->directions[2] = ofPoint(0, 1);
	this->directions[3] = ofPoint(0, -1);
	this->directions[4] = ofPoint(0, 0);
}

Particle::~Particle() {

}

void Particle::Upate(std::vector<std::unique_ptr<Particle>>& particles) {

	if (ofGetFrameNum() % this->size == 0) {

		int try_count = 0;
		int r = ofRandom(4);
		while (try_count < 4) {

			this->direction_index = (r + try_count) % 4;

			if (this->location.x < 0) { this->direction_index = 0; }
			else if (this->location.x > ofGetWidth()) { this->direction_index = 1; }

			if (this->location.y < 0) { this->direction_index = 2; }
			else if (this->location.y > ofGetHeight()) { this->direction_index = 3; }

			this->next = this->location + this->directions[this->direction_index] * this->size;

			bool overlap = false;
			for (std::unique_ptr<Particle>& particle : particles) {

				if (this != particle.get()) {

					if (this->next == particle->next) {

						overlap = true;
						break;
					}
				}
			}

			if (overlap == false) { break; }
			try_count++;
		}

		if (try_count == 4) { this->direction_index = 4; }
	}
	else if (ofGetFrameNum() % this->size == 1) {

		this->next = ofPoint();
	}

	this->location += this->directions[this->direction_index];
}

void Particle::Draw() {

	ofPushMatrix();
	ofTranslate(this->location - ofPoint(ofGetWidth() * 0.5, ofGetHeight() * 0.5));

	switch (this->direction_index)
	{
	case 0:
		ofRotateY(ofMap(ofGetFrameNum() % this->size, 0, this->size - 1, 0, 90));
		break;
	case 1:
		ofRotateY(ofMap(ofGetFrameNum() % this->size, 0, this->size - 1, 0, -90));
		break;
	case 2:
		ofRotateX(ofMap(ofGetFrameNum() % this->size, 0, this->size - 1, 0, -90));
		break;
	case 3:
		ofRotateX(ofMap(ofGetFrameNum() % this->size, 0, this->size - 1, 0, 90));
		break;
	default:
		break;
	}

	ofDrawBox(this->size);

	ofPopMatrix();
}