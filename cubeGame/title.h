
#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED
#include "StdAfx.h"
#include <vector>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <gl\gl.h>                        // Header File For The OpenGL32 Library
#include <gl\glu.h>                       // Header File For The GLu32 Library
#include <windows.h> 
#include <mmsystem.h>



class Title
{
public:
	Title();
private:
	// Title screen global variables
	GLfloat mgrow;
	bool growing;

	GLfloat msize;
	GLfloat titledegrees;
	GLfloat titleposition;
	void handle_titlescreen_key(unsigned char key, int x, int y)
}
#endif