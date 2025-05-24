#include "Platform.h"
#include "GLstuff.h"
#include "ScorePopUp.h"

ScorePopUp::ScorePopUp(float x, float y, int points)
{
	life = 600;
	value = points;
	isAlive = true;

	pos[X] = x;
	pos[Y] = y;
	pos[Z] = 0.0f;
}

void ScorePopUp::move()
{
	life--;
	if (life <= 0) { isAlive = false; }
	pos[Y] += 0.001f; //float speed = 0.01f;
}

void ScorePopUp::draw() {
    //expired
    if (!isAlive) return;

    //prepare text
    char buf[16];
    int  pts = value;
    snprintf(buf, sizeof(buf), "%d", pts);
    int len = (int)strlen(buf);

	//position and color
    glPushMatrix();
   
    glDisable(GL_LIGHTING);
	//glColor3f(1.0f, 0.498f, 0.314f);  //light red
	glColor3f(1.0f, 0.0f, 0.0f);    //red
    //glColor3f(0.5f, 0.0f, 0.5f);    // purple

    glRasterPos3f(pos[X], pos[Y], pos[Z]);

    for (int i = 0; i < len; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
    }
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

float ScorePopUp::getSize()
{
    return 0.0f;
}