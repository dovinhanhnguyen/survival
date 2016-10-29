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

void draw_window (void)
  // Draw main GLUT window
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // point in space
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  string s = "Hello";
  glRasterPos3f(1.0, 1.0, 0.0);
  for (int i = 0; i < s.length(); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex3d(1.0, 1.0, 0.0);
  glVertex3d(1.0, -1.0, 0.0);
  glVertex3d(-1.0, -1.0, 0.0);
  glVertex3d(-1.0, 1.0, 0.0);
  glEnd();
  glPopMatrix();
  
  // scaled up by aspect_ratio
  // texture image is inverted
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  if (texture_available) glBindTexture(GL_TEXTURE_2D, texture); // for now
  else glBindTexture(GL_TEXTURE_2D, texture_2); // for now
  glColor3f(1.0, 1.0, 1.0);
  glTranslated(0.0, 0.0, 0.5);
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
  // Update states

  // Refresh the visualization
  draw_window();
}

void mouse_button (int button, int state, int x, int y)
  // Callback for mouse button presses in the orbital view window
{
}

//~ vector2d screen_to_space (double x, double y)
  //~ // Convert position of mouse click in window to 2D coordinates in space
//~ {
  //~ return vector2d((x*2.0*SCALE*aspect_ratio/window_width-SCALE*aspect_ratio), (SCALE-y*2.0*SCALE/window_height));
//~ }

void glut_key (unsigned char k, int x, int y)
  // Callback for key presses in all windows
{
  switch(k) {
  case 27: case 'q': case 'Q':
    // Escape or q or Q  - exit
    exit(0);
    break;
  case 'n':
    // Next scene
    texture_available = !texture_available;
    break;
  }
}

void initialise (void)
  // Initialise something
{
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
  glutMouseFunc(mouse_button);
  glutKeyboardFunc(glut_key);
  texture_available = setup_texture("mars_4k_color.png", texture) && setup_texture("space.jpg", texture_2);
  
  glutMainLoop();
  
  return 0;
}
