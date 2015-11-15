//Semestre 2016 - 1
//************************************************************//
//************************************************************//
//************************************************************//
#include "Main.h"
#include "texture.h"

float transZ = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
float angleX = 0.0f;
float angleY = 0.0f;
int screenW = 0.0;
int screenH = 0.0;
int normal = -1;
/***************
* Texturas
****************/
//Textura de fuera
CTexture pared;
//Textura piso
CTexture piso;
//Textura ventana
CTexture ventana;
//Textura puerta
CTexture puerta;


GLfloat Position[]= { 0.0f, 3.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

void InitGL ( void )     // Inicializamos parametros
{

	glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing

	//Configuracion luz
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_TEXTURE_2D);
	/*****************************
	* DefiniciOn de texturas
	*****************************/
	pared.LoadTGA("pared.tga");
	pared.BuildGLTexture();
	pared.ReleaseImage();

	piso.LoadTGA("piso.tga");
	piso.BuildGLTexture();
	piso.ReleaseImage();

	ventana.LoadTGA("ventana.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();

	puerta.LoadTGA("puerta.tga");
	puerta.BuildGLTexture();
	puerta.ReleaseImage();
}

void prisma(float largo, float altura, float profundidad, GLuint text)
{
	GLfloat vertice[8][3] = {
		{ largo*0.5 ,-altura*0.5, profundidad*0.5 },    //Coordenadas Vértice 0 V0
		{ -largo*0.5 ,-altura*0.5, profundidad*0.5 },    //Coordenadas Vértice 1 V1
		{ -largo*0.5 ,-altura*0.5, -profundidad*0.5 },    //Coordenadas Vértice 2 V2
		{ largo*0.5,-altura*0.5, -profundidad*0.5 },    //Coordenadas Vértice 3 V3
		{ largo*0.5,altura*0.5, profundidad*0.5 },    //Coordenadas Vértice 4 V4
		{ largo*0.5,altura*0.5, -profundidad*0.5 },    //Coordenadas Vértice 5 V5
		{ -largo*0.5,altura*0.5, -profundidad*0.5 },    //Coordenadas Vértice 6 V6
		{ -largo*0.5,altura*0.5, profundidad*0.5 },    //Coordenadas Vértice 7 V7
	};

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Front
		glNormal3f(0.0f, 0.0f, 1.0f*normal);
		glTexCoord2f(0, 0);	glVertex3fv(vertice[0]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[4]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[7]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f*normal, 0.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3fv(vertice[0]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[3]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[5]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f*normal);
		glTexCoord2f(0, 1); glVertex3fv(vertice[6]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[5]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[3]);
		glTexCoord2f(0, 0); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f*normal, 0.0f, 0.0f);
		glTexCoord2f(1, 0); glVertex3fv(vertice[1]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[7]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[6]);
		glTexCoord2f(0, 0); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, piso.GLindex);
	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, 1.0f*normal, 0.0f);
		glTexCoord2f(0, 0); glVertex3fv(vertice[0]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[1]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[2]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, 1.0f*normal, 0.0f);
		glTexCoord2f(0, 0); glVertex3fv(vertice[4]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[5]);		
		glTexCoord2f(1, 1); glVertex3fv(vertice[6]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[7]);
	glEnd();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	/*Array que contiene las texturas*/	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/******************************************
	* Agregar aquí
	******************************************/
	glPushMatrix();	
		glTranslatef(transX, 0.0f, transZ);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);
		glPushMatrix();
			prisma(76.7, 12, 48.7, pared.GLindex);						
		glPopMatrix();
	glPopMatrix();
  glutSwapBuffers ( );
  // Swap The Buffers
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	//glOrtho(-5,5,-5,5,0.2,20);	
	//glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 800);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	//glLoadIdentity();									
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'e':
		case 'E':
			transY +=6.0f;
			break;
		case 'q':
		case 'Q':
			transY +=6.0f;
		case 'w':
		case 'W':
			transZ +=6.0f;
			break;
		case 's':
		case 'S':
			transZ -=6.0f;
			break;
		case 'a':
		case 'A':
			transX += 6.0f;
			break;
		case 'd':
		case 'D':
			transX -= 6.0f;
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
		break;        
		default:        // Cualquier otra
		break;
  }
	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		angleX +=2.0f;
		break;
    case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
		angleX -=2.0f;
		break;
	case GLUT_KEY_LEFT:
		angleY +=2.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY -=2.0f;
		break;
    default:
      break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  screenW = glutGet(GLUT_SCREEN_WIDTH);
  screenH = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitWindowSize  (800, 600);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 5"); // Nombre de la Ventana
  printf("Resolution H: %i \n", screenW);
  printf("Resolution V: %i \n", screenH);
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutMainLoop        ( );          // 

  return 0;
}




