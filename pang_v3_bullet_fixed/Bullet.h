#include "commonstuff.h"
#include "Shape.h"

#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet: public Shape {
 private:
  int status;
 public:
  Bullet(float, float, float,float);
  void move() override;
  void draw();
  float getSize();
  bool getStatus();
  bool setStatus(bool);
};

#endif