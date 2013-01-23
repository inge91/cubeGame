

#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "cube.h"
#include "platform.h"
#include <windows.h>

using namespace std;

GLfloat boxsize = 2;
bool rotating = false;
GLfloat degrees = 1;
bool mute = false;


Cube c = Cube(mute);
Platform p = Platform(&c);
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 100:
		if(c.mmovement == c.NONE)
		{
			c.mmovement = c.RIGHT;
		}	
		break;
	case 97:
		if(c.mmovement == c.NONE)
		{
			c.mmovement = c.LEFT;
		}	
		
		break;
	case 119: 
		if(c.mmovement == c.NONE)
		{
			c.mmovement = c.UP;
		}	
		
		break;
	case 115:
if(c.mmovement == c.NONE)
		{
		c.mmovement = c.DOWN;
		}	
		break;
		case 109:
			mute = !mute;
			c.set_sound();
			p.set_sound();
			break;

	case 27: //Escape key
			exit(0);
	}
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	// Establish view 
	glTranslatef(0, 0, -50);
	glRotatef(35, 1,0, 0);
	glRotatef(-20, 0, 1, 0);

	glColor3f(1, 1, 1);
	glRasterPos3f(100, 100, 0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)"some text");
	


	glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT); // clear screen, to glClearColor()
    glColor3f(1.0,0.0,0.0); // output the string, in red
	glRasterPos2f(14, 5);
	int len, i;
	char *s = "hello";
	char* s2 = "hello";
	len = (int) strlen(s);
	   glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*) s2);

	// Draws the cube and handles movement
	c.drawCube();
	
	// Update the board and see if cube didn't fall
	p.update();

	// Draw the level
	p.draw_level();
	
	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(2, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cube Game");
	glutGameModeString("1920x1080");
	std::cout<<glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)<<endl;

	//glutEnterGameMode(); 
	//glutFullScreen();
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(2, update, 0);
	
	glutMainLoop();
	return 0;
}
 
