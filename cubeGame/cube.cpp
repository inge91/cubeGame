#include "StdAfx.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "cube.h"


Cube::Cube()
{
	mposx = 2;
	mposz = 0;
	msize = 2;
	mmovement = NONE;
	mdegrees = 0;
}
int i = 0;
void Cube::drawCube()
{
	glPushMatrix();
	

	if(mmovement != NONE)
	{ 
		if(i >0)
		{
			std::cout<<"Hello";
		}
		switch(mmovement)
		{
			

		case RIGHT:
			std::cout<< msize + msize * mposx * 2<<std::endl;
			glTranslatef(msize  + (msize * mposx * 2), -msize,0);
			glRotatef(-mdegrees, 0, 0, 1);
			glTranslatef(- msize - (msize * mposx * 2), msize,0);
				  break;
		}

		mdegrees ++;
		// In case full 90 degrees has occured stop and determine new position
		if(mdegrees % 90 == 0)
		{ 
			i ++ ;
			// Move one unit 
			switch(mmovement)
			{
			case RIGHT:
				mposx ++;
			}
			mmovement = NONE;
		}
		
	}
	else{
		glTranslatef(mposx * (msize*2), 0, mposz * (msize*2));
		glRotatef(-mdegrees, 0, 0, 1);
	}

	//glTranslatef(mposx* (2*msize), 0, mposz * (2*msize));
	glBegin(GL_QUADS);

	// Draw cube on center
	// This is the front
	glColor3f(1, 0, 0);
	glNormal3f(0, 0, 1);
	glVertex3f(-msize, -msize, msize);
	glVertex3f( msize, -msize, msize);
	glVertex3f( msize,  msize, msize);
	glVertex3f(-msize,  msize, msize);


	// This is the back
	glColor3f(1, 0, 0);
	glNormal3f(0, 0, -1);
	glVertex3f(-msize, -msize, -msize);
	glVertex3f( msize, -msize, -msize);
	glVertex3f( msize,  msize, -msize);
	glVertex3f(-msize,  msize, -msize);

	// This is the top
	glColor3f(0, 1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(-msize, msize, -msize);
	glVertex3f( msize, msize, -msize);
	glVertex3f( msize, msize, msize);
	glVertex3f(-msize, msize, msize);

	// This is the bottom
	glColor3f(0, 1, 0);
	glNormal3f(0, -1, 0);
	glVertex3f(-msize, -msize, -msize);
	glVertex3f( msize, -msize, -msize);
	glVertex3f( msize, -msize, msize);
	glVertex3f(-msize, -msize, msize);


	// This is the left
	glColor3f(0, 0, 1);
	glNormal3f(-1 , 0, 0);
	glVertex3f(-msize, -msize, -msize);
	glVertex3f(-msize,  msize, -msize);
	glVertex3f(-msize,  msize, msize);
	glVertex3f(-msize, -msize, msize);


	// This is the right
	glColor3f(0, 0, 1);
	glNormal3f(1 , 0, 0);
	glVertex3f(msize, -msize, -msize);
	glVertex3f(msize,  msize, -msize);
	glVertex3f(msize,  msize, msize);
	glVertex3f(msize, -msize, msize);

	glEnd();
	glPopMatrix();

			glBegin(GL_LINES);
			glColor3f(1, 1, 1);

			glVertex3f(msize  + (msize * mposx * 2), -msize,-100);
			glVertex3f(msize  + (msize * mposx * 2), -msize,100);
			glEnd();
}
