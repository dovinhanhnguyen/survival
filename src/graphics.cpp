// Implementation for graphics
// dvan2, Oct 2016

#include "graphics.h"

void reshape (int width, int height)
  // Reshape and set up matrices
{
  window_width = glutGet(GLUT_WINDOW_WIDTH);
  window_height = glutGet(GLUT_WINDOW_HEIGHT);
  aspect_ratio = window_width/window_height;
  
  glutSetWindow(main_window);
  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-SCALE*aspect_ratio, SCALE*aspect_ratio, -SCALE, SCALE, -1.0, 1.0);
}

void print_bitmap (float r, float g, float b, float x, float y, float z, string s, void *font)
  // Draw bitmap characters
{
  glColor3f(r, g, b);
  glRasterPos3f(x, y, z);
  for (int i = 0; i < s.length(); i++) glutBitmapCharacter(font, s[i]);
}

void bind_texture (GLuint texture_id, float r, float g, float b)
  // Bind texture and set colour for theme
{
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glColor3f(r, g, b);
}

void draw_control_bar (double tlx, double tly, double gap_x, double gap_y, double val, double red, double green, double blue, string title)
  // Draws control bar, top left (tlx, tly), val (fraction, range 0-1), colour (red, green, blue), title
{
  if (0.25 <= val && val < 0.5) {
    red = 1.0;
    green = 1.0;
    blue = 0.0;
  }
  if (0 <= val && val < 0.25) {
    red = 1.0;
    green = 0.0;
    blue = 0.0;
  }
  glColor3f(red, green, blue);
  glBegin(GL_QUADS);
  glVertex2d(tlx+0.01, tly-0.01);
  glVertex2d(tlx+val*gap_x-0.01, tly-0.01);
  glVertex2d(tlx+val*gap_x-0.01, tly-gap_y+0.01);
  glVertex2d(tlx+0.01, tly-gap_y+0.01);
  glEnd();
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2d(tlx, tly);
  glVertex2d(tlx+gap_x, tly);
  glVertex2d(tlx+gap_x, tly-gap_y);
  glVertex2d(tlx, tly-gap_y);
  glEnd();
  print_bitmap (1.0, 0.8, 1.0, tlx, tly + 0.05, 0.0, title, GLUT_BITMAP_HELVETICA_10);
}

void draw_window (void)
  // Draw main GLUT window
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // Point in space
  glPushMatrix();
  switch (stage) {
    // TO DO: a tittle for each scene
    case STARTING:
      print_bitmap(0.8, 0.8, 0.8, -2.2, -0.2, 0.0, "A SURVIVAL GAME", GLUT_BITMAP_TIMES_ROMAN_24);
      break;
    case MIDDLE:
      switch (my_player.status) {
        case NOT_PLAYING:
          print_bitmap(0.8, 0.8, 0.8, -1.85, -1.4, 0.0, "Vitals", GLUT_BITMAP_TIMES_ROMAN_24);
          draw_control_bar (-1.9, 1.0, 1.5, 0.2, my_player.boat/100.0, 0.0, 1.0, 0.0, "Building boat");
          draw_control_bar (-1.9, 0.4, 1.5, 0.2, my_player.stamina/100.0, 0.0, 1.0, 0.0, "Stamina");
          draw_control_bar (-1.9, -0.2, 1.5, 0.2, my_player.sanity/100.0, 0.0, 1.0, 0.0, "Sanity");
          draw_control_bar (-1.9, -0.8, 1.5, 0.2, my_player.time_left/30.0, 0.0, 1.0, 0.0, "Time");
          print_bitmap(1.0, 1.0, 1.0, 0.6, 0.9, 0.0, "swing horizontally to chop woods and build a boat", GLUT_BITMAP_HELVETICA_12);
          print_bitmap(1.0, 1.0, 1.0, 0.6, 0.5, 0.0, "swing vertically to cast fishing rod for food", GLUT_BITMAP_HELVETICA_12);
          print_bitmap(1.0, 1.0, 1.0, 0.6, 0.1, 0.0, "press button a to have a good sleep", GLUT_BITMAP_HELVETICA_12);
          break;
        case BUILDING:
          print_bitmap(1.0, 0.8, 1.0, 1.5, -1.6, 0.0, "Hope ...", GLUT_BITMAP_TIMES_ROMAN_24);
          draw_control_bar (1.5, 1.6, 0.8, 0.1, my_player.boat/100.0, 0.0, 1.0, 0.0, "Building boat");
          draw_control_bar (1.5, 1.3, 0.8, 0.1, my_player.stamina/100.0, 0.0, 1.0, 0.0, "Stamina");
          draw_control_bar (1.5, 1.0, 0.8, 0.1, my_player.sanity/100.0, 0.0, 1.0, 0.0, "Sanity");
          draw_control_bar (1.5, 0.7, 0.8, 0.1, my_player.time_left/30.0, 0.0, 1.0, 0.0, "Time");
          print_bitmap(1.0, 1.0, 1.0, -2.2, 0.7, 0.0, "press b to stop working", GLUT_BITMAP_HELVETICA_12);
          break;
        case EATING:
          print_bitmap(1.0, 0.8, 1.0, 1.5, -1.6, 0.0, "Gaining energy ...", GLUT_BITMAP_TIMES_ROMAN_24);
          draw_control_bar (1.5, 1.6, 0.8, 0.1, my_player.boat/100.0, 0.0, 1.0, 0.0, "Building boat");
          draw_control_bar (1.5, 1.3, 0.8, 0.1, my_player.stamina/100.0, 0.0, 1.0, 0.0, "Stamina");
          draw_control_bar (1.5, 1.0, 0.8, 0.1, my_player.sanity/100.0, 0.0, 1.0, 0.0, "Sanity");
          draw_control_bar (1.5, 0.7, 0.8, 0.1, my_player.time_left/30.0, 0.0, 1.0, 0.0, "Time");
          print_bitmap(1.0, 1.0, 1.0, -2.2, 0.7, 0.0, "press b to stop eating", GLUT_BITMAP_HELVETICA_12);
          break;
        case SLEEPING:
          print_bitmap(1.0, 0.8, 1.0, 1.5, -1.6, 0.0, "Good night ...", GLUT_BITMAP_TIMES_ROMAN_24);
          draw_control_bar (1.5, 1.6, 0.8, 0.1, my_player.boat/100.0, 0.0, 1.0, 0.0, "Building boat");
          draw_control_bar (1.5, 1.3, 0.8, 0.1, my_player.stamina/100.0, 0.0, 1.0, 0.0, "Stamina");
          draw_control_bar (1.5, 1.0, 0.8, 0.1, my_player.sanity/100.0, 0.0, 1.0, 0.0, "Sanity");
          draw_control_bar (1.5, 0.7, 0.8, 0.1, my_player.time_left/30.0, 0.0, 1.0, 0.0, "Time");
          print_bitmap(1.0, 1.0, 1.0, -2.2, 0.7, 0.0, "press b to stop sleeping", GLUT_BITMAP_HELVETICA_12);
          break;
      }
      break;
    case ENDING:
      if (!my_player.alive) {
        print_bitmap(1.0, 0.8, 1.0, -0.4, 1.0, 0.0, "Game over ...", GLUT_BITMAP_TIMES_ROMAN_24);
        print_bitmap(1.0, 0.8, 1.0, -0.7, -1.5, 0.0, "@ ARM Hackathon 2016", GLUT_BITMAP_HELVETICA_18);
      }
      else print_bitmap(0.2, 0.2, 0.2, -0.7, -1.4, 0.0, "@ ARM Hackathon 2016", GLUT_BITMAP_TIMES_ROMAN_24);
      break;
  }
  glPopMatrix();
  
  // Scaled up by aspect_ratio
  // Note that texture image is inverted
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  
  switch (stage) {
    case STARTING:
      bind_texture(starting_texture, 0.8, 0.7, 0.8);
      break;
    case MIDDLE:
      switch (my_player.status) {
        case NOT_PLAYING:
          bind_texture(not_playing_texture, 0.6, 0.8, 0.4);
          break;
        case BUILDING:
          bind_texture(building_texture, 0.8, 0.8, 1.0);
          break;
        case EATING:
          bind_texture(eating_texture, 0.8, 0.6, 0.4);
          break;
        case SLEEPING:
          bind_texture(sleeping_texture, 0.8, 0.6, 0.7);
          break;
      }
      break;
    case ENDING:
      if (!my_player.alive) bind_texture(dead_texture, 0.6, 0.6, 0.8);
      else bind_texture(alive_texture, 1.0, 1.0, 1.0);
      break;
  }
  
  glTranslated(0.0, 0.0, 0.5); // pushed 'into' screen
  //glColor3f(0.6, 0.3, 0.3);
  //glColor3f(0.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 1.0);
  glVertex2d(-1.0, -1.0);
  glTexCoord2d(1.0, 1.0);
  glVertex2d(1.0, -1.0);
  glTexCoord2d(1.0, 0.0);
  glVertex2d(1.0, 1.0);
  glTexCoord2d(0.0, 0.0);
  glVertex2d(-1.0, 1.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  
  glutSwapBuffers();
}

void update_state (void)
  // The GLUT idle function, called every time round the event loop
{
  // Check for end game states
  if (my_player.escaped || !my_player.alive) stage = ENDING;

  // Refresh the visualization
  draw_window();
}


void glut_key (unsigned char k, int x, int y)
  // Callback for key presses in all windows
{
  switch(k) {
  case 27: case 'q': case 'Q':
    // Escape or q or Q  - exit
    exit(0);
    break;
  case 'i':
    // Enter game or leave action
    if (stage == STARTING && my_player.status == NOT_PLAYING) stage = MIDDLE;
    if (stage == MIDDLE && my_player.status != NOT_PLAYING) my_player.status = NOT_PLAYING;
    break;
  case 'j':
    // Build
    if (stage == MIDDLE && my_player.status == NOT_PLAYING) {
      my_player.status = BUILDING;
      break;
    }
    if (stage == MIDDLE && my_player.status == BUILDING) my_player.update();
    break;
  case 'k':
    // Eat
    if (stage == MIDDLE && my_player.status == NOT_PLAYING) {
      my_player.status = EATING;
      break;
    }
    if (stage == MIDDLE && my_player.status == EATING) my_player.update();
    break;
  case 'l':
    // Sleep
    if (stage == MIDDLE && my_player.status == NOT_PLAYING) {
      my_player.status = SLEEPING;
      break;
    }
    if (stage == MIDDLE && my_player.status == SLEEPING) my_player.update();
    break;
  }
}

bool setup_texture (string filename, GLuint &id)
{
  int width, height;
  unsigned char* tex = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  
  if (tex != NULL) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    if (glGetError() != GL_NO_ERROR) {
      cerr << "Error when binding " << id << endl;
    return false;
    }
  }
  else return false;
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex);
  
  SOIL_free_image_data(tex);
  
  if (glGetError() != GL_NO_ERROR) {
    cerr << "Error when creating texture image " << id << endl;
    return false;
  }
  else return true;
}

int main (int argc, char* argv[])
  // Initializes GLUT windows and charge state, then enters GLUT main loop
{
  // Main GLUT window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
  main_window = glutCreateWindow("Survival game");
  glEnable(GL_DEPTH_TEST);
  glDrawBuffer(GL_BACK);
  glutDisplayFunc(draw_window);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_state);
  glutKeyboardFunc(glut_key);
  texture_available = setup_texture("../img/island.png", starting_texture) && setup_texture("../img/red_forest.jpg", not_playing_texture) && setup_texture("../img/building.jpg", building_texture) && setup_texture("../img/eating.jpg", eating_texture) && setup_texture("../img/sleeping.jpg", sleeping_texture) && setup_texture("../img/dead.jpg", dead_texture) && setup_texture("../img/alive.jpg", alive_texture);
  if (!texture_available) cerr << "Error when loading texture image" << endl;
  
  stage = STARTING;
  glutMainLoop();
  
  return 0;
}
