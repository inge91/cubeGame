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
	mprevx = mposx;
	mprevz = mposz;

	msize = 2;
	mmovement = NONE;
	mdegrees = 0;
	morientationx = mdegrees;
	morientationz = mdegrees;
}

GLfloat xprev=-99;
GLfloat zprev=-99;
bool first = true;
int movement = 0;

void Cube::drawCube()
{
	glPushMatrix();
	if(mmovement != NONE)
	{ 
		xprev = morientationx;
		zprev = morientationz;
		switch(mmovement)
		{
			

		case RIGHT:
			glTranslatef(msize  + (msize * mposx * 2), -msize,0);
			glRotatef(-mdegrees, 0, 0, 1);
			glTranslatef(- msize - (msize * mposx * 2), msize,0);
			movement = RIGHT;
				  break;
		case LEFT:
			glTranslatef(- msize  + (msize * mposx * 2), -msize,0);
			glRotatef(mdegrees, 0, 0, 1);
			glTranslatef(msize - (msize * mposx * 2), msize,0);
			movement = LEFT;
				  break;

		case UP:
			glTranslatef(0, -msize, - msize  + (msize * mposz * 2) );
			glRotatef(-mdegrees, 1, 0, 0);
			glTranslatef(0, msize,  msize - (msize * mposz * 2)   );
			movement = UP;
			break;
			
		case DOWN:
			glTranslatef(0, -msize, msize  + (msize * mposz * 2) );
			glRotatef(mdegrees, 1, 0, 0);
			glTranslatef(0, msize,  - msize - (msize * mposz * 2) );
			movement = DOWN;
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
				mprevx =mposx;
				mposx ++;
				msequence.push_front(X);
				break;
			case LEFT:
				morientationx -= mdegrees;
				morientationx = morientationx % 360;
				mdegrees = 0;
				mprevx =mposx;
				mposx --;
				msequence.push_front(NEGX);
				break;
			case UP:
				morientationz += mdegrees;
				morientationz = morientationz % 360;
				mdegrees = 0;
				mprevz =mposz;
				mposz --;
				msequence.push_front(Y);
				break;
			case DOWN:
				morientationz -= mdegrees;
				morientationz = morientationz % 360;
				mdegrees = 0;
				mprevz =mposz;
				mposz ++;
				msequence.push_front(NEGY);
				break;
			
			}
			mmovement = NONE;
		}
		
	}

	// Apply transformation and rotation in x and y direction to show right side
	glTranslatef(mposx * (msize*2), 0, 0);
	glTranslatef(0, 0, mposz * (msize *2));

	int value;
	std::list<int>::const_iterator iterator;
	for(iterator = msequence.begin(); iterator != msequence.end(); ++iterator)
	{
		value = *iterator;
		switch(value)
		{
		case X:
		glRotatef(90, 0, 0, 1);
		break;
		case NEGX:
		glRotatef(-90, 0, 0, 1);
		break;
		case Y:
		glRotatef(90, 1, 0, 0);
		break;
		case NEGY:
		glRotatef(-90, 1, 0, 0);
		break;
		
		}
	}
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
	msequence.clear();
	// There are no previous positions yet
	mprevx = mposx;
	mprevz = mposz;
}


