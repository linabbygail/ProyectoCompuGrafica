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
int otherVariable;

/***************
* Texturas
****************/
//Textura de fuera
CTexture fuera;
//Textura pared
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
	fuera.LoadTGA("fuera3.tga");
	fuera.BuildGLTexture();
	fuera.ReleaseImage();

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
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0);	glVertex3fv(vertice[0]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[4]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[7]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3fv(vertice[0]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[3]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[5]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3fv(vertice[6]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[5]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[3]);
		glTexCoord2f(0, 0); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 0); glVertex3fv(vertice[1]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[7]);
		glTexCoord2f(0, 1); glVertex3fv(vertice[6]);
		glTexCoord2f(0, 0); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, piso.GLindex);
	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3fv(vertice[0]);
		glTexCoord2f(1, 0); glVertex3fv(vertice[1]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[2]);
		glTexCoord2f(1, 1); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, 1.0f, 0.0f);
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

	glPushMatrix();
		glTranslatef(transX, 0.0f, transZ);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);		

		glColor3f(1, 1, 1);
		/*Barandales por fuera*/
		glPushMatrix();
			glPushMatrix();
				glTranslatef(74.5, 30, -4.5);
				glColor3f(1, 1, 0);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 18);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 19);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 19);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 1.1);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 16.9);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 25);
				prisma(1, 72, 1, 0);
				glTranslatef(0, 0, 17);
				prisma(1, 72, 1, 0);
			glPopMatrix();
			glTranslatef(-3.5, 30, -4.5);
			glColor3f(1, 1, 0);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 18);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 19);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 19);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 1.1);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 16.9);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 25);
			prisma(1, 72, 1, 0);
			glTranslatef(0, 0, 17);
			prisma(1, 72, 1, 0);
		glPopMatrix();

		/***************************************
		*			Planta Baja
		***************************************/
		glPushMatrix();
			/*Baño izquierda*/
			glColor3f(0,1,0);
			prisma(6, 12,10,1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);				
			glPopMatrix();
			/*DRS izquierda*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			/*Oficina director izquierda*/
			glTranslatef(13, 0,-5);
			glColor3f(0, 0, 1);
			prisma(20, 12, 18, 0);						
			/*Ventana director izquierda*/
			glPushMatrix();
				glTranslatef(-4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);				
			glPopMatrix();			
			/*Supporting staff office izquierda*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin izquierda*/
			glPushMatrix();
				glTranslatef(1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Supporting staff office derecha*/
			glTranslatef(12.5, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin derecha*/
			glPushMatrix();
				glTranslatef(-1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Director office derecha*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 12, 18, 0);
			/*Ventana director derecha*/
			glPushMatrix();
				glTranslatef(4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);				
			glPopMatrix();			
			/*Bath derecha*/
			glTranslatef(13, 0, -4);
			glColor3f(0, 1, 0);
			prisma(6, 12, 10, 1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);
			glPopMatrix();
			/*DRS derecha*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			glPushMatrix();
				/*Director office derecha*/
				glTranslatef(-6, 0, 14);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);	
				/*Director office izquierda*/
				glTranslatef(-59, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);				
				/*	Ventana oficiona director izquierda*/
				glPushMatrix();
					glTranslatef(-9,0,0);
					glColor3f(0.62,0.92,0.99);
					prisma(0.1,6,8,0);
					/*	Ventana oficiona director derecha*/
					glTranslatef(77, 0, 0);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 8, 0);
				glPopMatrix();		
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-6.25, 0, 15.5);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.75,0,1);
						glColor3f(0.62,0.92,0.99);
						prisma(0.1,6,4,0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();			
					/*staff office izquierdo*/
					glTranslatef(9, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*staff office derecho*/
					glTranslatef(53.5, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*bath derecho*/
					glTranslatef(9, 0, 0);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-7,0,23);
					glColor3f(1 ,0 ,1 );
					prisma(4, 12, 4, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2, 0, -0.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
					glPushMatrix();
						/*f.lavortry izquierdo*/
						glTranslatef(5, 0, 2);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*f.lavortry derecha*/
						glTranslatef(63, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*wc derecha*/
						glTranslatef(5, 0, -2);
						glColor3f(1, 0, 1);
						prisma(4, 12, 4, 0);
						/*wc derecha*/
						glTranslatef(0, 0, 4);
						glColor3f(0, 1, 1);
						prisma(4, 12, 4, 0);
					glPopMatrix();
					/*wc izquierda*/
					glTranslatef(0, 0, 4);
					glColor3f(0, 1, 1);
					prisma(4, 12, 4, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-6.5,0,30.5);
					glColor3f(1, 1, 1);
					prisma(5, 12, 3,0);
					glPushMatrix();
						/*m.lavortry izquierdo*/
						glTranslatef(5, 0, 7.5);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*m.lavortry derecho*/
						glTranslatef(62, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*wc derecho*/
						glTranslatef(5, 0, -7.5);
						glColor3f(1, 1, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 0, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 0, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 1);
						prisma(5, 12, 3, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 0, 0);
					prisma(5, 12, 3, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.5, 0, 2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana lado derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 0, 1);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 1);
					prisma(5, 12, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					/*dining hall*/
					glTranslatef(-4, 0, 59.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 25, 0);
					/*ventana dining hall*/
					glPushMatrix();
						glTranslatef(-5, 0, -2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*archive*/
					glTranslatef(67, 0, -7.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 10, 0);
					/*computer net room*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 0, 0);
					prisma(10, 12, 10, 0);
					/*telephone exchange*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 1, 0);
					prisma(10, 12, 10, 0);
					/*electric room*/
					glTranslatef(0, 0, 11);
					glColor3f(1, 1, 1);
					prisma(10, 12, 12, 0);
				glPopMatrix();
				glPushMatrix();
					/*kitchen*/
					glTranslatef(-4,0,80.5);
					glColor3f(1, 1, 1);
					prisma(10, 12, 17, 0);
					/*kitchen ventana*/
					glPushMatrix();
						glTranslatef(-5, 0, -3.5); 
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
					glPushMatrix();
						/*corridor izquierdo*/
						glColor3f(1, 0, 0);
						glTranslatef(9.5, 0, -22);
						prisma(9, 12, 59, 0);
						/*corridor derecho*/
						glColor3f(1, 0, 0);
						glTranslatef(48, 0, 0);
						prisma(9, 12, 59, 0);
					glPopMatrix();					
				glPopMatrix();				
			glPopMatrix();
			glPushMatrix();
				/*Corridor central*/
				glTranslatef(-36,-3, 110.5);
				glColor3f(0, 1, 0);
				prisma(69, 12, 15, 0);
				/*Ventanas corridor central*/
				glPushMatrix();
					/*Ventana izquierda*/
					glTranslatef(-34.5, 0, 3.75);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
					/*Ventana derecha*/
					glTranslatef(69, 0, -2.25);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7, 0);
				glPopMatrix();
				glPushMatrix();				
					/*bath izquierdo*/
					glTranslatef(-32,0,12.5);
					glColor3f(1,1,0);
					prisma(5,12,10,0);
					/*Ventana izquierda*/
					glPushMatrix();
						glTranslatef(-2.5, 0, -1.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
						glPushMatrix();
							/*suporting izquierdo*/
							glTranslatef(8,0,0);
							glColor3f(1,0,1);
							prisma(12,12,10,0);
							/*suporting derecho*/
							glTranslatef(47.5, 0, 0);
							glColor3f(1, 0, 1);
							prisma(12, 12, 10, 0);
						glPopMatrix();
					/*bath derecho*/
					glTranslatef(64, 0, 0);
					glColor3f(1, 1, 0);
					prisma(5, 12, 10, 0);
					/*Ventana*/
					glPushMatrix();
						glTranslatef(2.5, 0, -3);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*Director office*/
						glTranslatef(-8.5,0,12);
						glColor3f(1, 1, 1);
						prisma(22, 12, 14, 0);
						/*Ventana*/
						glPushMatrix();
							glTranslatef(11, 0, -2);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						/*Columna*/
						glTranslatef(-3, 0, 7.75);
						glColor3f(0, 0, 1);
						prisma(1.5, 12, 1.5, 0);
						/**/
						glTranslatef(-0.75, 0, 5.75);
						glColor3f(1, 0, 0);
						prisma(0.1, 12, 10, 0);						
						/*Ventana*/
						glTranslatef(0, 1, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.12, 6, 10, 0);						
					glPopMatrix();
				glPopMatrix();
				/*falta agregar a la oficina del direct un cuadrito D:*/
				glPushMatrix();
					glTranslatef(-23,0,24.5);
					glColor3f(0, 1, 1);
					prisma(23, 12, 14, 0);
					/*Ventana izquierda*/
					glPushMatrix();	
						/*Primer ventana*/
						glTranslatef(-11.5, 0, -2);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
						/*Segunda ventana*/
						glTranslatef(0, 0, 7);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*rest room izquierda*/
						glTranslatef(-5.5, 0, 17);
						glColor3f(1, 0, 0);
						prisma(12, 12, 20, 0);
						/*ventna rest room izquierda*/
						glPushMatrix();
							/*Primer ventana*/
							glTranslatef(-6, 0, -6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);						
							/*Segunda ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							/*Tercer ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						glPushMatrix();
							/*drs izquierda*/
							glTranslatef(-2.5, 0, 13.5);
							glColor3f(1, 1, 1);
							prisma(7, 12, 7, 0);
							glPushMatrix();
								/*managing director office de izquierda*/
								glTranslatef(16.5, 0, 5.5);
								glColor3f(1,0,1);
								prisma(26, 12, 18, 0);
								/*Ventanas*/
								glPushMatrix();
									glTranslatef(-9, 0, 9);
									glColor3f(0.62, 0.92, 0.99);
									prisma(8, 6, 0.1, 0);
									glTranslatef(10, 0, 0);
									glColor3f(0.62, 0.92, 0.99);
									prisma(8, 6, 0.1, 0);
									glTranslatef(12, 0, -9);
									glColor3f(0.62, 0.92, 0.99);
									prisma(0.1, 6, 8, 0);
								glPopMatrix();
								/*Columna*/
								glTranslatef(13.75, 0, -8.25);
								glColor3f(0, 1, 1);
								prisma(1.5, 12, 1.5, 0);
								/**/
								glTranslatef(5.75, 0, -0.75);
								glColor3f(1, 0, 0);
								prisma(10, 12, 0.1, 0);								
								/*Ventana*/
								glTranslatef(0, 1, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(10, 6, 0.12, 0);
								/*Central, puerta*/								
								//glRotatef(45, 0, 1, 0);
								glTranslatef(9.9, -1, -4.2);								
								glRotatef(41, 0, 1, 0);
								glColor3f(1, 1, 0);							
								prisma(13, 12, 0.1, 0);
								/*Puerta*/
								glTranslatef(0, -1, 0);
								glColor3f(1,1,1);
								prisma(7,10,0.12,0);
								/*Ventana*/
								glTranslatef(-5, 2, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(3, 6, 0.12, 0);
								glTranslatef(10, 0, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(3, 6, 0.12, 0);
							glPopMatrix();
							/*bath izquierda*/
							glTranslatef(0, 0, 9);
							glColor3f(0, 1, 1);
							prisma(7, 12, 11, 0);
							/*ventana bath izquierda*/
							glPushMatrix();
								glTranslatef(-3.5, 0, 2);
								glColor3f(0.62, 0.92, 0.99);
								prisma(0.1, 6, 4, 0);
							glPopMatrix();
						glPopMatrix();
						/*supporting staff*/
						glTranslatef(11.5, 0, 0);
						glColor3f(0, 0, 1);
						prisma(11, 12, 20, 0);
					glPopMatrix();
				glPopMatrix();				
			glPopMatrix();			
		glPopMatrix();

		/***************************************
		*			Primer piso
		***************************************/
		glPushMatrix();
			glTranslatef(0,12,0);
					/*Baño izquierda*/
			glColor3f(0,1,0);
			prisma(6, 12,10,1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);
			glPopMatrix();
			/*DRS izquierda*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			/*Oficina director izquierda*/
			glTranslatef(13, 0,-5);
			glColor3f(0, 0, 1);
			prisma(20, 12, 18, 0);						
			/*Ventana director izquierda*/
			glPushMatrix();
				glTranslatef(-4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);
			glPopMatrix();			
			/*Supporting staff office izquierda*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin izquierda*/
			glPushMatrix();
				glTranslatef(1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Supporting staff office derecha*/
			glTranslatef(12.5, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin derecha*/
			glPushMatrix();
				glTranslatef(-1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Director office derecha*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 12, 18, 0);
			/*Ventana director derecha*/
			glPushMatrix();
				glTranslatef(4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);
			glPopMatrix();			
			/*Bath derecha*/
			glTranslatef(13, 0, -4);
			glColor3f(0, 1, 0);
			prisma(6, 12, 10, 1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);
			glPopMatrix();
			/*DRS derecha*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			glPushMatrix();
				/*Director office derecha*/
				glTranslatef(-6, 0, 14);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);	
				/*Director office izquierda*/
				glTranslatef(-59, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);
				/*	Ventana oficiona director izquierda*/
				glPushMatrix();
					glTranslatef(-9,0,0);
					glColor3f(0.62,0.92,0.99);
					prisma(0.1,6,8,0);
					/*	Ventana oficiona director derecha*/
					glTranslatef(77, 0, 0);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 8, 0);
				glPopMatrix();		
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-6.25, 0, 15.5);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.75,0,1);
						glColor3f(0.62,0.92,0.99);
						prisma(0.1,6,4,0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();			
					/*staff office izquierdo*/
					glTranslatef(9, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*staff office derecho*/
					glTranslatef(53.5, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*bath derecho*/
					glTranslatef(9, 0, 0);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-7,0,23);
					glColor3f(1 ,0 ,1 );
					prisma(4, 12, 4, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2, 0, -0.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
					glPushMatrix();
						/*f.lavortry izquierdo*/
						glTranslatef(5, 0, 2);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*f.lavortry derecha*/
						glTranslatef(63, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*wc derecha*/
						glTranslatef(5, 0, -2);
						glColor3f(1, 0, 1);
						prisma(4, 12, 4, 0);
						/*wc derecha*/
						glTranslatef(0, 0, 4);
						glColor3f(0, 1, 1);
						prisma(4, 12, 4, 0);
					glPopMatrix();
					/*wc izquierda*/
					glTranslatef(0, 0, 4);
					glColor3f(0, 1, 1);
					prisma(4, 12, 4, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-6.5,0,30.5);
					glColor3f(1, 1, 1);
					prisma(5, 12, 3,0);
					glPushMatrix();
						/*m.lavortry izquierdo*/
						glTranslatef(5, 0, 7.5);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*m.lavortry derecho*/
						glTranslatef(62, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*wc derecho*/
						glTranslatef(5, 0, -7.5);
						glColor3f(1, 1, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 0, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 0, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 1);
						prisma(5, 12, 3, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 0, 0);
					prisma(5, 12, 3, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.5, 0, 2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana lado derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 0, 1);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 1);
					prisma(5, 12, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					/*dining hall*/
					glTranslatef(-4, 0, 59.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 25, 0);
					/*ventana dining hall*/
					glPushMatrix();
						glTranslatef(-5, 0, -2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*archive*/
					glTranslatef(67, 0, -7.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 10, 0);
					/*computer net room*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 0, 0);
					prisma(10, 12, 10, 0);
					/*telephone exchange*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 1, 0);
					prisma(10, 12, 10, 0);
					/*electric room*/
					glTranslatef(0, 0, 11);
					glColor3f(1, 1, 1);
					prisma(10, 12, 12, 0);
				glPopMatrix();
				glPushMatrix();
					/*kitchen*/
					glTranslatef(-4,0,80.5);
					glColor3f(1, 1, 1);
					prisma(10, 12, 17, 0);
					/*kitchen ventana*/
					glPushMatrix();
						glTranslatef(-5, 0, -3.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
					glPushMatrix();
						/*corridor izquierdo*/
						glColor3f(1, 0, 0);
						glTranslatef(9.5, 0, -22);
						prisma(9, 12, 59, 0);
						/*corridor derecho*/
						glColor3f(1, 0, 0);
						glTranslatef(48, 0, 0);
						prisma(9, 12, 59, 0);
					glPopMatrix();					
				glPopMatrix();				
			glPopMatrix();
			glPushMatrix();
				/*Corridor central*/
				glTranslatef(-36,-3, 110.5);
				glColor3f(0, 1, 0);
				prisma(69, 12, 15, 0);
				/*Ventanas corridor central*/
				glPushMatrix();
					/*Ventana izquierda*/
					glTranslatef(-34.5, 0, 3.75);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
					/*Ventana derecha*/
					glTranslatef(69, 0, -2.25);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7, 0);
				glPopMatrix();
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-32,0,12.5);
					glColor3f(1,1,0);
					prisma(5,12,10,0);
					/*Ventana izquierda*/
					glPushMatrix();
						glTranslatef(-2.5, 0, -1.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
						glPushMatrix();
							/*suporting izquierdo*/
							glTranslatef(8,0,0);
							glColor3f(1,0,1);
							prisma(12,12,10,0);
							/*suporting derecho*/
							glTranslatef(47.5, 0, 0);
							glColor3f(1, 0, 1);
							prisma(12, 12, 10, 0);
						glPopMatrix();
					/*bath derecho*/
					glTranslatef(64, 0, 0);
					glColor3f(1, 1, 0);
					prisma(5, 12, 10, 0);
					/*Ventana*/
					glPushMatrix();
						glTranslatef(2.5, 0, -3);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*Director office*/
						glTranslatef(-8.5,0,12);
						glColor3f(1, 1, 1);
						prisma(22, 12, 14, 0);
						/*Ventana*/
						glPushMatrix();
							glTranslatef(11, 0, -2);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						/*Columna*/
						glTranslatef(-3, 0, 7.75);
						glColor3f(0, 0, 1);
						prisma(1.5, 12, 1.5, 0);
						/**/
						glTranslatef(-0.75, 0, 5.75);
						glColor3f(1, 0, 0);
						prisma(0.1, 12, 10, 0);						
						/*Ventana*/
						glTranslatef(0, 1, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.12, 6, 10, 0);						
					glPopMatrix();
					glPushMatrix();
						/*senior manager office*/
						glTranslatef(-5,0,12);
						glColor3f(1, 1, 1);
						prisma(15, 12, 14, 0);	
						glTranslatef(-10.5, 0, 27);
						glColor3f(1, 0, 0);
						prisma(36, 12, 40, 0);						
					glPopMatrix();
				glPopMatrix();
				/*falta agregar a la oficina del direct un cuadrito D:*/
				glPushMatrix();
					glTranslatef(-23,0,24.5);
					glColor3f(0, 1, 1);
					prisma(23, 12, 14, 0);
					/*Ventana izquierda*/
					glPushMatrix();	
						/*Primer ventana*/
						glTranslatef(-11.5, 0, -2);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
						/*Segunda ventana*/
						glTranslatef(0, 0, 7);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*rest room*/
						glTranslatef(-5.5, 0, 17);
						glColor3f(1, 0, 0);
						prisma(12, 12, 20, 0);
						/*ventna rest room izquierda*/
						glPushMatrix();
							/*Primer ventana*/
							glTranslatef(-6, 0, -6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);						
							/*Segunda ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							/*Tercer ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						glPushMatrix();
							/*drs*/
							glTranslatef(-2.5, 0, 13.5);
							glColor3f(1, 1, 1);
							prisma(7, 12, 7, 0);
							glPushMatrix();
								/*managing director office*/
								glTranslatef(16.5, 0, 5.5);
								glColor3f(1,0,1);
								prisma(26, 12, 18, 0);
								/*Ventanas*/
								glPushMatrix();
									glTranslatef(-9, 0, 9);
									glColor3f(0.62, 0.92, 0.99);
									prisma(8, 6, 0.1, 0);
									glTranslatef(10, 0, 0);
									glColor3f(0.62, 0.92, 0.99);
									prisma(8, 6, 0.1, 0);
								glPopMatrix();
							glPopMatrix();
							/*bath*/
							glTranslatef(0, 0, 9);
							glColor3f(0, 1, 1);
							prisma(7, 12, 11, 0);
							/*ventana bath izquierda*/
							glPushMatrix();
								glTranslatef(-3.5, 0, 2);
								glColor3f(0.62, 0.92, 0.99);
								prisma(0.1, 6, 4, 0);
							glPopMatrix();
						glPopMatrix();

						/*supporting staff*/
						glTranslatef(11.5, 0, 0);
						glColor3f(0, 0, 1);
						prisma(11, 12, 20, 0);
					glPopMatrix();
				glPopMatrix();				
			glPopMatrix();			
		glPopMatrix();
		/***************************************
		*			Segundo piso
		***************************************/
		glPushMatrix();
			glTranslatef(0,24,0);
						/*Baño izquierda*/
			glColor3f(0,1,0);
			prisma(6, 12,10,1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);
			glPopMatrix();
			/*DRS izquierda*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			/*Oficina director izquierda*/
			glTranslatef(13, 0,-5);
			glColor3f(0, 0, 1);
			prisma(20, 12, 18, 0);						
			/*Ventana director izquierda*/
			glPushMatrix();
				glTranslatef(-4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);
			glPopMatrix();			
			/*Supporting staff office izquierda*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin izquierda*/
			glPushMatrix();
				glTranslatef(1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Supporting staff office derecha*/
			glTranslatef(12.5, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin derecha*/
			glPushMatrix();
				glTranslatef(-1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Director office derecha*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 12, 18, 0);
			/*Ventana director derecha*/
			glPushMatrix();
				glTranslatef(4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);
			glPopMatrix();			
			/*Bath derecha*/
			glTranslatef(13, 0, -4);
			glColor3f(0, 1, 0);
			prisma(6, 12, 10, 1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);
			glPopMatrix();
			/*DRS derecha*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			glPushMatrix();
				/*Director office derecha*/
				glTranslatef(-6, 0, 14);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);	
				/*Director office izquierda*/
				glTranslatef(-59, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);
				/*	Ventana oficiona director izquierda*/
				glPushMatrix();
					glTranslatef(-9,0,0);
					glColor3f(0.62,0.92,0.99);
					prisma(0.1,6,8,0);
					/*	Ventana oficiona director derecha*/
					glTranslatef(77, 0, 0);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 8, 0);
				glPopMatrix();		
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-6.25, 0, 15.5);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
						/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.75,0,1);
						glColor3f(0.62,0.92,0.99);
						prisma(0.1,6,4,0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();			
					/*staff office izquierdo*/
					glTranslatef(9, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*staff office derecho*/
					glTranslatef(53.5, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*bath derecho*/
					glTranslatef(9, 0, 0);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-7,0,23);
					glColor3f(1 ,0 ,1 );
					prisma(4, 12, 4, 0);
					glPushMatrix();
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2, 0, -0.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
						/*f.lavortry izquierdo*/
						glTranslatef(5, 0, 2);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*f.lavortry derecha*/
						glTranslatef(63, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*wc derecha*/
						glTranslatef(5, 0, -2);
						glColor3f(1, 0, 1);
						prisma(4, 12, 4, 0);
						/*wc derecha*/
						glTranslatef(0, 0, 4);
						glColor3f(0, 1, 1);
						prisma(4, 12, 4, 0);
					glPopMatrix();
					/*wc izquierda*/
					glTranslatef(0, 0, 4);
					glColor3f(0, 1, 1);
					prisma(4, 12, 4, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-6.5,0,30.5);
					glColor3f(1, 1, 1);
					prisma(5, 12, 3,0);
					glPushMatrix();
						/*m.lavortry izquierdo*/
						glTranslatef(5, 0, 7.5);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*m.lavortry derecho*/
						glTranslatef(62, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*wc derecho*/
						glTranslatef(5, 0, -7.5);
						glColor3f(1, 1, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 0, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 0, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 1);
						prisma(5, 12, 3, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 0, 0);
					prisma(5, 12, 3, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.5, 0, 2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana lado derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 0, 1);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 1);
					prisma(5, 12, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					/*dining hall*/
					glTranslatef(-4, 0, 59.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 25, 0);
					/*ventana dining hall*/
					glPushMatrix();
						glTranslatef(-5, 0, -2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*archive*/
					glTranslatef(67, 0, -7.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 10, 0);
					/*computer net room*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 0, 0);
					prisma(10, 12, 10, 0);
					/*telephone exchange*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 1, 0);
					prisma(10, 12, 10, 0);
					/*electric room*/
					glTranslatef(0, 0, 11);
					glColor3f(1, 1, 1);
					prisma(10, 12, 12, 0);
				glPopMatrix();
				glPushMatrix();
					/*kitchen*/
					glTranslatef(-4,0,80.5);
					glColor3f(1, 1, 1);
					prisma(10, 12, 17, 0);
					/*kitchen ventana*/
					glPushMatrix();
						glTranslatef(-5, 0, -3.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
					glPushMatrix();
						/*corridor izquierdo*/
						glColor3f(1, 0, 0);
						glTranslatef(9.5, 0, -22);
						prisma(9, 12, 59, 0);
						/*corridor derecho*/
						glColor3f(1, 0, 0);
						glTranslatef(48, 0, 0);
						prisma(9, 12, 59, 0);
					glPopMatrix();					
				glPopMatrix();				
			glPopMatrix();
			glPushMatrix();
				/*Corridor central*/
				glTranslatef(-36,-3, 110.5);
				glColor3f(0, 1, 0);
				prisma(69, 12, 15, 0);
				/*Ventanas corridor central*/
				glPushMatrix();
					/*Ventana izquierda*/
					glTranslatef(-34.5, 0, 3.75);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
					/*Ventana derecha*/
					glTranslatef(69, 0, -2.25);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7, 0);
				glPopMatrix();
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-32,0,12.5);
					glColor3f(1,1,0);
					prisma(5,12,10,0);
					/*Ventana izquierda*/
					glPushMatrix();
						glTranslatef(-2.5, 0, -1.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
						glPushMatrix();
							/*suporting izquierdo*/
							glTranslatef(8,0,0);
							glColor3f(1,0,1);
							prisma(12,12,10,0);
							/*suporting derecho*/
							glTranslatef(47.5, 0, 0);
							glColor3f(1, 0, 1);
							prisma(12, 12, 10, 0);
						glPopMatrix();
					/*bath derecho*/
					glTranslatef(64, 0, 0);
					glColor3f(1, 1, 0);
					prisma(5, 12, 10, 0);
					/*Ventana*/
					glPushMatrix();
						glTranslatef(2.5, 0, -3);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*senior manager office*/
						glTranslatef(-5,0,12);
						glColor3f(1, 1, 1);
						prisma(15, 12, 14, 0);	
						/*Ventana*/
						glPushMatrix();
							glTranslatef(7.5, 0, -2);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						/*Rojo grande*/
						glTranslatef(-10.5, 0, 27);
						glColor3f(1, 0, 0);
						prisma(36, 12, 40, 0);
						/*arriba*/
						glTranslated(0, 6.75, 19.25);
						glColor3f(0, 0, 0.54);						
						prisma(36, 1.5, 1.5, 1);
						glTranslatef(17.25, 0, -20);
						prisma(1.5, 1.5, 38.5, 1);
					glPopMatrix();
				glPopMatrix();
				/*falta agregar a la oficina del direct un cuadrito D:*/
				glPushMatrix();
					glTranslatef(-23,0,24.5);
					glColor3f(0, 1, 1);
					prisma(23, 12, 14, 0);
					/*Ventana izquierda*/
					glPushMatrix();	
						/*Primer ventana*/
						glTranslatef(-11.5, 0, -2);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
						/*Segunda ventana*/
						glTranslatef(0, 0, 7);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*rest room*/
						glTranslatef(-5.5, 0, 17);
						glColor3f(1, 0, 0);
						prisma(12, 12, 20, 0);
						/*ventna rest room izquierda*/
						glPushMatrix();
							/*Primer ventana*/
							glTranslatef(-6, 0, -6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);						
							/*Segunda ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							/*Tercer ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						glPushMatrix();
							/*drs*/
							glTranslatef(-2.5, 0, 13.5);
							glColor3f(1, 1, 1);
							prisma(7, 12, 7, 0);
							glPushMatrix();
								/*managing director office*/
								glTranslatef(16.5, 0, 5.5);
								glColor3f(1,0,1);
								prisma(26, 12, 18, 0);
								/*Ventanas*/
								glPushMatrix();
									glTranslatef(-9, 0, 9);
									glColor3f(0.62, 0.92, 0.99);
									prisma(8, 6, 0.1, 0);
									glTranslatef(10, 0, 0);
									glColor3f(0.62, 0.92, 0.99);
									prisma(8, 6, 0.1, 0);
								glPopMatrix();
							glPopMatrix();
							/*bath*/
							glTranslatef(0, 0, 9);
							glColor3f(0, 1, 1);
							prisma(7, 12, 11, 0);
							/*ventana bath izquierda*/
							glPushMatrix();
								glTranslatef(-3.5, 0, 2);
								glColor3f(0.62, 0.92, 0.99);
								prisma(0.1, 6, 4, 0);
							glPopMatrix();
						glPopMatrix();

						/*supporting staff*/
						glTranslatef(11.5, 0, 0);
						glColor3f(0, 0, 1);
						prisma(11, 12, 20, 0);
					glPopMatrix();
				glPopMatrix();				
			glPopMatrix();			
		glPopMatrix();
		/***************************************
		*			Tercer Piso 
		***************************************/
		glPushMatrix();
			glTranslatef(0, 36, 0);
			/*Baño izquierda*/
			glColor3f(0,1,0);
			prisma(6, 12,10,1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);				
			glPopMatrix();
			/*DRS izquierda*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			/*Oficina director izquierda*/
			glTranslatef(13, 0,-5);
			glColor3f(0, 0, 1);
			prisma(20, 12, 18, 0);						
			/*Ventana director izquierda*/
			glPushMatrix();
				glTranslatef(-4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);				
			glPopMatrix();			
			/*Supporting staff office izquierda*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin izquierda*/
			glPushMatrix();
				glTranslatef(1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Supporting staff office derecha*/
			glTranslatef(12.5, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin derecha*/
			glPushMatrix();
				glTranslatef(-1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Director office derecha*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 12, 18, 0);
			/*Ventana director derecha*/
			glPushMatrix();
				glTranslatef(4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);				
			glPopMatrix();			
			/*Bath derecha*/
			glTranslatef(13, 0, -4);
			glColor3f(0, 1, 0);
			prisma(6, 12, 10, 1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);
			glPopMatrix();
			/*DRS derecha*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			glPushMatrix();
				/*Director office derecha*/
				glTranslatef(-6, 0, 14);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);	
				/*Director office izquierda*/
				glTranslatef(-59, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);				
				/*	Ventana oficiona director izquierda*/
				glPushMatrix();
					glTranslatef(-9,0,0);
					glColor3f(0.62,0.92,0.99);
					prisma(0.1,6,8,0);
					/*	Ventana oficiona director derecha*/
					glTranslatef(77, 0, 0);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 8, 0);
				glPopMatrix();		
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-6.25, 0, 15.5);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.75,0,1);
						glColor3f(0.62,0.92,0.99);
						prisma(0.1,6,4,0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();			
					/*staff office izquierdo*/
					glTranslatef(9, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*staff office derecho*/
					glTranslatef(53.5, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*bath derecho*/
					glTranslatef(9, 0, 0);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-7,0,23);
					glColor3f(1 ,0 ,1 );
					prisma(4, 12, 4, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2, 0, -0.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
					glPushMatrix();
						/*f.lavortry izquierdo*/
						glTranslatef(5, 0, 2);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*f.lavortry derecha*/
						glTranslatef(63, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*wc derecha*/
						glTranslatef(5, 0, -2);
						glColor3f(1, 0, 1);
						prisma(4, 12, 4, 0);
						/*wc derecha*/
						glTranslatef(0, 0, 4);
						glColor3f(0, 1, 1);
						prisma(4, 12, 4, 0);
					glPopMatrix();
					/*wc izquierda*/
					glTranslatef(0, 0, 4);
					glColor3f(0, 1, 1);
					prisma(4, 12, 4, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-6.5,0,30.5);
					glColor3f(1, 1, 1);
					prisma(5, 12, 3,0);
					glPushMatrix();
						/*m.lavortry izquierdo*/
						glTranslatef(5, 0, 7.5);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*m.lavortry derecho*/
						glTranslatef(62, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*wc derecho*/
						glTranslatef(5, 0, -7.5);
						glColor3f(1, 1, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 0, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 0, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 1);
						prisma(5, 12, 3, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 0, 0);
					prisma(5, 12, 3, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.5, 0, 2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana lado derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 0, 1);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 1);
					prisma(5, 12, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					/*dining hall*/
					glTranslatef(-4, 0, 59.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 25, 0);
					/*ventana dining hall*/
					glPushMatrix();
						glTranslatef(-5, 0, -2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*archive*/
					glTranslatef(67, 0, -7.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 10, 0);
					/*computer net room*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 0, 0);
					prisma(10, 12, 10, 0);
					/*telephone exchange*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 1, 0);
					prisma(10, 12, 10, 0);
					/*electric room*/
					glTranslatef(0, 0, 11);
					glColor3f(1, 1, 1);
					prisma(10, 12, 12, 0);
				glPopMatrix();
				glPushMatrix();
					/*kitchen*/
					glTranslatef(-4,0,80.5);
					glColor3f(1, 1, 1);
					prisma(10, 12, 17, 0);
					/*kitchen ventana*/
					glPushMatrix();
						glTranslatef(-5, 0, -3.5); 
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
					glPushMatrix();
						/*corridor izquierdo*/
						glColor3f(1, 0, 0);
						glTranslatef(9.5, 0, -22);
						prisma(9, 12, 59, 0);
						/*corridor derecho*/
						glColor3f(1, 0, 0);
						glTranslatef(48, 0, 0);
						prisma(9, 12, 59, 0);
					glPopMatrix();					
				glPopMatrix();				
			glPopMatrix();
			glPushMatrix();
				/*Corridor central*/
				glTranslatef(-36,-3, 110.5);
				glColor3f(0, 1, 0);
				prisma(69, 12, 15, 0);
				/*Ventanas corridor central*/
				glPushMatrix();
					/*Ventana izquierda*/
					glTranslatef(-34.5, 0, 3.75);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
					/*Ventana derecha*/
					glTranslatef(69, 0, -2.25);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7, 0);
				glPopMatrix();
				glPushMatrix();				
					/*bath izquierdo*/
					glTranslatef(-32,0,12.5);
					glColor3f(1,1,0);
					prisma(5,12,10,0);
					/*Ventana izquierda*/
					glPushMatrix();
						glTranslatef(-2.5, 0, -1.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
						glPushMatrix();
							/*suporting izquierdo*/
							glTranslatef(8,0,0);
							glColor3f(1,0,1);
							prisma(12,12,10,0);
							/*suporting derecho*/
							glTranslatef(47.5, 0, 0);
							glColor3f(1, 0, 1);
							prisma(12, 12, 10, 0);
						glPopMatrix();
					/*bath derecho*/
					glTranslatef(64, 0, 0);
					glColor3f(1, 1, 0);
					prisma(5, 12, 10, 0);
					/*Ventana*/
					glPushMatrix();
						glTranslatef(2.5, 0, -3);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*Director office*/
						glTranslatef(-8.5,0,12);
						glColor3f(1, 1, 1);
						prisma(22, 12, 14, 0);						
							/*Ventana*/
						glPushMatrix();
							glTranslatef(11, 0, -2);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						/**/
						glTranslatef(-3.75, 0, 12.75);
						glColor3f(1, 0, 0);
						prisma(0.1, 12, 11.5, 0);
						/*Ventana*/
						glTranslatef(0, 1, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.12, 6, 11.5, 0);						
					glPopMatrix();
				glPopMatrix();
				/*falta agregar a la oficina del direct un cuadrito D:*/
				glPushMatrix();
					glTranslatef(-23,0,24.5);
					glColor3f(0, 1, 1);
					prisma(23, 12, 14, 0);
					/*Ventana izquierda*/
					glPushMatrix();	
						/*Primer ventana*/
						glTranslatef(-11.5, 0, -2);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
						/*Segunda ventana*/
						glTranslatef(0, 0, 7);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*rest room izquierda*/
						glTranslatef(-5.5, 0, 17);
						glColor3f(1, 0, 0);
						prisma(12, 12, 20, 0);
						/*ventna rest room izquierda*/
						glPushMatrix();
							/*Primer ventana*/
							glTranslatef(-6, 0, -6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);						
							/*Segunda ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							/*Tercer ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						glPushMatrix();
							/*drs izquierda*/
							glTranslatef(-2.5, 0, 13.5);
							glColor3f(1, 1, 1);
							prisma(7, 12, 7, 0);
							glPushMatrix();
								/*managing director office de izquierda*/
								glTranslatef(16.5, 0, 5.5);
								glColor3f(1,0,1);
								prisma(26, 12, 18, 0); 
								/*Cuadro saliente*/
								glPushMatrix();
									glTranslatef(11,0,7.1);
									glColor3f(1, 1, 1);
									prisma(8, 12, 8, 0);
									glTranslatef(0, 0, 3.7);
									glColor3f(0.62, 0.92, 0.99);
									prisma(7.98, 6, 0.62, 0);
									glTranslatef(3.7, 0, -3.99);
									glColor3f(0.62, 0.92, 0.99);
									prisma(0.62, 6, 7.98, 0);
								glPopMatrix();
								/**/
								glTranslatef(18.75, 0, -9);
								glColor3f(1, 0, 0);
								prisma(11.5, 12, 0.1, 0);
								/*Ventana*/
								glTranslatef(0, 1, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(11.5, 6, 0.12, 0);
								/*Central, puerta*/
								//glRotatef(45, 0, 1, 0);
								glTranslatef(10.6, -1, -4.25);
								glRotatef(41, 0, 1, 0);
								glColor3f(1, 1, 0);
								prisma(13, 12, 0.1, 0);
								/*Puerta*/
								glTranslatef(0, -1, 0);
								glColor3f(1,1,1);
								prisma(7,10,0.12,0);
								/*Ventana*/
								glTranslatef(-5, 2, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(3, 6, 0.12, 0);
								glTranslatef(10, 0, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(3, 6, 0.12, 0);
							glPopMatrix();
							/*bath izquierda*/
							glTranslatef(0, 0, 9);
							glColor3f(0, 1, 1);
							prisma(7, 12, 11, 0);
							/*ventana bath izquierda*/
							glPushMatrix();
								glTranslatef(-3.5, 0, 2);
								glColor3f(0.62, 0.92, 0.99);
								prisma(0.1, 6, 4, 0);
							glPopMatrix();
						glPopMatrix();
						/*supporting staff*/
						glTranslatef(11.5, 0, 0);
						glColor3f(0, 0, 1);
						prisma(11, 12, 20, 0);
					glPopMatrix();
				glPopMatrix();				
			glPopMatrix();			
		glPopMatrix();
		/***************************************
		*			Cuarto Piso
		***************************************/
		glPushMatrix();
			glTranslatef(0, 48, 0);
			/*Baño izquierda*/
			glColor3f(0,1,0);
			prisma(6, 12,10,1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);
				prisma(3,6,0.1,0);	
				/*Ventana piso arriba*/
				glTranslatef(0,12,0);
				prisma(3, 6, 0.1, 0);
			glPopMatrix();
			/*DRS izquierda*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			/*Oficina director izquierda*/
			glTranslatef(13, 0,-5);
			glColor3f(0, 0, 1);
			prisma(20, 12, 18, 0);						
			/*Ventana director izquierda*/
			glPushMatrix();
				glTranslatef(-4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6, 6, 0.1, 0);
				/*ventana piso arriba*/
				glTranslatef(0, 12, 0);
				prisma(6, 6, 0.1, 0);
			glPopMatrix();			
			/*Supporting staff office izquierda*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 1, 0);
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin izquierda*/
			glPushMatrix();
				glTranslatef(1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7, 6, 0.1, 0);
				/*ventana piso arriba*/
				glTranslatef(0, 12, 0);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Supporting staff office derecha*/
			glTranslatef(12.5, 0, 0);
			glColor3f(0, 1, 1);			
			prisma(12.5, 12, 18, 0);
			/*Ventana supportin derecha*/
			glPushMatrix();
				glTranslatef(-1,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(7, 6, 0.1, 0);
				/*ventana piso arriba*/
				glTranslatef(0, 12, 0);
				prisma(7,6,0.1,0);
			glPopMatrix();
			/*Director office derecha*/
			glTranslatef(16.25, 0, 0);
			glColor3f(1, 0, 1);
			prisma(20, 12, 18, 0);
			/*Ventana director derecha*/
			glPushMatrix();
				glTranslatef(4,1,-9);
				glColor3f(0.62,0.92,0.99);
				prisma(6,6,0.1,0);	
				/*ventana piso arriba*/
				glTranslatef(0, 12, 0);
				prisma(6, 6, 0.1, 0);
			glPopMatrix();			
			/*Bath derecha*/
			glTranslatef(13, 0, -4);
			glColor3f(0, 1, 0);
			prisma(6, 12, 10, 1);
			/*Ventana baño*/
			glPushMatrix();
				glTranslatef(0,1,-5);
				glColor3f(0.62,0.92,0.99);				
				prisma(3,6,0.1,0);
				/*Ventana piso arriba*/
				glTranslatef(0, 12, 0);
				prisma(3, 6, 0.1, 0);
			glPopMatrix();
			/*DRS derecha*/
			glTranslatef(0, 0, 9);
			glColor3f(1, 0, 0);
			prisma(6, 12, 8, 1);
			glPushMatrix();
				/*Director office derecha*/
				glTranslatef(-6, 0, 14);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);	
				/*Director office izquierda*/
				glTranslatef(-59, 0, 0);
				glColor3f(0, 1, 0);
				prisma(18, 12, 20, 1);				
				/*	Ventana oficiona director izquierda*/
				glPushMatrix();
					glTranslatef(-9,0,0);
					glColor3f(0.62,0.92,0.99);
					prisma(0.1,6,8,0);
					/*ventana piso arriba*/
					glPushMatrix();
						glTranslatef(0, 12, 0);
						prisma(0.1, 6, 8, 0);
					glPopMatrix();
					/*	Ventana oficiona director derecha*/
					glTranslatef(77, 0, 0);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 8, 0);
					/*Ventana piso arriba*/
					glTranslatef(0, 12, 0);
					prisma(0.1, 6, 8, 0);
				glPopMatrix();		
				glPushMatrix();
					/*bath izquierdo*/
					glTranslatef(-6.25, 0, 15.5);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.75,0,1);
						glColor3f(0.62,0.92,0.99);
						prisma(0.1,6,4,0);
						glPushMatrix();
							/*Ventana piso arriba*/
							glTranslatef(0, 12, 0);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
						/*Ventana piso arriba*/
						glTranslatef(0, 12, 0);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();			
					/*staff office izquierdo*/
					glTranslatef(9, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*staff office derecho*/
					glTranslatef(53.5, 0, 0);
					glColor3f(0, 0, 1);
					prisma(12.5, 12, 11, 0);
					/*bath derecho*/
					glTranslatef(9, 0, 0);
					glColor3f(1, 0, 0);
					prisma(5.5, 12, 11, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-7,0,23);
					glColor3f(1 ,0 ,1 );
					prisma(4, 12, 4, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2, 0, -0.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);						
						/*Ventana piso arriba*/
						glPushMatrix();
							glTranslatef(0, 12, 0);
							prisma(0.1, 6, 3, 0);
						glPopMatrix();
						/*Ventana bath derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
						/*Ventana piso arriba*/
						glPushMatrix();
							glTranslatef(0, 12, 0);
							prisma(0.1, 6, 3, 0);
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();
						/*f.lavortry izquierdo*/
						glTranslatef(5, 0, 2);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*f.lavortry derecha*/
						glTranslatef(63, 0, 0);
						glColor3f(1, 0, 0);
						prisma(6, 12, 8, 0);
						/*wc derecha*/
						glTranslatef(5, 0, -2);
						glColor3f(1, 0, 1);
						prisma(4, 12, 4, 0);
						/*wc derecha*/
						glTranslatef(0, 0, 4);
						glColor3f(0, 1, 1);
						prisma(4, 12, 4, 0);
					glPopMatrix();
					/*wc izquierda*/
					glTranslatef(0, 0, 4);
					glColor3f(0, 1, 1);
					prisma(4, 12, 4, 0);
				glPopMatrix();
				glPushMatrix();
					/*wc izquierdo*/
					glTranslatef(-6.5,0,30.5);
					glColor3f(1, 1, 1);
					prisma(5, 12, 3,0);
					glPushMatrix();
						/*m.lavortry izquierdo*/
						glTranslatef(5, 0, 7.5);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*m.lavortry derecho*/
						glTranslatef(62, 0, 0);
						glColor3f(1, 1, 0);
						prisma(5, 12, 18, 0);
						/*wc derecho*/
						glTranslatef(5, 0, -7.5);
						glColor3f(1, 1, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 0, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 0, 1);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(1, 1, 0);
						prisma(5, 12, 3, 0);
						/*wc derecho*/
						glTranslatef(0, 0, 3);
						glColor3f(0, 1, 1);
						prisma(5, 12, 3, 0);
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 0, 0);
					prisma(5, 12, 3, 0);
					/*Ventana bath izquierdo*/
					glPushMatrix();
						glTranslatef(-2.5, 0, 2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana piso arriba*/
						glPushMatrix();
							glTranslatef(0, 12, 0);
							prisma(0.1, 6, 7.5, 0);
						glPopMatrix();
						/*Ventana lado derecho*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						glPushMatrix();
							glTranslatef(0, 12, 0);
							prisma(0.1, 6, 7.5, 0);
						glPopMatrix();
					glPopMatrix();
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 0, 1);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc izquierdo*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 1);
					prisma(5, 12, 3, 0);
				glPopMatrix();			
				glPushMatrix();
					/*dining hall*/
					glTranslatef(-4, 0, 59.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 25, 0);
					/*ventana dining hall*/
					glPushMatrix();
						glTranslatef(-5, 0, -2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
					glPopMatrix();
					/*archive*/
					glTranslatef(67, 0, -7.5);
					glColor3f(1, 0, 1);
					prisma(10, 12, 10, 0);
					/*computer net room*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 0, 0);
					prisma(10, 12, 10, 0);
					/*telephone exchange*/
					glTranslatef(0, 0, 10);
					glColor3f(1, 1, 0);
					prisma(10, 12, 10, 0);
					/*electric room*/
					glTranslatef(0, 0, 11);
					glColor3f(1, 1, 1);
					prisma(10, 12, 12, 0);
				glPopMatrix();
				glPushMatrix();
					/*kitchen*/
					glTranslatef(-4,0,80.5);
					glColor3f(1, 1, 1);
					prisma(10, 12, 17, 0);
					/*kitchen ventana*/
					glPushMatrix();
						glTranslatef(-5, 0, -3.5); 
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
					glPushMatrix();
						/*corridor izquierdo*/
						glColor3f(1, 0, 0);
						glTranslatef(9.5, 0, -22);
						prisma(9, 12, 59, 0);
						/*corridor derecho*/
						glColor3f(1, 0, 0);
						glTranslatef(48, 0, 0);
						prisma(9, 12, 59, 0);
					glPopMatrix();					
				glPopMatrix();				
			glPopMatrix();
			glPushMatrix();
				/*Corridor central*/
				glTranslatef(-36,-3, 110.5);
				glColor3f(0, 1, 0);
				prisma(69, 12, 15, 0);
				/*Ventanas corridor central*/
				glPushMatrix();
					/*Ventana izquierda*/
					glTranslatef(-34.5, 0, 3.75);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
					/*Ventana derecha*/
					glTranslatef(69, 0, -2.25);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7, 0);
				glPopMatrix();
				glPushMatrix();				
					/*bath izquierdo*/
					glTranslatef(-32,0,12.5);
					glColor3f(1,1,0);
					prisma(5,12,10,0);
					/*Ventana izquierda*/
					glPushMatrix();
						glTranslatef(-2.5, 0, -1.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 3, 0);
					glPopMatrix();
						glPushMatrix();
							/*suporting izquierdo*/
							glTranslatef(8,0,0);
							glColor3f(1,0,1);
							prisma(12,12,10,0);
							/*suporting derecho*/
							glTranslatef(47.5, 0, 0);
							glColor3f(1, 0, 1);
							prisma(12, 12, 10, 0);
						glPopMatrix();
					/*bath derecho*/
					glTranslatef(64, 0, 0);
					glColor3f(1, 1, 0);
					prisma(5, 12, 10, 0);
					/*Ventana*/
					glPushMatrix();
						glTranslatef(2.5, 0, -3);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*director office*/
						glTranslatef(-8.5,0,12);
						glColor3f(1, 1, 1);
						prisma(22, 12, 14, 0);
							/*Ventana*/
						glPushMatrix();
							glTranslatef(11, 0, -2);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						/**/
						glTranslatef(-3.75, 0, 12.75);
						glColor3f(1, 0, 0);
						prisma(0.1, 12, 11.5, 0);						
						/*Ventana*/
						glTranslatef(0, 1, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.12, 6, 11.5, 0);						
					glPopMatrix();
				glPopMatrix();
				/*falta agregar a la oficina del direct un cuadrito D:*/
				glPushMatrix();
					glTranslatef(-23,0,24.5);
					glColor3f(0, 1, 1);
					prisma(23, 12, 14, 0);
					/*Ventana izquierda*/
					glPushMatrix();	
						/*Primer ventana*/
						glTranslatef(-11.5, 0, -2);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
						/*Segunda ventana*/
						glTranslatef(0, 0, 7);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 4, 0);
					glPopMatrix();
					glPushMatrix();
						/*rest room izquierda*/
						glTranslatef(-5.5, 0, 17);
						glColor3f(1, 0, 0);
						prisma(12, 12, 20, 0);
						/*ventna rest room izquierda*/
						glPushMatrix();
							/*Primer ventana*/
							glTranslatef(-6, 0, -6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);						
							/*Segunda ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
							/*Tercer ventana*/
							glTranslatef(0, 0, 6);
							glColor3f(0.62, 0.92, 0.99);
							prisma(0.1, 6, 4, 0);
						glPopMatrix();
						glPushMatrix();
							/*drs izquierda*/
							glTranslatef(-2.5, 0, 13.5);
							glColor3f(1, 1, 1);
							prisma(7, 12, 7, 0);
							glPushMatrix();
								/*managing director office de izquierda*/
								glTranslatef(16.5, 0, 5.5);
								glColor3f(1,0,1);
								prisma(26, 12, 18, 0);
								glPushMatrix();
									glTranslatef(11,0,7.1);
									glColor3f(1, 1, 1);
									prisma(8, 12, 8, 0);
									glTranslatef(0, 0, 3.7);
									glColor3f(0.62, 0.92, 0.99);
									prisma(7.98, 6, 0.62, 0);
									glTranslatef(3.7, 0, -3.99);
									glColor3f(0.62, 0.92, 0.99);
									prisma(0.62, 6, 7.98, 0);
								glPopMatrix();
								glPushMatrix();
									glTranslatef(18.75, 12, -9);
									glColor3f(1, 0, 0);
									prisma(11.5, 12, 0.1, 0);
									/*Ventana*/
									glTranslatef(0, 1, 0);
									glColor3f(0.62, 0.92, 0.99);
									prisma(11.5, 6, 0.12, 0);
									/*Central, puerta*/								
									//glRotatef(45, 0, 1, 0);
									glTranslatef(10.6, -1, -4.25);								
									glRotatef(41, 0, 1, 0);
									glColor3f(1, 1, 0);							
									prisma(13, 12, 0.1, 0);								
									/*Ventana*/								
									glTranslatef(0, 1, 0);
									glColor3f(0.62, 0.92, 0.99);
									prisma(13, 6, 0.12, 0);		
								glPopMatrix();
								/**/
								glTranslatef(18.75, 0, -9);
								glColor3f(1, 0, 0);
								prisma(11.5, 12, 0.1, 0);								
								/*Ventana*/
								glTranslatef(0, 1, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(11.5, 6, 0.12, 0);								
								/*Central, puerta*/								
								//glRotatef(45, 0, 1, 0);
								glTranslatef(10.6, -1, -4.25);								
								glRotatef(41, 0, 1, 0);
								glColor3f(1, 1, 0);							
								prisma(13, 12, 0.1, 0);								
								/*Ventana*/								
								glTranslatef(0, 1, 0);
								glColor3f(0.62, 0.92, 0.99);
								prisma(13, 6, 0.12, 0);		
							glPopMatrix();
							/*bath izquierda*/
							glTranslatef(0, 0, 9);
							glColor3f(0, 1, 1);
							prisma(7, 12, 11, 0);
							/*ventana bath izquierda*/
							glPushMatrix();
								glTranslatef(-3.5, 0, 2);
								glColor3f(0.62, 0.92, 0.99);
								prisma(0.1, 6, 4, 0);
							glPopMatrix();
						glPopMatrix();
						/*supporting staff*/
						glTranslatef(11.5, 0, 0);
						glColor3f(0, 0, 1);
						prisma(11, 12, 20, 0);
					glPopMatrix();
				glPopMatrix();				
			glPopMatrix();			
		glPopMatrix();
		/***************************************
		*				Techo
		***************************************/
		glPushMatrix();			
			glTranslatef(-1.5, 67.5, 53.5);
			glColor3f(0,0,0.54);
			prisma(3, 3,117,1);
			glPushMatrix();
				glTranslatef(38,-1.45,-30);
				glColor3f(0,1,1);
				prisma(75, 0.1,57,1);
				glTranslatef(-28.5, 0, 58.5);
				glColor3f(0, 1, 1);
				prisma(16, 0.1, 60, 1);
				glTranslatef(55, 0, 0);
				glColor3f(0, 1, 1);
				prisma(16, 0.1, 60, 1);
			glPopMatrix();
			glTranslatef(74, 0, 0);
			glColor3f(0, 0, 0.54);
			prisma(3, 3, 117, 0);
			glTranslatef(-37, 0, -57);
			glColor3f(0, 0, 0.54);
			prisma(76, 3, 3, 0);
			glTranslatef(-33.5, -3, 154);
			glColor3f(0, 0, 0.54);
			prisma(3, 3, 76, 0);
			glTranslatef(13.25, 0, 37);
			glColor3f(0, 0, 0.54);
			prisma(29.5, 3, 3, 0);
			glTranslatef(13.75, 0, 1.125);
			glColor3f(0, 0, 0.54);
			prisma(3, 3, 5.25, 0);
			glTranslatef(3.75, 0, 1.125);
			glColor3f(0, 0, 0.54);
			prisma(5, 3, 3, 0);
			glTranslatef(1.125, 0, -3.75);
			glColor3f(0, 0, 0.54);
			prisma(3, 3, 5, 0);
		glPopMatrix();
		/***********************************
		*			Quinto Piso
		***********************************/
		glPushMatrix();
			glTranslatef(35.5, 60, 19.5);
			glColor3f(1, 1, 1);
			prisma(77, 12, 49, 0);
			/*Ventanas*/
			glPushMatrix();

			glPopMatrix();
			glPushMatrix();
				/*wc izquierdo*/
				glTranslatef(-36.5,0,26.5);
				glColor3f(1 ,0 ,1 );
				prisma(4, 12, 4, 0);
				glPushMatrix();
					/*f.lavortry izquierdo*/
					glTranslatef(5, 0, 2);
					glColor3f(1, 0, 0);
					prisma(6, 12, 8, 0);
					/*f.lavortry derecha*/
					glTranslatef(63, 0, 0);
					glColor3f(1, 0, 0);
					prisma(6, 12, 8, 0);
					/*wc derecha*/
					glTranslatef(5, 0, -2);
					glColor3f(1, 0, 1);
					prisma(4, 12, 4, 0);
					/*wc derecha*/
					glTranslatef(0, 0, 4);
					glColor3f(0, 1, 1);
					prisma(4, 12, 4, 0);
				glPopMatrix();
				/*wc izquierda*/
				glTranslatef(0, 0, 4);
				glColor3f(0, 1, 1);
				prisma(4, 12, 4, 0);
			glPopMatrix();
			glPushMatrix();
				/*wc izquierdo*/
				glTranslatef(-36,0,34);
				glColor3f(1, 1, 1);
				prisma(5, 12, 3,0);
				glPushMatrix();
					/*m.lavortry izquierdo*/
					glTranslatef(5, 0, 7.5);
					glColor3f(1, 1, 0);
					prisma(5, 12, 18, 0);
					/*m.lavortry derecho*/
					glTranslatef(62, 0, 0);
					glColor3f(1, 1, 0);
					prisma(5, 12, 18, 0);
					/*wc derecho*/
					glTranslatef(5, 0, -7.5);
					glColor3f(1, 1, 1);
					prisma(5, 12, 3, 0);
					/*wc derecho*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc derecho*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 0, 0);
					prisma(5, 12, 3, 0);
					/*wc derecho*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 0, 1);
					prisma(5, 12, 3, 0);
					/*wc derecho*/
					glTranslatef(0, 0, 3);
					glColor3f(1, 1, 0);
					prisma(5, 12, 3, 0);
					/*wc derecho*/
					glTranslatef(0, 0, 3);
					glColor3f(0, 1, 1);
					prisma(5, 12, 3, 0);
				glPopMatrix();
				/*wc izquierdo*/
				glTranslatef(0, 0, 3);
				glColor3f(0, 1, 0);
				prisma(5, 12, 3, 0);
				/*wc izquierdo*/
				glTranslatef(0, 0, 3);
				glColor3f(1, 0, 0);
				prisma(5, 12, 3, 0);
				/*wc izquierdo*/
				glTranslatef(0, 0, 3);
				glColor3f(0, 0, 1);
				prisma(5, 12, 3, 0);
				/*wc izquierdo*/
				glTranslatef(0, 0, 3);
				glColor3f(1, 1, 0);
				prisma(5, 12, 3, 0);
				/*wc izquierdo*/
				glTranslatef(0, 0, 3);
				glColor3f(0, 1, 1);
				prisma(5, 12, 3, 0);
			glPopMatrix();			
			glPushMatrix();
				/*dining hall*/
				glTranslatef(-33.5, 0, 63);
				glColor3f(1, 0, 1);
				prisma(10, 12, 25, 0);
				/*ventana dining hall*/
				glPushMatrix();
					glTranslatef(-5, 0, -2.25);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
					/*Ventana derecha*/
					glTranslatef(77, 0, 0);
					glColor3f(0.62, 0.92, 0.99);
					prisma(0.1, 6, 7.5, 0);
				glPopMatrix();
				/*archive*/
				glTranslatef(67, 0, -7.5);
				glColor3f(1, 0, 1);
				prisma(10, 12, 10, 0);
				/*computer net room*/
				glTranslatef(0, 0, 10);
				glColor3f(1, 0, 0);
				prisma(10, 12, 10, 0);
				/*telephone exchange*/
				glTranslatef(0, 0, 10);
				glColor3f(1, 1, 0);
				prisma(10, 12, 10, 0);
				/*electric room*/
				glTranslatef(0, 0, 11);
				glColor3f(1, 1, 1);
				prisma(10, 12, 12, 0);
			glPopMatrix();
			glPushMatrix();
				/*kitchen*/
				glTranslatef(-33.5,0,84);
				glColor3f(1, 1, 1);
				prisma(10, 12, 17, 0);
				/*kitchen ventana*/
					glPushMatrix();
						glTranslatef(-5, 0, -3.5);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
						/*Ventana derecha*/
						glTranslatef(77, 0, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
				glPushMatrix();
				/*corridor izquierdo*/
					glColor3f(1, 0, 0);
					glTranslatef(9.5, 0, -22);
					prisma(9, 12, 59, 0);
					/*corridor derecho*/
					glColor3f(1, 0, 0);
					glTranslatef(48, 0, 0);
					prisma(9, 12, 59, 0);
				glPopMatrix();					
				glPopMatrix();				
				glPushMatrix();
					/*Corridor central*/
					glTranslatef(-0.5, -3, 100);
					glColor3f(0, 1, 0);
					prisma(69, 12, 15, 0);					
					/*Ventanas corridor central*/
					glPushMatrix();
						/*Ventana izquierda*/
						glTranslatef(-34.5, 0, 3.75);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7.5, 0);
						/*Ventana derecha*/
						glTranslatef(34.5, 0, -2.25);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.1, 6, 7, 0);
					glPopMatrix();
					glPushMatrix();
						/*depports managers office izquierda*/
						glTranslatef(-23,0,13.5);
						glColor3f(1,1,1);
						prisma(23, 12, 12, 0);						
						/*depports managers office derecha*/
						glTranslatef(46.5, 0, 0);
						glColor3f(1, 1, 1);
						prisma(22, 12, 12, 0);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-23, 0, 25.5);
						glColor3f(1, 1, 0);
						prisma(23,12,12,0);
						glPushMatrix();
							glTranslatef(0, 0, 12);
							glColor3f(1, 0, 1);
							prisma(23, 12, 12, 0);
							glTranslatef(0, 0, 12.5);
							glColor3f(0, 0, 1);
							prisma(23, 12, 13, 0);
							glTranslatef(5, 0, 13);
							glColor3f(1, 0, 1);
							prisma(33, 12, 13, 0);
							glPushMatrix();
								glTranslatef(14.5,0,4.6);
								glColor3f(1, 1, 1);
								prisma(8, 12, 8, 0);
								glTranslatef(0, 0, 3.7);
								glColor3f(0.62, 0.92, 0.99);
								prisma(7.98, 6, 0.62, 0);
								glTranslatef(3.7, 0, -3.99);
								glColor3f(0.62, 0.92, 0.99);
								prisma(0.62, 6, 7.98, 0);
							glPopMatrix();
							//adele
						glPopMatrix();
						/*deputy manager office*/
						glTranslatef(46.5, 0, 0);
						glColor3f(1, 1, 0);
						prisma(22, 12, 12, 0);
						/**/
						glTranslatef(-3.75, 0, 11.75);
						glColor3f(1, 0, 0);
						prisma(0.1, 12, 11.5, 0);
						/*Ventana*/
						glTranslatef(0, 1, 0);
						glColor3f(0.62, 0.92, 0.99);
						prisma(0.12, 6, 11.5, 0);
					glPopMatrix();
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




