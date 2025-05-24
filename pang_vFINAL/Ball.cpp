#include "Platform.h"
#include "GLstuff.h"

#include <typeinfo>

#include "Ball.h"

// Forward declarations
class Man;
class Bullet;


Ball::Ball(int t)
{
  float tmp;

  size = BIG;
  type = t;

  pos[X] = RAND_DOM(0,SIZEX);
  pos[Y] = RAND_DOM(0,SIZEY);
  pos[Z] = 0;

  tmp = 2*(RAND_FRAC()-0.5);
  tspeed[X] = tmp*BALL_SPEED;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.0;
  color[B] = 0.0;

  acc_ratio = 0.0005;

  //  printf("Mi no is %d",mynumber);
}


Ball::Ball(int t, int s, float px, float py)
{
  float tmp;

  size = s;
  type = t;

  pos[X] = px;
  pos[Y] = py;
  pos[Z] = 0;

  tmp = 2*(RAND_FRAC()-0.5);
  tspeed[X] = tmp*BALL_SPEED;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  if(size==BIG)
    {
      color[R] = 0.9;
      color[G] = 0.0;
      color[B] = 0.0;
    }
  
  if(size==MEDIUM)
    {
      color[R] = 0.9;
      color[G] = 0.5;
      color[B] = 0.0;
    }
  
  if(size==SMALL)
    {
      color[R] = 0.9;
      color[G] = 0.9;
      color[B] = 0.0;
    }

 
    acc_ratio = 0.0005;

}


void Ball::draw()
{
  predraw();
  glutSolidSphere(size*0.3,9,8);

  // printf("Drawing ball %gm %g\n",pos[X],pos[Y]);
  
  postdraw();
}

 
//  parte la bola en 2 (crea una nueva y reduce el tamaño de la existente)
Ball *Ball::split()
{
  Ball *tmp;

  tmp = new Ball(1,size-1,pos[X],pos[Y]);
  size--;


  //update ball calour on split
  if (size == BIG) {
      color[R] = 0.9f;  color[G] = 0.0f;  color[B] = 0.0f;
  }
  else if (size == MEDIUM) {
      color[R] = 0.9f;  color[G] = 0.5f;  color[B] = 0.0f;
  }
  else if (size == SMALL) {
      color[R] = 0.9f;  color[G] = 0.9f;  color[B] = 0.0f;
  }

  return tmp;
}

 
float Ball::getSize()
{
  return (0.3*size);
}

void Ball::reposition()
{
    pos[X] = (rand() % int(SIZEX * 10) - int(SIZEX * 5)) / 10.0f;
    pos[Y] = (rand() % int(SIZEY * 10) - int(SIZEY * 5)) / 10.0f;
    pos[Z] = 0;

}

float Ball::operator+(Shape* s) 
{

  float myPos[3], otherPos[3];
  this->getPos(myPos);
  s->getPos(otherPos);

  return mydistance(myPos[X], myPos[Y], otherPos[X], otherPos[Y]);
}
