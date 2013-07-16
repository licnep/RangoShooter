#include "loader.h"
#include "3dHelperClasses.h"

float linearInterpolation(float start,float end, float percent) 
{
	return start+percent*(end-start);
}

void translateRotate(locRot r) {
	glTranslatef(r.x,r.y,r.z);
	glRotatef(r.x_rot,1.0,0.0,0.0);
	glRotatef(r.y_rot,0.0,1.0,0.0);
	glRotatef(r.z_rot,0.0,0.0,1.0);
}

void animation::setup(locRot end_locRot, int duration_milliseconds, std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now()) {
	this->end_locRot = end_locRot;
	this->start_time = start_time;
	//end_time = std::chrono::system_clock::now();
	this->end_time = start_time + std::chrono::milliseconds(duration_milliseconds);
	this->duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	finished = false;
}

locRot animation::getLocRot() {
	double tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count();
	if (tempo_trascorso<0) return locRot(); //ritorna 0,0,0... se l'animazione non e' ancora iniziata

	double percentage = tempo_trascorso/duration;
	if (percentage>=1) 
	{
		finished = true;
		return end_locRot;
	}
	//std::cout << "percent: " << percentage << std::endl;
	locRot lr;
	lr.x = linearInterpolation(0,end_locRot.x,percentage);
	lr.y = linearInterpolation(0,end_locRot.y,percentage);
	lr.z = linearInterpolation(0,end_locRot.z,percentage);
	lr.x_rot = linearInterpolation(0,end_locRot.x_rot,percentage);
	lr.y_rot = linearInterpolation(0,end_locRot.y_rot,percentage);
	lr.z_rot = linearInterpolation(0,end_locRot.z_rot,percentage);
	return lr;
}
