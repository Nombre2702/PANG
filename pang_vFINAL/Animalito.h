#pragma once

#include "commonstuff.h"
#include "Shape.h"

class Animalito : public Shape {
	private:
		float speed;
		int animalito_spawned; //counter for spawned Animalitos
	public:
		Animalito(float start_x, float start_y, float speed);
		~Animalito();
		void move() override;
		void draw();
		float getSize();
		float operator+(Shape* s);
};