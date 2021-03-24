#include <stdlib.h>
#include <GL/glut.h>

static int a = 0, b = 0;
static float FPS = 60.0;

void draw(int w, int h, int y, bool reflect) {
	glLoadIdentity();
	glTranslatef(w-w/2, h - y, 0);
	if (reflect)
		glScalef(1, -1, 1);
	glTranslatef(a, -b, 0);
	glColor4f(0, 0, 1, 0.3);
	glutSolidSphere(55, 30, 30);
	glColor4f(1, 0, 0, 0.3);
	glTranslatef(200 + a, -b, 0);
	glutSolidCube(45);
}

void display() {
	glClearColor(1, 1, 1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	int w = glutGet(GLUT_WINDOW_WIDTH) / 2, h = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	draw(w,h,-80, true);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	draw(w,h,80, false);
	glDisable(GL_BLEND);

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
	case 'w':
		b+=5;
		break;
	case 's':
		b-=5;
		break;
	case 'a':
		a-=5;
		break;
	case 'd':
		a+=5;
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