// Header file for graphics
// dvan2, Oct 2016

#ifndef __GRAPHICS__
#define __GRAPHICS__

#if defined (__MINGW32__) && !defined (WIN32)
#define WIN32
#endif

#ifdef WIN32
#define _USE_MATH_DEFINES
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <SOIL.h>
#include "player_class.h"
using namespace std;

#define SMALL_NUM 0.0000001
#define SCALE 2.0 // (m)
#define PREFERRED_WIDTH 1024
#define PREFERRED_HEIGHT 768

enum game_stage { STARTING = 0, MIDDLE = 1, ENDING = 2 };

// Graphics variables
int main_window;
double aspect_ratio, window_width, window_height;
bool texture_available;
GLuint starting_texture, not_playing_texture, building_texture, eating_texture, sleeping_texture, dead_texture, alive_texture;
player my_player;
game_stage stage;

// Function prototypes
void reshape_window (int width, int height);
void draw_window (void);
void update_state (void);
void mouse_button (int button, int state, int x, int y);
void glut_key (unsigned char k, int x, int y);
void initialise (void);
bool setup_texture (string filename, GLuint &id);

#endif
