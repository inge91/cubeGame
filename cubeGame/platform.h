
#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED
#include "StdAfx.h"
#include <vector>
#include "cube.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

class Platform
{
	public:
		Platform(Cube c);

		// Draws the level in its current state
		void draw_level();
		
	private:
		// ENUMS to fill in the grid board
		enum {EMPTY,ONE, TWO, THREE, START, END};

		// Size of the panels
		GLfloat msize;		GLfloat mminx;		GLfloat mmaxz;		// Rows of the level, stored in vectors
		vector<vector <int>> mlevel;

		// Level fills the level vector
		void prepare_level();





};


#endif