#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	~Particle();
	void Upate(std::vector<std::unique_ptr<Particle>>& particles);
	void Draw();

	ofPoint next;
private:

	int size;
	int depth;

	ofPoint location;
	int direction_index;
	ofPoint directions[5];
};