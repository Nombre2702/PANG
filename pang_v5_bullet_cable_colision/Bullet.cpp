#include "Platform.h"
#include "GLstuff.h"
#include <GL/glu.h>
#include "Bullet.h"

Bullet::Bullet(float px, float py, float vx, float vy)
{
	state = UP; //initial state
    status = true; //true means active

	anchorX = px;
	anchorY = py;

  pos[X] = px;
  pos[Y] = py;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = -90;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = vx;
  tspeed[Y] = vy;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.9;
  color[B] = 0.0;

    acc_ratio = 0.0;

}

void Bullet::move() {
    switch (state) {
    case INACTIVE:
        //do nothing
        return;

    case UP:
        //move up
        pos[X] += tspeed[X];
        pos[Y] += tspeed[Y];
		//high world limit change direction
        if (pos[Y] >= SIZEY2) {
            state = DOWN;
        }
        break;

    case DOWN:
        //move down
        pos[X] += tspeed[X];
        pos[Y] -= tspeed[Y];
		//down world limit delete bullet
        if (pos[Y] <= anchorY) {
            state = INACTIVE;
            status = false;
        }
        break;
    }
}

void Bullet::draw()
{
    //draw bullet
  predraw();
  glColor3f(0.2f, 0.2f, 0.2f);
  glutSolidCone(0.3,1.0,10,10);
  postdraw();

  //draw cable dynamically
  float length = pos[Y] - anchorY;
  if (length <= 0) return;

  // Dibuja un cilindro “levantado” desde el anclaje a lo largo de Y
  static GLUquadric* quad = nullptr;
  if (!quad) quad = gluNewQuadric();

  glPushMatrix();
  glDisable(GL_LIGHTING);
  glColor3f(0.2f, 0.2f, 0.2f);

  // Traslada al punto de anclaje
  glTranslatef(anchorX, anchorY, 0.0f);

  // Rota 90° para que el cilindro (que por defecto apunta a +Z) pase a apuntar en +Y:
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

  // Dibuja el cilindro: base y cima de radio 0.05 y altura = length
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluCylinder(quad, 0.05f, 0.05f, length, 12, 1);

  glEnable(GL_LIGHTING);
  glPopMatrix();
}


float Bullet::getSize()
{
  return (0.2);
}

bool Bullet::getStatus()
{
  return status;
}

void Bullet::setStatus(bool s)
{
  status = s;
}

Bullet::State Bullet::getState() {
    return state;
}

void Bullet::setState(Bullet::State s) {
    state = s;
}

float Bullet::getAnchorX() {
    return anchorX;
}

float Bullet::getAnchorY() {
    return anchorY;
}

float Bullet::getCableRadius() {
    return 0.05f;
}