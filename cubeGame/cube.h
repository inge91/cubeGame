// Header for the cube class

#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED
#include "StdAfx.h"
#include <GL/glut.h>

class Cube{

public:	
	//Constructor
	Cube();

	// Position in grid coordinates
	GLfloat mposx;
	GLfloat mposz;

	// keeps track of the direction of movement 
	int mmovement;
	
	// Degree of rotation storers
	int mdegrees;
	int morientationx;
	int morientationz;
	
	// The size of half the cube
	GLfloat msize;
	
	enum { NONE, UP, DOWN, LEFT, RIGHT };

	// Draw cube on the screen depending on position
	void drawCube();

	// Changes the position of the cube
	void change_position(int x, int z);
	
};

#endif
