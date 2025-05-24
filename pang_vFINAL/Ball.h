#include "commonstuff.h"
#include "Shape.h"

#ifndef __BALL_H__
#define __BALL_H__

class Ball:public Shape {
 private:
  int size;
  int type;
  float ax;
  float ay;
 public:
  Ball *split();
  Ball(int);
  Ball(int t, int s, float px, float py);
  void draw();
  float getSize();
  void reposition();
  float operator+(Shape*);
};

#endif