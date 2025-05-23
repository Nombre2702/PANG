#include "Platform.h"
#include "GLstuff.h"

#include "Man.h"


extern int invulnTime;

Man::Man()
{
  pos[X] = 0;
  pos[Y] = -9;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 90;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = 0;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.2;
  color[G] = 0.4;
  color[B] = 0.3;

  acc_ratio = 0.0;
}

void Man::strafe(float rx, float ry, float rz)
{
   pos[X] += rx;  pos[Y] += ry;  pos[Z] += rz;

   // tspeed[X] = rx;
}

 Bullet* Man::fire()
 {
   Bullet *tmp;

   tmp = new Bullet(pos[X],pos[Y], 0.0f, 0.015*BULLETSPEED);

   return tmp;
 }


void Man::draw()
{

  predraw();

  if (invulnTime > 0) {
      // override al color amarillo
      glColor3f(1.0f, 1.0f, 0.0f);
  }
  else {
      glColor3f(1.0f, 1.0f, 1.0f);
  }

  // Draw Body	
  glTranslatef(0,0, 0);
  glutSolidSphere(0.5, 20, 20);
  
  // Draw Head
  glTranslatef(0.0f, 0.0f, -0.85f);
  glutSolidSphere(0.35f, 20, 20);
  
  // Draw Eyes
  glPushMatrix();
      glColor3f(0.0f, 1.0f, 0.5f);
      glTranslatef(0.1f, 0.46f, -0.15f);
      glutSolidSphere(0.05f, 10, 10);
      glTranslatef(-0.2f, 0.0f, 0.0f);
      glutSolidSphere(0.05f, 10, 10);
  glPopMatrix();
  
  // Draw Nose
  glColor3f(1.0f, 0.5f, 0.5f);
  glRotatef(-90,1,0,0);
  glutSolidCone(0.15f, 0.5f, 10, 2);
  
  postdraw(); 
}
  

float Man::getSize()
{
  return (0.25);
}

void Man::resetpos()
{
 pos[X] = 0;
  pos[Y] = -9;
  pos[Z] = 0;

  
  rot[Z] = 0;
  rot[X] = 90;
  rot[Y] = 0;

  rspeed[X] = 0;
  rspeed[Y] = 0;
  rspeed[Z] = 0;

  tspeed[X] = 0;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.2;
  color[G] = 0.4;
  color[B] = 0.3;
}