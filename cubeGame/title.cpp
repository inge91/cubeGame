#include "StdAfx.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "title.h"

Title::Title()
{

	// Title screen global variables
	mgrow =0.5;
	growing = true;

	msize = 0.5;
	titledegrees = 0;
	titleposition = 0.25;

}

// Handle the keys pressed on the title screen
void Title:handle_titlescreen_key(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 119:
	case 38:
		if(titleposition != 0.25)
		{

			titleposition += 2;
		}
		break;
	case 's':
		if(titleposition != (0.25 - 3*2))
		{

			titleposition -= 2;
		}
		break;
	case 13:
		// Make the selection automatically the above one
		if(titleposition == 0.25 || titleposition == -1.75)
		{
			if(titleposition == 0.25)
			{
				// Do the level finder
				
				ifstream myfile ("pwd.txt");

				if(myfile == NULL){
					// Nothing to do
				}
				else
				{
					string a; 
					const char* l;
					int lvl;
					getline(myfile, a);
					lvl = a[0];
					p.change_mlevelno(lvl);
				}

			}
			
			titleposition = 0.25;
			p.prepare_level();
			glutDisplayFunc(drawScene);
			glutKeyboardFunc(handleKeypress);
		}
		else if (titleposition == -3.75)
		{
			titleposition = 0.25;
			glutDisplayFunc(instruction_screen);
			glutKeyboardFunc(instruction_keys);

		}
		else if(titleposition == -5.75)
		{
			exit(0);
		}

		break;

	case 27: //Escape key
			exit(0);
			break;
	}

}

// Response keys in case of instruction pagevo
void instruction_keys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		glutKeyboardFunc(handle_titlescreen_key);
		glutDisplayFunc(screen_title);

	}

}


void instruction_screen()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Establish view 
	glTranslatef(0, 0, -50);

	glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT); // clear screen, to glClearColor()
    glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-10,2);
	int len, i;
	string fin = "The objective is to work from the beginning to the end position (the blue tile)." 
		"\n Once you visit a tile it will disappear.\n Some tiles can be visited multiple times, depending on " 
		" the color. \n All tiles have to be cleared to win the level.\n You have infinite lives."
		"\n\n Press m to mute sounds. \n Press r to restart level. ";
	const char* a = fin.c_str();
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a);
	glutSwapBuffers();

}


void screen_title()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Establish view 
	glTranslatef(0, 0, -50);

	glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT); // clear screen, to glClearColor()
    glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-2,0);
	int len, i;
	string fin = "Continue";
	const char* a = fin.c_str();
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a);

	string fin2 = "New Game" ;
	const char* a2 = fin2.c_str();
	glRasterPos2f(-2, -2);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a2);

	string fin3 = "Instructions" ;
	const char* a3 = fin3.c_str();
	glRasterPos2f(-2, -4);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a3);

	string fin4 = "Exit Game" ;
	const char* a4 = fin4.c_str();
	glRasterPos2f(-2, -6);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a4);

	string fin5 = "The Amazing Cube Game!" ;
	const char* a5 = fin5.c_str();
	glRasterPos2f(-4, 16);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a5);

	// Cursor cube
	glPushMatrix();
	glTranslatef(-3, titleposition, 0);
	glRotatef(titledegrees, 1, 1, 0);

	// Draw cube on center
	// This is the front
	glBegin(GL_QUADS);
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
	titledegrees += 0.5;
	if(titledegrees > 360)
	{
		titledegrees -= 360;
	}

	// Decorative cube
	glPushMatrix();
	glTranslatef(0, 8, 0);
	glRotatef(titledegrees, 0.5, 0, 1);

	// Draw cube on center
	// This is the front
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glNormal3f(0, 0, 1);
	glVertex3f(-mgrow, -mgrow, mgrow);
	glVertex3f( mgrow, -mgrow, mgrow);
	glVertex3f( mgrow,  mgrow, mgrow);
	glVertex3f(-mgrow,  mgrow, mgrow);

	// This is the back
	glColor3f(1, 0, 0);
	glNormal3f(0, 0, -1);
	glVertex3f(-mgrow, -mgrow, -mgrow);
	glVertex3f( mgrow, -mgrow, -mgrow);
	glVertex3f( mgrow,  mgrow, -mgrow);
	glVertex3f(-mgrow,  mgrow, -mgrow);

	// This is the top
	glColor3f(0, 1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(-mgrow, mgrow, -mgrow);
	glVertex3f( mgrow, mgrow, -mgrow);
	glVertex3f( mgrow, mgrow, mgrow);
	glVertex3f(-mgrow, mgrow, mgrow);

	// This is the bottom
	glColor3f(0, 1, 0);
	glNormal3f(0, -1, 0);
	glVertex3f(-mgrow, -mgrow, -mgrow);
	glVertex3f( mgrow, -mgrow, -mgrow);
	glVertex3f( mgrow, -mgrow, mgrow);
	glVertex3f(-mgrow, -mgrow, mgrow);


	// This is the left
	glColor3f(0, 0, 1);
	glNormal3f(-1 , 0, 0);
	glVertex3f(-mgrow, -mgrow, -mgrow);
	glVertex3f(-mgrow,  mgrow, -mgrow);
	glVertex3f(-mgrow,  mgrow, mgrow);
	glVertex3f(-mgrow, -mgrow, mgrow);


	// This is the right
	glColor3f(0, 0, 1);
	glNormal3f(1 , 0, 0);
	glVertex3f(mgrow, -mgrow, -mgrow);
	glVertex3f(mgrow,  mgrow, -mgrow);
	glVertex3f(mgrow,  mgrow, mgrow);
	glVertex3f(mgrow, -mgrow, mgrow);
	glEnd();
	glPopMatrix();

	// Handle the growing and slinking aspect
	if(growing)
	{
		if(mgrow > 4)
		{
			growing = false;
			mgrow -= 0.005;
		}
		else{
		
			mgrow += 0.005;
		}

	}
	else
	{
		if(mgrow <0.1)
		{
			growing = true;
			mgrow += 0.005;
		}
		else{
			mgrow -= 0.005;
		}
	}

	glutSwapBuffers();
}