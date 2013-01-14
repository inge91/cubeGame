#include "StdAfx.h"
#include "platform.h"
#include "cube.h"


Platform::Platform(Cube c)
{
	// Size of the panels sould be as big as the cube is
	msize = c.msize;
	prepare_level();
	mminx = -14;
	mmaxz = 14;
}

//TODO: Read from file
void Platform::prepare_level()
{
	vector<int> mrow1;
	vector<int> mrow2;
	vector<int> mrow3;
	vector<int> mrow4;
	vector<int> mrow5;
	vector<int> mrow6;
	vector<int> mrow7;
	
	mrow1.push_back(START);
	mrow1.push_back(EMPTY);
	mrow1.push_back(EMPTY);
	mrow1.push_back(EMPTY);
	mrow1.push_back(EMPTY);
	mrow1.push_back(EMPTY);
	mrow1.push_back(END);

	mrow2.push_back(ONE);
	mrow2.push_back(EMPTY);
	mrow2.push_back(EMPTY);
	mrow2.push_back(EMPTY);
	mrow2.push_back(EMPTY);
	mrow2.push_back(EMPTY);
	mrow2.push_back(ONE);

	mrow3.push_back(ONE);
	mrow3.push_back(EMPTY);
	mrow3.push_back(EMPTY);
	mrow3.push_back(EMPTY);
	mrow3.push_back(EMPTY);
	mrow3.push_back(EMPTY);
	mrow3.push_back(ONE);

	mrow4.push_back(ONE);
	mrow4.push_back(ONE);
	mrow4.push_back(ONE);
	mrow4.push_back(ONE);
	mrow4.push_back(ONE);
	mrow4.push_back(ONE);
	mrow4.push_back(ONE);

	mrow5.push_back(EMPTY);
	mrow5.push_back(EMPTY);
	mrow5.push_back(EMPTY);
	mrow5.push_back(EMPTY);
	mrow5.push_back(EMPTY);
	mrow5.push_back(EMPTY);
	mrow5.push_back(EMPTY);

	mrow6.push_back(EMPTY);
	mrow6.push_back(EMPTY);
	mrow6.push_back(EMPTY);
	mrow6.push_back(EMPTY);
	mrow6.push_back(EMPTY);
	mrow6.push_back(EMPTY);
	mrow6.push_back(EMPTY);

	mrow7.push_back(EMPTY);
	mrow7.push_back(EMPTY);
	mrow7.push_back(EMPTY);
	mrow7.push_back(EMPTY);
	mrow7.push_back(EMPTY);
	mrow7.push_back(EMPTY);
	mrow7.push_back(EMPTY);

	mlevel.push_back(mrow1);
	mlevel.push_back(mrow2);
	mlevel.push_back(mrow3);
	mlevel.push_back(mrow4);
	mlevel.push_back(mrow5);
	mlevel.push_back(mrow6);
	mlevel.push_back(mrow7);
}


void Platform::draw_level()
{
	int position;
	//mrow1 = mlevel.pop_back();
	glBegin(GL_QUADS);

	// Draw the board pane for pane
	for(int i =0; i < 7; i++){

		for( int j = 0; j < 7; j++){

			position = mlevel.at(i).at(j);	
			
			switch(position)
			{
			case EMPTY:
				continue;
			case ONE:
				glColor3f(0.7, 0.7, 0.7);
				break;
			case TWO:
				glColor3f(0.5, 0.5, 0);
				break;
			case THREE:
				glColor3f(0.6, 0.2, 0);
				break;
			case START:
				glColor3f(0.5, 1, 0);
				break;
			case END:
				glColor3f(0.0, 0.5, 0.8);
				break;
			}

			glVertex3f(mminx + (i *msize*2), -msize, mmaxz - (j*msize*2));
			glVertex3f(mminx + ((i+1)*msize*2), -msize, mmaxz - (j* msize*2));
			glVertex3f(mminx + ((i +1)*msize*2), -msize, mmaxz - ((j+1) *2*msize));
			glVertex3f(mminx + (i *msize*2), -msize, mmaxz - ((j+1) *2*msize));
		}
	}

	glEnd();

}


