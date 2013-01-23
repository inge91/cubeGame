// Header for the cube class

#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED
#include "StdAfx.h"
#include <GL/glut.h>
#include <list>
#include <windows.h> 
#include <mmsystem.h>

class Cube{

public:	
	//Constructor
	Cube(bool mute);

	// Position in grid coordinates
	GLfloat mposx;
	GLfloat mposz;

	GLfloat mprevx;
	GLfloat mprevz;

	// keeps track of the direction of movement 
	int mmovement;
	
	// Degree of rotation storers
	int mdegrees;
	int morientationx;
	int morientationz;
	
	// The size of half the cube
	GLfloat msize;
	
	enum { NONE, UP, DOWN, LEFT, RIGHT };

	enum{EMPTY, X, Y, NEGX, NEGY};

	bool mmute;
	

	// Contains the sequence of rotations for the cube
	std::list<int> msequence;
	
	// Draw cube on the screen depending on position
	void drawCube();

	// Changes the position of the cube
	void change_position(int x, int z);

	void set_sound();
	
};

#endif
