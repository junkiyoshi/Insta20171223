#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	Particle(ofVec2f location, ofVec2f velocity, ofColor body_color);
	~Particle();

	void update();
	void draw();

	ofVec2f get_location();
	bool isDead();
private:
	ofVec2f location;
	ofVec2f velocity;

	float	body_size;
	ofColor body_color;
	int		alpha;
};