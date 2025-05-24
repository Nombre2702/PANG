#include "Platform.h"
#include "GLstuff.h"

#include "Shape.h"

Shape::Shape()
{
  mynumber = RAND_DOM(0,1000000);
  // TBD: check mynumber is not repeated
}

void  Shape::getPos(float *p)
{
  p[X] = pos[X];
  p[Y] = pos[Y];
  p[Z] = pos[Z];
}


int Shape::getNo()
{
  return mynumber;
}

void Shape::predraw()
{
  glPushMatrix();
  glTranslatef(pos[X],pos[Y],pos[Z]);
  glRotatef(rot[X],1,0,0);
  glRotatef(rot[Y],0,1,0);
  glRotatef(rot[Z],0,0,1);

  glColor3f(color[R],color[G],color[B]);
}

void Shape::postdraw()
{
  glPopMatrix();
}

void Shape::move()
{
  pos[X] += 0.3*tspeed[X];
  pos[Y] += tspeed[Y];
  pos[Z] += tspeed[Z];

  // updates speed
  tspeed[Y] += 0.00035*GRAV*acc_ratio;
  
  // check world boundaries
  if (pos[X] <= -SIZEX2) { 
	  pos[X] = -SIZEX2; 
	  tspeed[X] = -0.5 * tspeed[X];
  }

  if (pos[Y] <= -SIZEY2) { 
	  pos[Y] = -SIZEY2; 
	  float random_speed = 0.25 * BALL_SPEED * (RAND_FRAC() + 0.2);
	  if (random_speed < 0.007) {
		  tspeed[Y] = 0.007;
	  }
	  else if (random_speed > 0.025) {
		  tspeed[Y] = 0.025;
	  }
	  else {
		  tspeed[Y] = random_speed;
	  }

	  if (tspeed[X] < 0.015 && tspeed[X] > -0.015) {
		  if (tspeed[X] > 0) {
			  tspeed[X] = RAND_FRAC() * BALL_SPEED * 0.15;
		  }
		  else {
			  tspeed[X] = (- 1.0)* RAND_FRAC()* BALL_SPEED * 0.15;
		  }
	  }
  }
  
  if(pos[X]>=SIZEX2) {
	  pos[X] = SIZEX2; 
	  tspeed[X] = -0.5 * tspeed[X];
  }
  if(pos[Y]>=SIZEY2) {
	  pos[Y] = SIZEY2; 
	  tspeed[Y] = -0.0125*BALL_SPEED;
  }
  
}
