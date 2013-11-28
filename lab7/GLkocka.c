// GLkocka.c

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

double kut = 0.0;

void kocka(double a) {
  glBegin(GL_LINE_LOOP);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(a, 0.0, 0.0);
    glVertex3d(a, a, 0.0);
    glVertex3d(0.0, a, 0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);
    glVertex3d(0.0, 0.0, a);
    glVertex3d(a, 0.0, a);
    glVertex3d(a, a, a);
    glVertex3d(0.0, a, a);
  glEnd();
  glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, a);
    glVertex3d(a, 0.0, 0.0);
    glVertex3d(a, 0.0, a);
    glVertex3d(a, a, 0.0);
    glVertex3d(a, a, a);
    glVertex3d(0.0, a, 0.0);
    glVertex3d(0.0, a, a);
  glEnd();
} // kocka



void elipsa(double a, double b) {
  double t;

  glBegin(GL_LINE_LOOP);
    glVertex2d(a, 0);
    for(t = 0.0; t < 2.0 * M_PI; t += M_PI / 100.0) 
      glVertex2d(a * cos(t), b * sin(t));
  glEnd();
} // elipsa

void iscrtaj(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3d(1.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotated(kut, 0.0, 0.0, 1.0);
  glRotated(kut, 0.0, 1.0, 0.0);
  glRotated(kut, 1.0, 0.0, 0.0);
  glTranslated(-4.0, -4.0, -4.0);
  kocka(2);

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  double xmin = -10.0, xmax = 10.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xmin, xmax, -yrange / 2.0, yrange / 2.0, xmin, xmax);
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
} // tipka

void rotiraj(void) {
   kut += 2;
   glutPostRedisplay();
} // rotiraj

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("GLkocka");

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);
  glutMainLoop();
  return 0;
} // main
