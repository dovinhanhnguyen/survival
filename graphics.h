// Header file for graphics
// dvan2, Oct 2016

#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <GL/glut.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <SOIL.h>
using namespace std;

#define SMALL_NUM 0.0000001
#define SCALE 2.0 // (m)
#define PREFERRED_WIDTH 800
#define PREFERRED_HEIGHT 600

// Graphics variables
int main_window;
double aspect_ratio, window_width, window_height;
bool texture_available;
GLuint texture, texture_2;

// Function prototypes
void reshape_window (int width, int height);
void draw_window (void);
void update_state (void);
void mouse_button (int button, int state, int x, int y);
void glut_key (unsigned char k, int x, int y);
void initialise (void);
bool setup_texture (string filename, GLuint &id);

#endif
