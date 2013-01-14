#include "StdAfx.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "cube.h"


Cube::Cube()
{
	mposx = -3;
	mposz = 3;
	msize = 2;
	mmovement = NONE;
	mdegrees = 0;
	morientationx = mdegrees;
	morientationz = mdegrees;
}
int i = 0;
void Cube::drawCube()
{

	glPushMatrix();
	if(mmovement != NONE)
	{ 
		switch(mmovement)
		{
			

		case RIGHT:
			glTranslatef(msize  + (msize * mposx * 2), -msize,0);
			glRotatef(-mdegrees, 0, 0, 1);
			glTranslatef(- msize - (msize * mposx * 2), msize,0);
				  break;
		case LEFT:
			glTranslatef(- msize  + (msize * mposx * 2), -msize,0);
			glRotatef(mdegrees, 0, 0, 1);
			glTranslatef(msize - (msize * mposx * 2), msize,0);
				  break;

		case UP:
			glTranslatef(0, -msize, - msize  + (msize * mposz * 2) );
			glRotatef(-mdegrees, 1, 0, 0);
			glTranslatef(0, msize,  msize - (msize * mposz * 2)   );
			break;
			
		case DOWN:
			glTranslatef(0, -msize, msize  + (msize * mposz * 2) );
			glRotatef(mdegrees, 1, 0, 0);
			glTranslatef(0, msize,  - msize - (msize * mposz * 2) );
			break;


		}

		mdegrees ++;
		// In case full 90 degrees has occured stop and determine new position
		if(mdegrees % 90 == 0)
		{ 
			// Move one unit 
			switch(mmovement)
			{
			case RIGHT:
				morientationx += mdegrees;
				morientationx = morientationx % 360;
				mdegrees = 0;
				mposx ++;
				break;
			case LEFT:
				morientationx -= mdegrees;
				morientationx = morientationx % 360;
				mdegrees = 0;
				mposx --;
				break;
			case UP:
				morientationz += mdegrees;
				morientationz = morientationz % 360;
				mdegrees = 0;
				mposz --;
				break;
			case DOWN:
				morientationz -= mdegrees;
				morientationz = morientationz % 360;
				mdegrees = 0;
				mposz ++;
				break;
			
			}
			mmovement = NONE;
		}
		
	}

	// Apply transformation and rotation in x and y direction to show right side
	glTranslatef(0, 0, mposz * (msize *2));
	glTranslatef(mposx * (msize*2), 0, 0);


	glRotatef(morientationx, 0, 0, 1);
	glRotatef(morientationz, 1, 0, 0);

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
}



void Cube::change_position(int x, int z)
{
	mposx = x;
	mposz = z;
}