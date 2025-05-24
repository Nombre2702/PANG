#pragma once

#include "Platform.h"

#include "commonlibs.h"

// Prototipos de funciones
GLuint LoadTexture(int, int, const char * filename );

void displaytext(GLuint Thetexture);

void init_GL_stuff(char*,int,int);

void drawBackgroundFullscreen(GLuint texID, int windowW, int windowH);