//Semestre 2016 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
#include "Main.h"

float transZ = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
float angleX = 0.0f;
float angleY = 0.0f;
int screenW = 0.0;
int screenH = 0.0;


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
}

void prisma(float largo, float altura, float profundidad, GLuint text)
{
	GLfloat vertice[8][3] = {
		{ largo ,-altura, profundidad },    //Coordenadas Vértice 0 V0
		{ -largo ,-altura, profundidad },    //Coordenadas Vértice 1 V1
		{ -largo ,-altura, -profundidad },    //Coordenadas Vértice 2 V2
		{ largo ,-altura, -profundidad },    //Coordenadas Vértice 3 V3
		{ largo ,altura, profundidad },    //Coordenadas Vértice 4 V4
		{ largo ,altura, -profundidad },    //Coordenadas Vértice 5 V5
		{ -largo ,altura, -profundidad },    //Coordenadas Vértice 6 V6
		{ -largo ,altura , profundidad },    //Coordenadas Vértice 7 V7
	};

	glBegin(GL_POLYGON);	//Front
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[2]);
		glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[7]);
	glEnd();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glTranslatef(transX, 0.0f, transZ);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);		
		/***************************************
		*			Planta Baja
		***************************************/
		glPushMatrix();
			glColor3f(0,1,0);
			prisma(6,7,10,1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glTranslatef(26, 0,-10);
			glColor3f(0, 0, 1);
			prisma(20, 7, 18, 0);			
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 7, 18, 0);
			glTranslatef(25, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 7, 18, 0);
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 7, 18, 0);
			glTranslatef(26, 0, -8);
			glColor3f(0, 1, 0);
			prisma(6, 7, 10, 1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glPushMatrix();
				glTranslatef(-12, 0, 28);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);	
				glTranslatef(-118, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);
				glPushMatrix();
				glTranslatef(-12.5, 0, 31);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(107, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-14,0,46);
					glColor3f(1 ,0 ,1 );
					prisma(4, 7, 4, 0);
					glPushMatrix();
						glTranslatef(10, 0, 4);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(126, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(10, 0, -4);
						glColor3f(1, 0, 1);
						prisma(4, 7, 4, 0);
						glTranslatef(0, 0, 8);
						glColor3f(0, 1, 1);
						prisma(4, 7, 4, 0);
					glPopMatrix();
					glTranslatef(0, 0, 8);
					glColor3f(0, 1, 1);
					prisma(4, 7, 4, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-13,0,61);
					glColor3f(1, 1, 1);
					prisma(5, 7, 3,0);
					glPushMatrix();
						glTranslatef(10, 0, 15);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(124, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(10, 0, -15);
						glColor3f(1, 1, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 0, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 0, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 1);
						prisma(5, 7, 3, 0);
					glPopMatrix();
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 0, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 0, 1);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 1);
					prisma(5, 7, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					glTranslatef(-8, 0, 119);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
					glTranslatef(134, 0, 0);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-8,0,151);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glTranslatef(19, 0, -43);
						prisma(9, 7, 50, 0);
						glColor3f(1, 0, 0);
						glTranslatef(96, 0, 0);
						prisma(9, 7, 50, 0);
					glPopMatrix();
					glTranslatef(35, 0, -2);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(64, 0, 0);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(35, 0, 2);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		/***************************************
		*			Primer Piso
		***************************************/
		glPushMatrix(); 
			glTranslatef(0, 14, 0);
			glColor3f(1,1,1);
			prisma(6,7,10,1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glTranslatef(26, 0,-10);
			glColor3f(0, 0, 1);
			prisma(20, 7, 18, 0);			
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 7, 18, 0);
			glTranslatef(25, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 7, 18, 0);
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 7, 18, 0);
			glTranslatef(26, 0, -8);
			glColor3f(0, 1, 0);
			prisma(6, 7, 10, 1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glPushMatrix();
				glTranslatef(-12, 0, 28);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);	
				glTranslatef(-118, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);
				glPushMatrix();
				glTranslatef(-12.5, 0, 31);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(107, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-14,0,46);
					glColor3f(1 ,0 ,1 );
					prisma(4, 7, 4, 0);
					glPushMatrix();
						glTranslatef(10, 0, 4);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(126, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(10, 0, -4);
						glColor3f(1, 0, 1);
						prisma(4, 7, 4, 0);
						glTranslatef(0, 0, 8);
						glColor3f(0, 1, 1);
						prisma(4, 7, 4, 0);
					glPopMatrix();
					glTranslatef(0, 0, 8);
					glColor3f(0, 1, 1);
					prisma(4, 7, 4, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-13,0,61);
					glColor3f(1, 1, 1);
					prisma(5, 7, 3,0);
					glPushMatrix();
						glTranslatef(10, 0, 15);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(124, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(10, 0, -15);
						glColor3f(1, 1, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 0, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 0, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 1);
						prisma(5, 7, 3, 0);
					glPopMatrix();
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 0, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 0, 1);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 1);
					prisma(5, 7, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					glTranslatef(-8, 0, 119);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
					glTranslatef(134, 0, 0);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-8,0,151);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glTranslatef(19, 0, -43);
						prisma(9, 7, 50, 0);
						glColor3f(1, 0, 0);
						glTranslatef(96, 0, 0);
						prisma(9, 7, 50, 0);
					glPopMatrix();
					glTranslatef(35, 0, -2);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(64, 0, 0);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(35, 0, 2);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/***************************************
		*			Segundo Piso
		***************************************/
		glPushMatrix(); 
			glTranslatef(0, 14, 0);
			glColor3f(1,0,1);
			prisma(6,7,10,1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glTranslatef(26, 0,-10);
			glColor3f(0, 0, 1);
			prisma(20, 7, 18, 0);			
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 7, 18, 0);
			glTranslatef(25, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 7, 18, 0);
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 7, 18, 0);
			glTranslatef(26, 0, -8);
			glColor3f(0, 1, 0);
			prisma(6, 7, 10, 1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glPushMatrix();
				glTranslatef(-12, 0, 28);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);	
				glTranslatef(-118, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);
				glPushMatrix();
				glTranslatef(-12.5, 0, 31);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(107, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-14,0,46);
					glColor3f(1 ,0 ,1 );
					prisma(4, 7, 4, 0);
					glPushMatrix();
						glTranslatef(10, 0, 4);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(126, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(10, 0, -4);
						glColor3f(1, 0, 1);
						prisma(4, 7, 4, 0);
						glTranslatef(0, 0, 8);
						glColor3f(0, 1, 1);
						prisma(4, 7, 4, 0);
					glPopMatrix();
					glTranslatef(0, 0, 8);
					glColor3f(0, 1, 1);
					prisma(4, 7, 4, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-13,0,61);
					glColor3f(1, 1, 1);
					prisma(5, 7, 3,0);
					glPushMatrix();
						glTranslatef(10, 0, 15);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(124, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(10, 0, -15);
						glColor3f(1, 1, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 0, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 0, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 1);
						prisma(5, 7, 3, 0);
					glPopMatrix();
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 0, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 0, 1);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 1);
					prisma(5, 7, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					glTranslatef(-8, 0, 119);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
					glTranslatef(134, 0, 0);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-8,0,151);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glTranslatef(19, 0, -43);
						prisma(9, 7, 50, 0);
						glColor3f(1, 0, 0);
						glTranslatef(96, 0, 0);
						prisma(9, 7, 50, 0);
					glPopMatrix();
					glTranslatef(35, 0, -2);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(64, 0, 0);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(35, 0, 2);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/***************************************
		*			Tercer Piso
		***************************************/
		glPushMatrix(); 
			glTranslatef(0, 28, 0);
			glColor3f(1,1,0);
			prisma(6,7,10,1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glTranslatef(26, 0,-10);
			glColor3f(0, 0, 1);
			prisma(20, 7, 18, 0);			
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 7, 18, 0);
			glTranslatef(25, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 7, 18, 0);
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 7, 18, 0);
			glTranslatef(26, 0, -8);
			glColor3f(0, 1, 0);
			prisma(6, 7, 10, 1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glPushMatrix();
				glTranslatef(-12, 0, 28);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);	
				glTranslatef(-118, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);
				glPushMatrix();
				glTranslatef(-12.5, 0, 31);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(107, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-14,0,46);
					glColor3f(1 ,0 ,1 );
					prisma(4, 7, 4, 0);
					glPushMatrix();
						glTranslatef(10, 0, 4);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(126, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(10, 0, -4);
						glColor3f(1, 0, 1);
						prisma(4, 7, 4, 0);
						glTranslatef(0, 0, 8);
						glColor3f(0, 1, 1);
						prisma(4, 7, 4, 0);
					glPopMatrix();
					glTranslatef(0, 0, 8);
					glColor3f(0, 1, 1);
					prisma(4, 7, 4, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-13,0,61);
					glColor3f(1, 1, 1);
					prisma(5, 7, 3,0);
					glPushMatrix();
						glTranslatef(10, 0, 15);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(124, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(10, 0, -15);
						glColor3f(1, 1, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 0, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 0, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 1);
						prisma(5, 7, 3, 0);
					glPopMatrix();
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 0, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 0, 1);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 1);
					prisma(5, 7, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					glTranslatef(-8, 0, 119);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
					glTranslatef(134, 0, 0);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-8,0,151);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glTranslatef(19, 0, -43);
						prisma(9, 7, 50, 0);
						glColor3f(1, 0, 0);
						glTranslatef(96, 0, 0);
						prisma(9, 7, 50, 0);
					glPopMatrix();
					glTranslatef(35, 0, -2);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(64, 0, 0);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(35, 0, 2);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/***************************************
		*			Cuarto Piso
		***************************************/
		glPushMatrix(); 
			glTranslatef(0, 42, 0);
			glColor3f(0,1,1);
			prisma(6,7,10,1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glTranslatef(26, 0,-10);
			glColor3f(0, 0, 1);
			prisma(20, 7, 18, 0);			
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 7, 18, 0);
			glTranslatef(25, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 7, 18, 0);
			glTranslatef(32.5, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 7, 18, 0);
			glTranslatef(26, 0, -8);
			glColor3f(0, 1, 0);
			prisma(6, 7, 10, 1);
			glTranslatef(0, 0, 18);
			glColor3f(1, 0, 0);
			prisma(6, 7, 8, 1);
			glPushMatrix();
				glTranslatef(-12, 0, 28);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);	
				glTranslatef(-118, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 7, 20, 1);
				glPushMatrix();
				glTranslatef(-12.5, 0, 31);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(107, 0, 0);
				glColor3f(0, 0, 1);
				prisma(12.5, 7, 11, 0);
				glTranslatef(18, 0, 0);
				glColor3f(1, 0, 0);
				prisma(5.5, 7, 11, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-14,0,46);
					glColor3f(1 ,0 ,1 );
					prisma(4, 7, 4, 0);
					glPushMatrix();
						glTranslatef(10, 0, 4);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(126, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 7, 8, 0);
						glTranslatef(10, 0, -4);
						glColor3f(1, 0, 1);
						prisma(4, 7, 4, 0);
						glTranslatef(0, 0, 8);
						glColor3f(0, 1, 1);
						prisma(4, 7, 4, 0);
					glPopMatrix();
					glTranslatef(0, 0, 8);
					glColor3f(0, 1, 1);
					prisma(4, 7, 4, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-13,0,61);
					glColor3f(1, 1, 1);
					prisma(5, 7, 3,0);
					glPushMatrix();
						glTranslatef(10, 0, 15);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(124, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 7, 18, 0);
						glTranslatef(10, 0, -15);
						glColor3f(1, 1, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 0, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 0, 1);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(1, 1, 0);
						prisma(5, 7, 3, 0);
						glTranslatef(0, 0, 6);
						glColor3f(0, 1, 1);
						prisma(5, 7, 3, 0);
					glPopMatrix();
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 0, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 0, 1);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(1, 1, 0);
					prisma(5, 7, 3, 0);
					glTranslatef(0, 0, 6);
					glColor3f(0, 1, 1);
					prisma(5, 7, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					glTranslatef(-8, 0, 119);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
					glTranslatef(134, 0, 0);
					glColor3f(1, 0, 1);
					prisma(10, 7, 25, 0);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-8,0,151);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
					glPushMatrix();
						glColor3f(1, 0, 0);
						glTranslatef(19, 0, -43);
						prisma(9, 7, 50, 0);
						glColor3f(1, 0, 0);
						glTranslatef(96, 0, 0);
						prisma(9, 7, 50, 0);
					glPopMatrix();
					glTranslatef(35, 0, -2);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(64, 0, 0);
					glColor3f(0, 1, 0);
					prisma(7, 7, 9, 0);
					glTranslatef(35, 0, 2);
					glColor3f(1, 1, 1);
					prisma(10, 7, 7, 0);
				glPopMatrix();
			glPopMatrix();
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
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 700);

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



