#pragma once
#include "ofMain.h"

class Cleator
{
public:
	Cleator();
	~Cleator();

	void applyForce(ofVec2f force);
	void seek(ofVec2f target);

	void update();
	void draw();

	ofVec2f get_location();
	ofVec2f get_velocity();

private:
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
	ofVec2f future;
	ofVec2f target;
	float max_speed;
	float max_force;
	float radius;
	float angle;
};