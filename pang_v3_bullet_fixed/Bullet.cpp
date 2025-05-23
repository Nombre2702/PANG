#include "Platform.h"
#include "GLstuff.h"

#include "Bullet.h"

Bullet::Bullet(float px, float py, float vx, float vy)
{
	status = true; //true means active

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
	pos[X] += tspeed[X];
	pos[Y] += tspeed[Y];

    //disappear when out of bounds
    if (pos[X] < -SIZEX2 || pos[X] > SIZEX2 || pos[Y] < -SIZEY2 || pos[Y] > SIZEY2)
    {
        //delete this bullet flag
        status = false;
    }
}

void Bullet::draw()
{
  predraw();
  glutSolidCone(0.3,1.0,10,10);	
  postdraw();
}


float Bullet::getSize()
{
  return (0.2);
}

bool Bullet::getStatus()
{
  return status;
}

bool Bullet::setStatus(bool s)
{
  status = s;
  return status;
}