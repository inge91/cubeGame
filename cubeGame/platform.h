
#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED
#include "StdAfx.h"
#include <vector>
#include "cube.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <gl\gl.h>                        // Header File For The OpenGL32 Library
#include <gl\glu.h>                       // Header File For The GLu32 Library
#include <Windows.h> 
using namespace std;

class Platform
{
	public:
		Platform(Cube *c);

		// Draws the level in its current state
		void draw_level();
		void update();
		void set_sound();
		
	private:
		// ENUMS to fill in the grid board
		enum {EMPTY,ONE, TWO, THREE, START, END};

		// Size of the panels
		GLfloat msize;		GLfloat mminx;		GLfloat mmaxz;		Cube * mc;		// Rows of the level, stored in vectors
		int mlevel [7][7];
		string mlevelno;

		// Level fills the level vector
		void prepare_level();
		// Update to next level
		void update_level();

		// Debug prints
		void print_board();
		void print_position(int x, int y);

		// returns true if still unvisited tiles
		// else false
		bool unattended();

		bool mmute;

};



#endif