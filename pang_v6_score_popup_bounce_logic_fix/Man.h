#include "commonstuff.h"
#include "Shape.h"
#include "Bullet.h"

#ifndef __SHIP_H__
#define __SHIP_H__

class Man: public Shape {
 private:
  int status;
 public:
  Man();
  void draw();
  //void move();
  void strafe(float,float,float);
  Bullet* fire();
  float getSize();
  void resetpos();
};

#endif