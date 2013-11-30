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

void sphere(double r, int m, int n) {
  double step1 = PI/(n+1);
  double step2 = PI/(m+1);
  double drawStep = 0.01;
  double theta = 0;
  double phi = 0;
  double t;
  int i1 = 0;
  int i2 = 0;

  double x1, y1, z1;
  double x2, y2, z2;
  double x3, y3;
  double x4, y4;
  glBegin(GL_QUAD_STRIP);
     for (theta = 0; theta <= 2; theta += step1) {
        z1 = r * cos(theta);
        z2 = r * cos(theta + step1);
         if (i1 == 0) {
            i1 = 1;
          } else {
            i1 = 0;
          }
        for (phi = 0; phi <= 2 * PI; phi += step2) {
          if (i1 == 0) {
            glColor3d(1.0, 0.0, 0.0);
            i1 = 1;
          } else {
            glColor3d(1.0, 0.2, 1.0);
            i1 = 0;
          }
          x1 = r * cos(phi) * sin(theta);
          y1 = r * sin(theta) * sin(phi);
          x2 = r * cos(phi) * sin(theta+step1);
          y2 = r * sin(theta+step1) * sin(phi);
          x3 = r * cos(phi+step2) * sin(theta);
          y3 = r * sin(theta) * sin(phi+step2);
          x4 = r * cos(phi+step2) * sin(theta+step1);
          y4 = r * sin(theta+step1) * sin(phi+step2);
          glVertex3d(x1, y1, z1);
          glVertex3d(x2, y2, z2);
          glVertex3d(x3, y3, z1);
          glVertex3d(x4, y4, z2);
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

  gluLookAt(32.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  glRotated(kut, 0.0, 0.0, 1.0);
  glRotated(kut, 0.0, 1.0, 0.0);
  glRotated(kut, 1.0, 0.0, 0.0);

  osi(20.0);
  
  glTranslated(d, d, d);
  sphere(5, 10, 20);

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
