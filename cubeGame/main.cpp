
#include "StdAfx.h"
#include "main.h"

GLfloat boxsize = 2;
bool rotating = false;
GLfloat degrees = 1;
bool mute = false;

// Size of the window
int width = 800;
int height = 600;
Cube c = Cube(mute);
Platform p = Platform(&c);

// Title screen global variables
GLfloat mgrow =0.5;
bool growing = true;

GLfloat msize = 0.5;
GLfloat titledegrees = 0;
GLfloat titleposition = 0.25;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND ); glClearColor(0.0,0.0,0.0,0.0);

}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}


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
		case 'r':
			p.prepare_level();
			break;

	case 27: //Escape key
		glutDisplayFunc(screen_title);
		glutKeyboardFunc(handle_titlescreen_key);
			
	}
}


// Handle the keys pressed on the title screen
void handle_titlescreen_key(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 119:
	case 38:
		if(titleposition != 0.25)
		{
			if(!mute)
			{
				PlaySound(L"select.wav", NULL, SND_ASYNC|SND_FILENAME);
			}
			titleposition += 2;
		}
		break;
	case 's':
		if(titleposition != (0.25 - 3*2))
		{
			if(!mute){
				PlaySound(L"select.wav", NULL, SND_ASYNC|SND_FILENAME);
			}
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
			else{
			p.change_mlevelno(1);
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
	case 109:
		mute = !mute;
		c.set_sound();
		p.set_sound();
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
		"\n\n Press m to mute sounds. \n Press r to restart level.\n Progresse is saved automatically ";
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

	string fin5 = "Six Sides of Destruction" ;
	const char* a5 = fin5.c_str();
	glRasterPos2f(-4, 16);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a5);



	string fin6 = "" ;
	if(mute)
	{
		fin6 = "Press m to unmute";
	}
	else{
		fin6 = "Press m to mute";
	}
	const char* a6 = fin6.c_str();
	glRasterPos2f(-2, -20);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a6);


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

void draw_meta()
{
	glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT); // clear screen, to glClearColor()
    glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-15, -20);
	int len, i;
	string s = "Level: ";
	string c = p.get_level();
	string fin = s + c;
	const char* a = fin.c_str();
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a);

	string fin2 = "" ;
	if(mute)
	{
		fin2 = "Press m to unmute";
	}
	else{
		fin2 = "Press m to mute";
	}
	const char* a2 = fin2.c_str();
	glRasterPos2f(-2, -20);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) a2);

	glEnable(GL_LIGHTING);

}


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0, 0, -50);
	draw_meta();

	glPushMatrix();
	// Establish view 
	glRotatef(35, 1,0, 0);
	glRotatef(-20, 0, 1, 0);

	// Display some text


	// Draws the cube and handles movement  
	c.drawCube();
	
	// Update the board and see if cube didn't fall
	p.update();

	// Draw the level
	p.draw_level();
	glPopMatrix();
	
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
	glutGameModeGet(GLUT_GAME_MODE_POSSIBLE);
	if(GLUT_GAME_MODE_POSSIBLE)
	{
		glutEnterGameMode(); 
	}
	else
	{
			RECT desktop;
		   // Get a handle to the desktop window
		   const HWND hDesktop = GetDesktopWindow();
		   // Get the size of screen to the variable desktop
		   GetWindowRect(hDesktop, &desktop);
		   width = desktop.right;
		   height = desktop.bottom-65;
			glutInitWindowSize(desktop.right, desktop.bottom-55);
		glutInitWindowPosition (0,0);
		glutCreateWindow("Six Sides of Destruction");
	}
	initRendering();
	glutDisplayFunc(screen_title);
	glutKeyboardFunc(handle_titlescreen_key);
	glutReshapeFunc(handleResize);
	glutTimerFunc(2, update, 0);
	
	glutMainLoop();
	return 0;
}
 