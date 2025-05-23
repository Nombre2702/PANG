#pragma once

#include "commonstuff.h"

#include "Shape.h"
#include "Ball.h"
#include "Bullet.h"
#include "Man.h"
#include "Animalito.h"

struct nodo {
	Shape* data;    //pointer to the object Shape
	nodo* next;     //pointer to the next node in the list
};

class ObjectsList {
private:
	int n;				//number of objects
	struct nodo* head;	//head of the list
	Man* theMan;		//pointer to player
public:
	ObjectsList();				//constructor
	~ObjectsList();				//destructor
	void add(Shape* s);			//add object to the list
	void remove(Shape* s);		//remove object from the list
	void draw();				//draw all objects in the list
	void move();				//move all objects in the list
	Man* getMan();				//get pointer to player
	void reposition(Man* theMan);	//reposition object if it is out of bounds
	float collisions(Bullet* theBullet, Man* theMan);	//check for collisions between objects
};