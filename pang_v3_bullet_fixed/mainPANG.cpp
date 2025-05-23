



//***********************
// Asteroids Open GL
// Claudio Rossi, Universidad Politécnica de Madrid 
// (C) 2015 
//***********************



#include "Platform.h"
#include "commonstuff.h"
#include "commonlibs.h"

#include "GLstuff.h"

#include "Shape.h"
#include "Ball.h"
#include "Bullet.h"
#include "Man.h"
#include "ObjectsList.h"


//***********************
// Prototipos de funciones 
//***********************

// Callback de la logica del juego
void myLogic();

//Callback de dibujo
void OnDibuja(void);	

//Callbacks para teclado
void OnKeyboardDown(unsigned char key, int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);

// función para imprimir invo en la pantalla
void printdata();

  
//***********************
// Variables globales
//***********************

//estado del juego
enum GameState { START_SCREEN, PLAYING, GAME_OVER };
GameState gameState = START_SCREEN;
bool gameStarted = false; // indica si el juego ha empezado o no

//invulnerabilidad del jugador
int invulnTime = 0;

// Posición de la camara
float cam_pos[6]={0, 0, 27};


// Objetos globales
ObjectsList worldobjects;   // lista de objetos del juego
Man *theMan=NULL;           // puntero al jugador 
Bullet *theBullet=NULL;     // puntero al proyectil

// Varias constantes usadas en el programa
int shotTime=0;     // contador de tiempo de vida del proyectil
int nMan=5;         // numero de "vidas"
int score=0;        // Puntuación
GLuint KLtexture;   // Texture data structure
GLuint playTexture; // Texture data structure




//***********************
// Programa principal
//***********************


int main(int argc,char* argv[])
{

  // inicializaciones


  // Inicialización GLUT
  glutInit(&argc, argv);
 
  // Inicializaciones openGL (ver GLstuff.c)
  init_GL_stuff((char*)"PANG 2022",WINX,WINY);
  

  // Define call backs te GLUT

  // Display function: contiene las instrucciones para dibujar los objetos
  glutDisplayFunc(OnDibuja);
  
  // Idle function: contiene la logica del juego
  glutIdleFunc(myLogic);
  
  // Callbacks de teclado
  glutKeyboardFunc(OnKeyboardDown);
  glutSpecialFunc(OnSpecKeyboardDown);

  
  // Posiciona el punto de vista (cámara)
  gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],   // posicion del  ojo  
	    0.0, 0.0, 0.0,		                    // hacia que punto mira  
	    0.0, 1.0, 0.0);                         // vector "UP"  (vertical positivo)

  // Carga la imagen del fondo
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  KLtexture= LoadTexture(800,600, "PANG.bmp" );
  playTexture = LoadTexture(800, 600, "PANG_background_resized.bmp");
  glBindTexture (GL_TEXTURE_2D, KLtexture);

  
  // WORLDOBJECTS es una variable estática, se inicializa "automaticamente" al ejecutar el programa
  // o sea, su constructor es ejecutado al crearla variable cuando arranca el programa
  // Contiene los elementos del juego (punteros a los objetos)  
  
  // Creación de los objetos iniciales
  theMan = worldobjects.getMan();
  
  // bucle infinito de Open GL
  glutMainLoop();

  // Esto solo sirve para que el compilador no proteste, nunca se llegará aquí
  return 0;   

}

/************************** FIN DEL MAIN ************************************/





//***********************
// Callbacks
//***********************


// Imprime puntuacción y num. de naves
void printdata()
{
  int i,l;
  char buffer[50];  // contiene la cadena de caracteres que se muestra
  
  glPushMatrix();

  snprintf(buffer, sizeof(buffer), "                Men: %d       Score: %d", nMan, score);
  l=strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i=0; i < l; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); 
    }
  glEnable(GL_LIGHTING);

  glPopMatrix();

}




// Logica del juego: mueve los objeto mandando el mensaje "move"
void myLogic()
{

    if (gameState != PLAYING)
        return;

    if (!gameStarted)
        return;

    if (invulnTime > 0) {
	    --invulnTime; //substract invulnerability time per frame
    }

    int res;  // variable auxiliar que contiene el resultado de la comprobacion de colision
	bool bulletState; // variable auxiliar que indica si el proyectil está en el aire o no

    // Pide al mudo que mueve los objetos
    worldobjects.move();

    // Comprieba si ha habido colisión, pasa referencia a proyectil y jugador, retorna tipo de colisión
    // res==0:  No ha colisicón
    // res==1:  Bola/jugador
    // res>=2:  Bola/Proyectil, depende del tipo de bola (grande/mediano/pequeño)
    res = worldobjects.collisions(theBullet,theMan);

    if (theBullet) {
        bulletState = theBullet->getStatus();
    }
  
    if (res == 1)    // Bola/jugador
    {
	    //if the player is immune, he doesn't lose a life
        if (invulnTime == 0) {
            nMan--;
        }

        if(nMan==0) {
	        gameState = GAME_OVER;
	    }
      
        theMan->resetpos();   // recoloca el jugador al centro
        worldobjects.reposition(theMan);   // comprueba que no haya una bola justo donde va a renacer el jugador
        if(invulnTime == 0) {
			//if not invulnerable, set invulnerability time
			invulnTime = 2400; //2 seconds of invulnerability
		}
    }

    if(res==2 || res==3 || res==4)    //   Bola/Proyectil
      { 
        score += 100*(res-1);              // Actualiza puntuación
      }

    if (res == 5) {
	    score += 600;                      // Actualiza puntuación
    }

    // borra el proyectil después de cierto tiempo si no ha dado con nada
    if (theBullet && !bulletState)
    {
        worldobjects.remove(theBullet);   // si theBullet==NULL no pasa nada, el metodo remove no lo encuentra y no hace nada
        theBullet = NULL;
    }

}
 
/**************************************************************/ 

void OnDibuja(void)
{ 
  //Borrado de la pantalla	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  switch (gameState) {
  case START_SCREEN:
          // Dibuja la imagen del fondo
          displaytext(KLtexture);
          //start text
          glDisable(GL_LIGHTING);
          glColor3f(1.0f, 1.0f, 1.0f);
          glRasterPos3f(-9, 9, -0.1);
          for (auto c : std::string("                                                      PRESS S TO START"))
              glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
          glEnable(GL_LIGHTING);
		  break;

  case PLAYING:
          drawBackgroundFullscreen(playTexture, WINX, WINY);
          // Manda el mensaje "draw" al mundo
          // Este mandará el mensaje "draw" a todas las figuras
          worldobjects.draw();

          //imprime los datos (vidas, puntuación)
          printdata();
	      break;
  case GAME_OVER:
          // Dibuja la imagen del fondo
          displaytext(KLtexture);
          worldobjects.draw();   // dibuja estático
          printdata();
          //game over text
          for (auto c : std::string("   GAME OVER"))
              glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
          for (auto c : std::string("   PRESS R TO RESTART"))
              glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		  break;
  }
 
  //Al final, cambiar el buffer y redibuja la pantalla
  glutSwapBuffers();
  glutPostRedisplay();
}

/**************************************************************/



   


void OnKeyboardDown(unsigned char key, int x, int y)
{ 
  int mod;

  mod=glutGetModifiers();

  switch (key)
  {
    case 'q':
    case ESC:
        exit(1);

    case 's':  //game start
        gameStarted = true;
        if (gameState == START_SCREEN) {
            gameState = PLAYING;
        }
        break;
    
    case 'r':  // Reinicia en Game Over
        if (gameState == GAME_OVER) {
			//delete all objects in the world
			worldobjects.~ObjectsList(); // destructor de la lista de objetos, borra todos los objetos
			//build new objectsList in same place
            new (&worldobjects) ObjectsList(); // reconstruye el mundo
			//rebuild theMan
            theMan = worldobjects.getMan();

            //restart game
            nMan = 5;
            score = 0;
            invulnTime = 0;
            shotTime = 0;
            theBullet = NULL;
            gameState = PLAYING;
        }
        break;

    case ' ':   // tecla espacio: disparo
        // Si no hay proyectil, lo crea  si el juego esta iniciado
        if (!theBullet && gameStarted)
        {
            Bullet* newB = theMan->fire();
            
            if (newB)
            {
                theBullet = newB;
                worldobjects.add(theBullet);
            }
        }
        break;
        //    case ',': theMan->hyperjump(); break;  // hyper jump (mueve el hombre a una posición random)

    }		

}

// solo usamos las teclas derecha e izquierda 
void OnSpecKeyboardDown(int key, int x, int y)
{ 
  switch(key)
    {

    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_LEFT:  theMan->strafe(-0.25,0,0);  // mueve el hompre a la izquierda
      break;
    case GLUT_KEY_RIGHT: theMan->strafe(0.25,0,0);   // mueve el hompre a la derecha
      break;
    case GLUT_KEY_PAGE_DOWN:
      break;
    case GLUT_KEY_PAGE_UP:
      break;
    }		

}