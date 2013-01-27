
#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "cube.h"
#include "platform.h"
#include <string>
#include <windows.h>
#include "wtypes.h"

// prototype
void drawScene();
void initRendering();
void handleResize(int w, int h);
void handleKeypress(unsigned char key, int x, int y);
void handle_titlescreen_key(unsigned char key, int x, int y);
void instruction_keys(unsigned char key, int x, int y);
void instruction_screen();
void screen_title();
void draw_meta();
void update(int value);

using namespace std;