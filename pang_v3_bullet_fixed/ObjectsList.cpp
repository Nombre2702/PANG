#include "Platform.h"
#include "GLstuff.h"
#include "commonlibs.h"

#include "ObjectsList.h"

ObjectsList::ObjectsList(){
	srand((unsigned)time(nullptr)); //seed the random number generator

	head = NULL;
	n = 0;
	
	//create new Man oject
	theMan = new Man();
	add(theMan);

	//create NUMBALLS Ball objects and add them to the list
	for(int i = 0; i < NUMBALLS; i++) {
		Ball* ball = new Ball(BIG); //initially balls are BIG
		add(ball);
	}

	reposition(theMan);	//reposition balls to avoid collision with the player
}

ObjectsList::~ObjectsList() {
	//delete all objects in the list
	struct nodo* current = head;

	while(current != NULL) {
		struct nodo* next = current->next;	//save in next the next node
		delete current->data;		//delete current Shape object
		delete current;				//delete the nodo object
		current = next;				//move to the next node
	}

	//list is empty now
	head = NULL;	//set head to NULL
	n = 0;			//set number of objects to 0
}

void ObjectsList::add(Shape* s) {
	nodo* newNodo = new struct nodo;	//create a new nodo object
	newNodo->data = s;		//set the data to the new Shape object
	newNodo->next = head;	//set the next pointer to the current head
	head = newNodo;			//set the head to the new nodo object
	n++; //increment the number of objects in the list
	
}

void ObjectsList::remove(Shape* s) {
	if (head == NULL) return; //if the list is empty, do nothing

	//special case: if the head is the one to be removed
	if (head->data == s) {
		struct nodo* temp = head;	//save the current head
		head = head->next;			//set the head to the next nodo
		delete temp->data;			//delete the Shape object
		delete temp;				//delete the nodo object
		n--;						//decrement the number of objects
		return;
	}

	//look for the nodo to remove
	struct nodo* current = head;	//current is the nodo before the one to be removed
	while (current->next != NULL && current->next->data != s) {
		current = current->next;	//move to the next nodo
	}

	if (current->next != NULL) {
		struct nodo* temp = current->next;	//save the nodo to be removed
		current->next = temp->next;			//set the next pointer of the current nodo to the next nodo
		delete temp->data;					//delete the Shape object
		delete temp;						//delete the nodo object
		n--;								//decrement the number of objects
	}
}

void ObjectsList::draw() {
	struct nodo* current = head;	//get the first nodo in the list
	//draw until there are no more nodos to draw
	while (current != NULL) {
		current->data->draw();		//each Shape object draws itself
		current = current->next;	//move to the next nodo
	}
}

void ObjectsList::move() {
	struct nodo* current = head;
	while (current != NULL) {
		current->data->move();		//each Shape object moves itself
		current = current->next;	//move to the next nodo
	}

	//spawn a new animalito every 12000 frames
	if (rand() % 12000 == 0) {
		float x = RAND_FRAC() * 2 * SIZEX2 - SIZEX2;	//x en [-SIZEX2, +SIZEX2]
		float y = RAND_FRAC() * (SIZEY2 - 2.0f) + 2.0f;	//y en [2, SIZEY2]
		float spd = 0.001f; // velocidad fija

		Animalito* animalito = new Animalito(x, y, spd); //create a new animalito object
		add(animalito); //add the animalito to the list	
	}
}

Man* ObjectsList::getMan() {
	return theMan;
}

void ObjectsList::reposition(Man* theMan) {
	struct nodo* current = head;

	float manPos[3];

	theMan->getPos(manPos);

	float x_player = manPos[X];
	float y_player = manPos[Y];

	while (current != NULL) {
		Ball* ball = dynamic_cast<Ball*>(current->data);
		if (ball) {
			float ballPos[3];

			ball->getPos(ballPos);

			float x_ball = ballPos[X];
			float y_ball = ballPos[Y];

			float distance = *ball + theMan;

			//if the ball is too close to the player, move it elsewhere
			while (distance < (ball->getSize() + theMan->getSize())) {
				ball->reposition();		//move ball elsewhere
				ball->getPos(ballPos);	//get new position of the ball

				x_ball = ballPos[X];
				y_ball = ballPos[Y];
				distance = *ball + theMan;
			}
		}
		current = current->next;
	}
}

float ObjectsList::collisions(Bullet* theBullet, Man* theMan) {
	struct nodo* current = head;

	while (current != NULL) {

		//check collision for Ball objects
		Ball* ball = dynamic_cast<Ball*>(current->data); //try to cast the current object to a Ball object
		//if the object is a ball
		if (ball) {
			//check collision between ball and man
			float ballPos[3], manPos[3];
			ball->getPos(ballPos);	//get the position of the ball
			theMan->getPos(manPos); //get the position of theMan

			float x_ball = ballPos[X];
			float y_ball = ballPos[Y];
			float x_player = manPos[X];
			float y_player = manPos[Y];

			float distance = *ball + theMan;
			//if collision detected
			if (distance < (ball->getSize() + theMan->getSize())) {
				return 1.0f; //collision detected
			}

			//check collision between ball and bullet
			if (theBullet) {
				float bulletPos[3];

				theBullet->getPos(bulletPos);	//get the position of the bullet

				float x_bullet = bulletPos[X];
				float y_bullet = bulletPos[Y];

				distance = *ball + theBullet;
				//if collision detected
				if (distance < (ball->getSize() + theBullet->getSize())) {
					//remove(theBullet);	//remove the bullet from the list, we do it main

					float size_aux = ball->getSize();	//get the size of the ball
					int size = int(size_aux / 0.3f + 0.5f);	//get the size code of the ball
					//depending on the size of the ball, create a new ball of a different size or delete the ball
					if(size == BIG) {
						Ball* newBall = ball->split();	//create a new ball of medium size
						add(newBall);					//add the new ball to the list
						theBullet->setStatus(false);	//set the bullet status to false (inactive)
						return 2.0f;					//collision detected with BIG ball
					} else if (size == MEDIUM) {
						Ball* newBall = ball->split();	//create a new ball of small size
						add(newBall);					//add the new ball to the list
						theBullet->setStatus(false);	//set the bullet status to false (inactive)
						return 3.0f;					//collision detected with MEDIUM ball
					} else if (size == SMALL) {
						remove(ball);	//remove the ball from the list
						theBullet->setStatus(false);	//set the bullet status to false (inactive)
						return 4.0f;	//collision detected with SMALL ball
					}
				}
			}
		}

		//check collision between Animalito and theBullet
		Animalito* animalito = dynamic_cast<Animalito*>(current->data); //try to cast the current object to an Animalito object
		if (animalito && theBullet) {
			float distance = *animalito + theBullet; //get the distance between the animalito and the bullet
			if (distance < (animalito->getSize() + theBullet->getSize())) {
				remove (animalito);	//remove the animalito from the list
				theBullet->setStatus(false);	//set the bullet status to false (inactive)
				return 5.0f;		//collision detected with animalito
			}
		}

		current = current->next;	//move to the next nodo
	}
	return 0.0f;
}