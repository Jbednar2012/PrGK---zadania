#pragma once
#include <GL/glut.h>

typedef enum {WHITE=0, LIGHT_GRAY, DARK_GRAY, BLACK, RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA} color;
typedef enum {SPHERE=0, CUBE, CONE, TORUS, TEAPOT} shape;

color currentColor = WHITE;
shape currentShape = SPHERE;
bool wire;

void colorize() {
	switch (currentColor) {
	case WHITE:		glColor3f(1.0, 1.0, 1.0); break;
	case LIGHT_GRAY:glColor3f(0.7, 0.7, 0.7); break;
	case DARK_GRAY:	glColor3f(0.3, 0.3, 0.3); break;
	case BLACK:		glColor3f(0.0, 0.0, 0.0); break;
	case RED:		glColor3f(1.0, 0.0, 0.0); break;
	case YELLOW:	glColor3f(1.0, 1.0, 0.0); break;
	case GREEN:		glColor3f(0.0, 1.0, 0.0); break;
	case CYAN:		glColor3f(0.0, 1.0, 1.0); break;
	case BLUE:		glColor3f(0.0, 0.0, 1.0); break;
	case MAGENTA:	glColor3f(1.0, 0.0, 1.0); break;
	}
}

void draw() {
	switch (currentShape) {
	case SPHERE:	if (wire)
						glutWireSphere(90, 30, 30);
					else glutSolidSphere(90, 30, 30);
					break;
	case CUBE:		if (wire)
					glutWireCube(90);
						else glutSolidCube(90);
					break;
	case CONE:		if (wire)
						glutWireCone(60,90,30,30);
					else glutSolidCone(60, 90, 30, 30);
					break;
	case TORUS:		if (wire)
						glutWireTorus(60,90,30,30);
					else glutSolidTorus(60, 90, 30, 30);
					break;
	case TEAPOT:	if (wire)
						glutWireTeapot(90);
					else glutSolidTeapot(90);
					break;
	}
}