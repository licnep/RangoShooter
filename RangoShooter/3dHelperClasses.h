#include "loader.h"

#pragma once
#include <chrono>
#include <list>

class locRot 
{
public:
	locRot(float x,float y,float z,float x_rot, float y_rot,float z_rot) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->x_rot = x_rot;
		this->y_rot = y_rot;
		this->z_rot = z_rot;
	}
	locRot operator+(locRot d) {
		locRot l;
		l.x = x+d.x;
		l.y = y+d.y;
		l.z = z+d.z;
		l.x_rot = x_rot+d.x_rot;
		l.y_rot = y_rot+d.y_rot;
		l.z_rot = z_rot+d.z_rot;
		return l;
	}
	locRot operator+=(locRot d) {
		x = x+d.x;
		y = y+d.y;
		z = z+d.z;
		x_rot = x_rot+d.x_rot;
		y_rot = y_rot+d.y_rot;
		z_rot = z_rot+d.z_rot;
		return *this;
	}
	//costruttore vuoto, inizializza tutto a 0
	locRot():x(0),y(0),z(0),x_rot(0),y_rot(0),z_rot(0) {}
	float x,y,z;
	float x_rot,y_rot,z_rot;
};

//does a glTranslate e glRotate
void translateRotate(locRot r);

float linearInterpolation(float start,float end, float percent);

class animation {
public:
	animation() {}
	animation(locRot end_locRot, int duration_milliseconds, std::chrono::time_point<std::chrono::system_clock> start_time) {
		this->setup(end_locRot, duration_milliseconds, start_time);
	}
	void setup(locRot end_locRot, int duration_milliseconds, std::chrono::time_point<std::chrono::system_clock> start_time);
	locRot getLocRot();

	std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
	double duration;
	locRot end_locRot;
	bool finished;
};

class Object3D {
public: 
	Object3D():locrot(0,0,0,0,0,0){}
	void pushAnimation(animation a) {
		animations.push_front(a);
	}
	locRot getLocRot() {
		locRot l = locrot;
		for (auto i = animations.begin(); i!=animations.end();) {
			l += i->getLocRot();
			if (i->finished) {
				locrot+=i->getLocRot(); //freeze the end position of the animation in our locrot
				animations.erase(i++); //remove the animation
			} else {
				i++;
			}
		}
		return l;
	}
	void setLocRot(locRot r) {
		locrot = r;
	}
	void applyGlMatrixTransformations()
	{
		locRot l = this->getLocRot(); //update con le eventuali animazioni
		glRotatef(l.x_rot,1.0f,0.0f,1.0f);
		glRotatef(l.y_rot,0.0f,1.0f,0.0f);
		glRotatef(l.z_rot,0.0f,0.0f,1.0f);
		glTranslatef(l.x, l.y, l.z);
	}
private:
	std::list<animation> animations;
	locRot locrot;
};