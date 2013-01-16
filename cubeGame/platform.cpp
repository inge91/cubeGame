#include "StdAfx.h"
#include "platform.h"
#include "cube.h"


Platform::Platform(Cube *c)
{
	mc = c;
	// Size of the panels sould be as big as the cube is
	msize = mc->msize;
	mlevelno = "2";
	mminx = -14;
	mmaxz = 14;
	prepare_level();
}

//TODO: Read from file
void Platform::prepare_level()
{

	string leveltxt = string("level") +  string(mlevelno) + string(".txt");
	ifstream myfile (leveltxt);
	//myfile.open("level1.txt", ios::out);

	string line1;
	string line2;
	string line3;
	string line4;
	string line5;
	string line6; 
	string line7;

	getline(myfile,line1);
	getline(myfile,line2);
	getline(myfile,line3);
	getline(myfile,line4);
	getline(myfile,line5);
	getline(myfile,line6);
	getline(myfile,line7);

	myfile.close();
	int mrow1[7];
	int mrow2[7];
	int mrow3[7];
	int mrow4[7];
	int mrow5[7];
	int mrow6[7];
	int mrow7[7];
	
	mrow1[0]=line7[0]-'0';
	mrow1[1]=line7[2]-'0';
	mrow1[2]=line7[4]-'0';
	mrow1[3]=line7[6]-'0';
	mrow1[4]=line7[8]-'0';
	mrow1[5]=line7[10]-'0';
	mrow1[6]=line7[12]-'0';

	mrow2[0]=line6[0]-'0';
	mrow2[1]=line6[2]-'0';
	mrow2[2]=line6[4]-'0';
	mrow2[3]=line6[6]-'0';
	mrow2[4]=line6[8]-'0';
	mrow2[5]=line6[10]-'0';
	mrow2[6]=line6[12]-'0';

	mrow3[0]=line5[0]-'0';
	mrow3[1]=line5[2]-'0';
	mrow3[2]=line5[4]-'0';
	mrow3[3]=line5[6]-'0';
	mrow3[4]=line5[8]-'0';
	mrow3[5]=line5[10]-'0';
	mrow3[6]=line5[12]-'0';

	mrow4[0]=line4[0]-'0';
	mrow4[1]=line4[2]-'0';
	mrow4[2]=line4[4]-'0';
	mrow4[3]=line4[6]-'0';
	mrow4[4]=line4[8]-'0';
	mrow4[5]=line4[10]-'0';
	mrow4[6]=line4[12]-'0';

	mrow5[0]=line3[0]-'0';
	mrow5[1]=line3[2]-'0';
	mrow5[2]=line3[4]-'0';
	mrow5[3]=line3[6]-'0';
	mrow5[4]=line3[8]-'0';
	mrow5[5]=line3[10]-'0';
	mrow5[6]=line3[12]-'0';

	mrow6[0]=line2[0]-'0';
	mrow6[1]=line2[2]-'0';
	mrow6[2]=line2[4]-'0';
	mrow6[3]=line2[6]-'0';
	mrow6[4]=line2[8]-'0';
	mrow6[5]=line2[10]-'0';
	mrow6[6]=line2[12]-'0';

	mrow7[0]=line1[0]-'0';
	mrow7[1]=line1[2]-'0';
	mrow7[2]=line1[4]-'0';
	mrow7[3]=line1[6]-'0';
	mrow7[4]=line1[8]-'0';
	mrow7[5]=line1[10]-'0';
	mrow7[6]=line1[12]-'0';

	// Fill the whole playing field
	for(int j = 0; j < 7; j++)
	{
		mlevel[0][j] = mrow1[j];
		mlevel[1][j] = mrow2[j];
		mlevel[2][j] = mrow3[j];
		mlevel[3][j] = mrow4[j];
		mlevel[4][j] = mrow5[j];
		mlevel[5][j] = mrow6[j];
		mlevel[6][j] = mrow7[j];

	}
	//TODO: dynamic positioner
	mc->change_position(-3, 3);
}


void Platform::draw_level()
{
	int position;
	//mrow1 = mlevel.pop_back();
	glBegin(GL_QUADS);

	// Draw the board pane for pane
	for(int i =0; i < 7; i++){

		for( int j = 0; j < 7; j++){

			position = mlevel[i][j];	
			
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

			glVertex3f(mminx + (j *msize*2), -msize, mmaxz - (i*msize*2));
			glVertex3f(mminx + ((j+1)*msize*2), -msize, mmaxz - (i* msize*2));
			glVertex3f(mminx + ((j +1)*msize*2), -msize, mmaxz - ((i+1) *2*msize));
			glVertex3f(mminx + (j *msize*2), -msize, mmaxz - ((i+1) *2*msize));
		}
	}

	glEnd();

}

// Update the game state
void Platform::update(){
	// No movement has occured, don't change anything
	if(mc->mposx == mc->mprevx && mc->mposz == mc->mprevz)
	{
		// Nothing
	}
	else{ 
	int x = mc->mposx +3;
	int y = -mc->mprevz + 3; 

	int position = mlevel[y][x];
	
	// artificially change the position if outside area
	if(x < 0 || x > 6 || y > 6 || y < 0)
	{
		position = EMPTY;
	}

	switch(position){
	// Cube died
	case EMPTY:
		prepare_level();
		break;
	case TWO:
		break;
	case END:
		std::cout<<"Won level";
		//mlevelno ++;
		//prepare_level();
		break;
	}
	}
	// No movement has occured, don't change anything
	if(mc->mposx == mc->mprevx && mc->mposz == mc->mprevz)
	{
		// Nothing
	}
	else
	{
		int j = mc->mprevx +3;
		int i = -mc->mprevz +3;

		int prev_position = mlevel[i][j];

		switch(prev_position)
		{
			case EMPTY:
			//Should never occur
			break;
			case ONE:
				mlevel[i][j] = prev_position -1;
				break;
			case TWO:
				mlevel[i][j] = prev_position -1;
				break;
			case THREE:
				mlevel[i][j] = prev_position -1;
				break;
		}
		// Set them alike for unnecessary double checking
		mc->mprevx = mc->mposx;
		mc->mprevz = mc->mposz;

	}
	
}
void Platform::print_board(){
		
	for(int i = 0; i < 7; i ++)
	{
		cout<<"\n";
		for(int j = 0; j < 7; j++)
		{
			cout<<mlevel[i][j];
			cout<<" ";
		}
	}

}

void Platform::print_position(int x, int y){
		
	for(int i = 0; i < 7; i ++)
	{
		cout<<"\n";
		for(int j = 0; j < 7; j++)
		{
			if(i == x && y == j)
			{
				cout<<"x";
			}
			else{ 
				cout<<mlevel[i][j];
			}
			cout<<" ";
		}
	}

}