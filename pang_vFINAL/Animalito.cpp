#include "Platform.h"
#include "GLstuff.h"

#include "Animalito.h"

Animalito::Animalito(float start_x, float start_y, float spd) {
	//constructor

	//position initialization
	pos[X] = start_x;
	pos[Y] = start_y;
	pos[Z] = 0.0f;

	//speed initialization
	speed = spd;

	//color initialization
	color[R] = RAND_FRAC();
	color[G] = RAND_FRAC();
	color[B] = RAND_FRAC();

}

Animalito::~Animalito() {
	//destructor
}

void Animalito::move() {

	//move horizontally
	pos[X] += speed;

	//wrap around screen
	if (pos[X] > SIZEX2) pos[X] = -SIZEX2;
	if (pos[X] < -SIZEX2) pos[X] = SIZEX2;
}

void Animalito::draw() {
	//draw the animalito
    predraw();  // set up transforms/color/material from Animalito/Shape

    // Body (soft sky-blue)
    glColor3f(0.4f, 0.7f, 1.0f);
    glutSolidSphere(0.2f, 16, 16);

    // Head (same color, just smaller and forward)
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.15f);
    glColor3f(0.4f, 0.7f, 1.0f);
    glutSolidSphere(0.12f, 12, 12);
    glPopMatrix();

    // Beak (bright orange)
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.27f);
    glRotatef(90, 1, 0, 0);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidCone(0.05f, 0.15f, 12, 4);
    glPopMatrix();

    // Wings (darker steel-blue)
    glColor3f(0.2f, 0.4f, 0.8f);
    // Left wing
    glPushMatrix();
    glTranslatef(-0.22f, 0.0f, 0.0f);
    glScalef(0.1f, 0.02f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Right wing
    glPushMatrix();
    glTranslatef(+0.22f, 0.0f, 0.0f);
    glScalef(0.1f, 0.02f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tail (same steel-blue)
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, -0.2f);
    glRotatef(30, 1, 0, 0);
    glScalef(0.1f, 0.02f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    postdraw(); // restore state
}

float Animalito::getSize() {
	//return the size of the animalito
	return 0.4f;
}

float Animalito::operator+(Shape* s) {

	float myPos[3], otherPos[3];
	this->getPos(myPos);
	s->getPos(otherPos);

	return mydistance(myPos[X], myPos[Y], otherPos[X], otherPos[Y]);
}