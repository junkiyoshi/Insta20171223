#include "Cleator.h"

Cleator::Cleator()
{
	this->location = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
	this->velocity = ofVec2f(0, 0);
	this->acceleration = ofVec2f(0, 0);

	this->max_speed = 10;
	this->max_force = 3;
	this->radius = 30;
	this->angle = ofRandom(360);
}

Cleator::~Cleator()
{

}

void Cleator::applyForce(ofVec2f force)
{
	this->acceleration += force;
}

void Cleator::seek(ofVec2f target)
{
	ofVec2f desired = this->location - target;
	float distance = desired.length();
	desired.normalize();
	if (distance < this->radius)
	{
		float m = ofMap(distance, 0, this->radius, 0, this->max_speed);
		desired *= m;
	}
	else
	{
		desired *= this->max_speed;
	}

	ofVec2f steer = this->velocity - desired;
	steer.limit(this->max_force);
	applyForce(steer);
}

void Cleator::update()
{
	this->future.set(this->velocity);
	this->future.normalize();
	this->future *= 60;
	this->future += this->location;

	this->angle = ofRandom(0, 360);
	float x = 60 * cos(this->angle * DEG_TO_RAD) + future.x;
	float y = 60 * sin(this->angle * DEG_TO_RAD) + future.y;
	this->target = ofVec2f(x, y);

	this->seek(this->target);

	this->velocity += this->acceleration;
	this->velocity.limit(max_speed);
	this->location += this->velocity;

	if (this->location.x < -ofGetWidth() / 2) {
		this->location.x = -ofGetWidth() / 2;
		this->velocity.x *= -1;
	}
	else if (this->location.x > ofGetWidth() / 2) {
		this->location.x = ofGetWidth() / 2;
		this->velocity.x *= -1;
	}

	if (this->location.y < -ofGetHeight() / 2) {
		this->location.y = -ofGetHeight() / 2;
		this->velocity.y *= -1;
	}
	else if (this->location.y > ofGetHeight() / 2) {
		this->location.y = ofGetHeight() / 2;
		this->velocity.y *= -1;
	}

	this->acceleration *= 0;
	this->velocity *= 0.98;

}

void Cleator::draw()
{

}

ofVec2f Cleator::get_location() {
	return this->location;
}

ofVec2f Cleator::get_velocity() {
	return this->velocity;
}