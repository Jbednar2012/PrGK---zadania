#include<GL/glut.h>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include "Particles.h"

static float FPS = 60.0;
static Particle smokeParticles[50];
static Point3D fire;
static float diffusion = 0.03;

void setNewDirection(Particle *smokeParticle) {
	smokeParticle->vector.newPosition = { smokeParticle->vector.currentPosition.x + (rand() % 3) - 1,smokeParticle->vector.currentPosition.y + 1, smokeParticle->vector.currentPosition.z + (rand() % 3) - 1 };
}

void setStartDiffusion(Particle *smokeParticle) {
	smokeParticle->alpha = (float)(rand() % 5 + 15) / 20;
}

void moveParticle(Particle *particle, Point3D newSpot) {
	particle->vector.currentPosition = newSpot;
}

void simulateSmokeParticle(Particle *particle)
{
	glLoadIdentity();
	glColor4f(0.5, 0.5, 0.5, particle->alpha);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex3f(particle->vector.currentPosition.x, particle->vector.currentPosition.y, particle->vector.currentPosition.z);
	glEnd();
	particle->alpha -= diffusion;
	if (particle->alpha <= 0.0) {
		moveParticle(particle, fire);
		setStartDiffusion(particle);
	}
	else moveParticle(particle, (particle->vector.newPosition));
	setNewDirection(particle);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glBegin(GL_POINTS);
		glColor4f(1, 0, 0, 1);
		glVertex3f(fire.x, fire.y, fire.z);
		glColor4f(1, 1, 0, 1);
		glVertex3f(fire.x, fire.y-5, fire.z);
	glEnd();
	std::cout << fire.x << "\t" << fire.y << "\t" << fire.z << std::endl;

	for (int i = 0; i < sizeof(smokeParticles) / sizeof(smokeParticles[0]); i++) {
		simulateSmokeParticle(&smokeParticles[i]);
		std::cout << smokeParticles[i].vector.currentPosition.x << " " << smokeParticles[i].vector.currentPosition.y << " " << smokeParticles[i].vector.currentPosition.z << " " << smokeParticles[i].alpha << std::endl;
	}
	glDisable(GL_BLEND);
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, 200, -200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
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

void klawiatura(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);
	float w = (float)glutGet(GLUT_WINDOW_WIDTH)/2, h = (float)glutGet(GLUT_WINDOW_HEIGHT)/2;
	fire = { w, h - 100, 0 };
	srand(time(0));
	for (int i = 0;i < sizeof(smokeParticles) / sizeof(smokeParticles[0]);i++) {
		moveParticle(&smokeParticles[i], fire);
		setNewDirection(&smokeParticles[i]);
		setStartDiffusion(&smokeParticles[i]);
		std::cout << smokeParticles[i].vector.currentPosition.x << " " << smokeParticles[i].vector.currentPosition.y << " " << smokeParticles[i].vector.currentPosition.z << std::endl;
		std::cout << smokeParticles[i].vector.newPosition.x << " " << smokeParticles[i].vector.newPosition.y << " " << smokeParticles[i].vector.newPosition.z << " " << smokeParticles[i].alpha << std::endl;
	}
	glutDisplayFunc(display);
	glutTimerFunc(1, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(klawiatura);
	glutMainLoop();
	return 0;
}