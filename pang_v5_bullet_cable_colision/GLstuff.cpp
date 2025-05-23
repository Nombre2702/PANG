#include "GLstuff.h"


void init_GL_stuff(char *title, int ANCHO, int ALTO)
{
  //Creacion y definicion de la ventana
    
  glutInitWindowSize(ANCHO,ALTO);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow(title);

  //Habilitar las luces, la renderizacion y el color de los materiales
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
	
  //definir la proyeccion
  glMatrixMode(GL_PROJECTION);
  gluPerspective( 40.0, ANCHO/ALTO, 0.1, 50);

  
  // color del fondo
  //  glClearColor(0.5f, 0.91f, 0.9f, 0.5f);    
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);    
	
  // Define el punto de vista
  glMatrixMode(GL_MODELVIEW);	
 
}


GLuint LoadTexture( int width, int height, const char * filename )
{
    GLuint texture;
    unsigned char* data;
    FILE* file;

    if (OPEN_FILE(file, filename, "rb") != 0)
        return 0;
    

    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

  for(int i = 0; i < width * height ; ++i)
    {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];
      
      data[index] = R;
      data[index+2] = B;
      
    }
  
  
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
  
  
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );
  
  return texture;
}


void displaytext(GLuint Thetexture)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, Thetexture);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-8.0, -8.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-8.0, 8.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(8.0, 8.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(8.0, -8.0, 0.0);

   glEnd();
   glFlush();
   glDisable(GL_TEXTURE_2D);
}

void drawBackgroundFullscreen(GLuint texID, int windowW, int windowH) {
    // 1) Save current state
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // 2) Switch to projection matrix and draw in 2D
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // left, right, bottom, top
    gluOrtho2D(0, windowW, 0, windowH);

    // 3) Switch to modelview and draw a quad over the entire window
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glTexCoord2f(1, 0); glVertex2f(windowW, 0);
    glTexCoord2f(1, 1); glVertex2f(windowW, windowH);
    glTexCoord2f(0, 1); glVertex2f(0, windowH);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // 4) Restore state
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
}