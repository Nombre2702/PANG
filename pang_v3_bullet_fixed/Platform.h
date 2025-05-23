#pragma once // para evitarnos el include guard cl�sico que tenemos en lso dem�s headers.

#ifdef _WIN32
// Windows
#include <windows.h>
#include "glut.h" 
#define OPEN_FILE(fp, filename, mode) fopen_s(&fp, filename, mode)
#else
// Linux/Unix
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h> 
#define OPEN_FILE(fp, filename, mode) ((fp = fopen(filename, mode)) ? 0 : errno)
#endif