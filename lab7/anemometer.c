// polikocka.c // Ivan Hip // 2011-11-14

#include "shapes.h"

double kut = 0.0;

void osi(double a) {
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(a, 0.0, 0.0); // x-os
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, a, 0.0); // y-os
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, a); // z-os
  glEnd();
} // osi

void dtsphere(double r, int m, int n) {
  double stepM = M_PI/(m+1);
  double stepN = M_PI/(n+1);
  double t, theta = 0, phi = 0;
  double x1, y1, z1;
  double x2, y2, z2;
  int colorChange = 0;
 
  glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta < M_PI / 2 ; theta += stepN) { // remove /2 for sphere
      z1 = r * cos(theta);
      z2 = r * cos(theta + stepN);
     
      if (colorChange == 0) {
        colorChange = 1;
      } else {
        colorChange = 0;
      }
      for (phi = 0; phi <= 2 * M_PI + stepM; phi += stepM) {
        if (colorChange == 0) {
          glColor3d(0.5, 0.5, 0.5);
          colorChange = 1;
        } else {
          glColor3d(1.0, 1.0, 1.0);
          colorChange = 0;
        }
        x1 = r * cos(phi) * sin(theta);
        y1 = r * sin(theta) * sin(phi);
        x2 = r * cos(phi) * sin(theta+stepN);
        y2 = r * sin(theta+stepN) * sin(phi);
 
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
      }
    }
  glEnd();
}

void iscrtaj(void) {
  double a = 8.0; // duljina stranice kocke
  double d = 0.5; // odmak od osi

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3d(1.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(25, 0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  double sphere_radius = 1;
  double cone_height = 8;
  double top_cylinder_radius = 1;
  double cylinder_hand_length = 5;
  // base cone
  cone(2, cone_height, 20);
  glTranslated(0, 0, cone_height - top_cylinder_radius - 0.5);
  // cylinder at top
  glRotated(kut, 0.0, 0.0, 1.0);
  cylinder(0.5, top_cylinder_radius, 20);
  // move to the middle of the cylinder
  glTranslated(0, 0, 0.5);
  glRotated(90, 1.0, 0.0, 0.0);
  //first hand
  cylinder(0.2, cylinder_hand_length, 20);
  // half_sphere on first hand
  glPushMatrix();
    glTranslated(0.0, 0.0, cylinder_hand_length + sphere_radius - 0.05);
    glRotated(90, 0.0, 1.0, 0.0);
    dtsphere(sphere_radius, 10, 10);
  glPopMatrix();
  glRotated(120, 0.0, 1.0, 0.0);
  cylinder(0.2, cylinder_hand_length, 20);
  // half_sphere on second hand
  glPushMatrix();
    glTranslated(0.0, 0.0, cylinder_hand_length + sphere_radius - 0.05);
    glRotated(90, 0.0, 1.0, 0.0);
    dtsphere(sphere_radius, 10, 10);
  glPopMatrix();
  glRotated(120, 0.0, 1.0, 0.0);
  cylinder(0.2, cylinder_hand_length, 20);
  // half_sphere on thirdss hand
  glPushMatrix();
    glTranslated(0.0, 0.0, cylinder_hand_length + sphere_radius - 0.05);
    glRotated(90, 0.0, 1.0, 0.0);
    dtsphere(sphere_radius, 10, 10);
  glPopMatrix();


  glutSwapBuffers();
} // iscrtaj



void skaliraj(int w, int h) {
  double xmin = -10.0, xmax = 10.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(xmin, xmax, -yrange / 2.0, yrange / 2.0, 20.0, 50.0);
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 's') glShadeModel(GL_SMOOTH); // glatko sjenčanje
  if(c == 'f') glShadeModel(GL_FLAT); // ravnomjerno sjenčanje
  if(c == 'B') glCullFace(GL_BACK); // odbaciti poligone koje gledamo u stražnju stranu 
  if(c == 'b') glCullFace(GL_FRONT); // odbaciti poligone koje gledamu u prednju stranu
  if(c == 'C') glEnable(GL_CULL_FACE); // uključivanje selektivnog odbacivanja
  if(c == 'c') glDisable(GL_CULL_FACE); // isključivanje selektivnog odbacivanja
  if(c == 'D') glEnable(GL_DEPTH_TEST); // uključivanje testiranja dubine
  if(c == 'd') glDisable(GL_DEPTH_TEST); // isključivanje testiranja dubine
} // tipka

void rotiraj(void) {
   kut += 0.5;

   glutPostRedisplay();
} // rotiraj

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(800, 600);
  glutCreateWindow("anemometer");

  glShadeModel(GL_FLAT);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);

  glutMainLoop();
  return 0;
} // main
