#include <stdlib.h>
#include <GL/glut.h>

static int angle = 0;
static float FPS = 60.0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	int w = glutGet(GLUT_WINDOW_WIDTH) / 2, h = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glLoadIdentity();
	glTranslatef(w - 70, h - 70, 0);
	glRotatef(angle, 1, 1, 0);
	glColor3f(0, 1, 1);
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluQuadricNormals(sphere, GLU_FLAT);
	gluSphere(sphere, 90, 20, 20);
	glLoadIdentity();
	glTranslatef(w + 70, h + 70, 0);
	glRotatef(-angle, 1, 1, 0);
	glColor3f(1, 0.5, 0);
	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricNormals(cylinder, GLU_FLAT);
	gluCylinder(cylinder, 100, 100, 50, 20, 20);
	gluDeleteQuadric(cylinder);
	gluDeleteQuadric(sphere);
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, 150, -150);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void klawiatura(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		angle++;
		break;
	case 's':
		angle--;
		break;
	case 'q':
		exit(0);
		break;
	}
}
void timer(int t) {
	glutTimerFunc(1000 / FPS, timer, 0);
	int w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutTimerFunc(1, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(klawiatura);
	glutMainLoop();
	return 0;
}