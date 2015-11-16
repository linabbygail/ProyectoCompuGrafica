#pragma once
#include "Main.h"

class CItem
{
public:

	//figures
	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text);
	void cilindro(float radio, float altura, int resolucion, GLuint text);
	void cono(float altura, float radio, int resolucion, GLuint text);

	//items
	void mueble(float altura, float largo, float profundidad, GLuint text, GLuint ladrillo);
	void mueble2(float altura, float largo, float profundidad, GLuint text);
	void estufa(float altura, float largo, float profundidad, GLuint text, GLuint text2);
	void hoya(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void maseta(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void tecla(float altura, float largo, float profundidad, GLuint text);

};