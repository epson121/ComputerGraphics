// polikocka.c // Ivan Hip // 2011-11-14

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926

double kut = 0.0;

void osi(double a) {
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(a, 0.0, 0.0); // x-os
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, a, 0.0); // y-os
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, a); // z-os
  glEnd();
} // osi

void cone(double r, double h, int n) {

  double t;
  double step = (2.0 * PI)/n;
  double phi;
  double x, y;
  
  int i1 = 0;
  int i2 = 0;
  
  glBegin(GL_TRIANGLES);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i1 == 0) {
        glColor3d(1.0, 0.0, 0.0);
        i1 = 1;
      } else {
        glColor3d(1.0, 0.2, 1.0);
        i1 = 0;
      }
      glVertex3d(0, 0, 0);
      //glVertex3d(r * cos(t), r * sin(t), 0);
      glVertex3d(r * cos(t), 0, -r * sin(t));
      glVertex3d(r * cos(t+step), 0, -r * sin(t+step));
      //glVertex3d(0, 0, 0);
    }
  glEnd();
  
  glBegin(GL_TRIANGLES);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i2 == 0) {
        glColor3d(1.0, 1.0, 0.0);
        i2 = 1;
      } else {
        glColor3d(1.0, 1.0, 1.0);
        i2 = 0;
      }
      glVertex3d(0, h, 0);
      //glVertex3d(x, y, 0);
      glVertex3d(r * cos(t), 0, r * sin(t));
      glVertex3d(r * cos(t+step), 0, r * sin(t+step));
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

  gluLookAt(32.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  glRotated(kut, 0.0, 0.0, 1.0);
  glRotated(kut, 0.0, 1.0, 0.0);
  glRotated(kut, 1.0, 0.0, 0.0);

  osi(20.0);
  
  glTranslated(d, d, d);
  cone(2.5, 5.0, 20);

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
  glutCreateWindow("polikocka");

  glShadeModel(GL_FLAT);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);

  glutMainLoop();
  return 0;
} // main
