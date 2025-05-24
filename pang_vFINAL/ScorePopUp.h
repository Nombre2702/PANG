#pragma once

#include "commonstuff.h"
#include "Shape.h"

class ScorePopUp : public Shape
{
public:
	ScorePopUp(float x, float y, int score);
	void move() override;
	void draw();
	float getSize();
private:
	int value;
	int life;
	bool isAlive;
};