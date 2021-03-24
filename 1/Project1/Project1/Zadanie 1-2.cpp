#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "Zadanie2-source.h"

void display1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(100, 100);
	glVertex2f(160, 100);
	glVertex2f(160, 400);
	glVertex2f(100, 400);

	glVertex2f(100, 340);
	glVertex2f(300, 340);
	glVertex2f(300, 400);
	glVertex2f(100, 400);

	glVertex2f(100, 220);
	glVertex2f(250, 220);
	glVertex2f(250, 280);
	glVertex2f(100, 280);

	glEnd();
	glutSwapBuffers();

}

void display2() {
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	colorize();
	int w = glutGet(GLUT_WINDOW_WIDTH) / 2, h = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glTranslated(w, h, 0);
	glRotatef(15, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	draw();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, 120, -120);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void klawiatura1(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	}
}

void klawiatura2(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0': currentColor = WHITE; break;
	case '1': currentColor = LIGHT_GRAY; break;
	case '2': currentColor = DARK_GRAY; break;
	case '3': currentColor = BLACK; break;
	case '4': currentColor = RED; break;
	case '5': currentColor = YELLOW; break;
	case '6': currentColor = GREEN; break;
	case '7': currentColor = CYAN; break;
	case '8': currentColor = BLUE; break;
	case '9': currentColor = MAGENTA; break;

	case 'q': currentShape = SPHERE; break;
	case 'w': currentShape = CUBE; break;
	case 'e': currentShape = CONE; break;
	case 'r': currentShape = TORUS; break;
	case 't': currentShape = TEAPOT; break;

	case 'y': wire = !wire; break;

	case 'z':
		exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(640, 480);
	printf("Wybierz zadanie do wyœwietlenia\n\n\t1 - Litera L\n\t2 - figury GLUT\n\t0 - wyjdŸ\n");
	int UIHandler;
	std::cin >> UIHandler;
	while (UIHandler < 0 || UIHandler>2) {
		system("cls");
		printf("W interfejsie nie ma takiej wartoœci. Spróbuj jeszcze raz.\n\n\t1 - Litera L\n\t2 - figury GLUT\n\t0 - wyjdŸ\n");
		std::cin >> UIHandler;
	}
	if (UIHandler != 0) {
		system("cls");
		glutCreateWindow(argv[0]);
		glutReshapeFunc(reshape);
		if (UIHandler == 1) {
			printf("Zmodyfikuj przykladowy program tak, aby wyswietlal zielona litere F.\n\n");
			printf("Do stworzenia litery F uzylem 3 GL_QUADS.\nWcisnij q, aby wyjsc.\n\n");
			glutDisplayFunc(display1);
			glutKeyboardFunc(klawiatura1);
			glutMainLoop();
		}
		else {
			printf("Napisz program, ktory bedzie wyswietlal podane w instrukcji bryly dostarczane przez biblioteke GLUT(teapot itp.). ");
			printf("Ustawienie, ktora z figur ma zostaæ wyswietlona powinno odbywc sie za pomoca dowolnie wybranych klawiszy.\n\n");
			printf("Klawisze:\n\t0-9 - kolory\n\tq - sfera\n\tw - szescian\n\te - stozek\n\tr - torus\n\tt - czajnik\n");
			printf("Wcisnij y jesli chcesz zobaczyc szkielet.\nWcisnij ponownie, aby sciany znowu byly widoczne.\nWcisnij z, aby wyjsc.");
			glutDisplayFunc(display2);
			glutKeyboardFunc(klawiatura2);
			glutMainLoop();
		}
	}
	return 0;
}