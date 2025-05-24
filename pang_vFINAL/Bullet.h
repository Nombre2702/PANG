#include "commonstuff.h"
#include "Shape.h"

#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet: public Shape {
 public:
	enum State { INACTIVE, UP, DOWN };
	Bullet(float, float, float,float);
	void move() override;
	void draw();
	float getSize();
	bool getStatus();
	void setStatus(bool);
	State getState();
	void setState(State);
	float getAnchorX();
	float getAnchorY();
	float getCableRadius();
private:
	State state;
	int status;
	float  anchorX;
	float  anchorY;
};

#endif