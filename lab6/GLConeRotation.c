// GLkocka.c

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define XMIN -10.0
#define XMAX 10.0
#define YMIN -10.0
#define YMAX 15.0
#define PI 3.1415926

double kut = 0.0;

void cone(double r, double h, int n) {

  double t;
  double step = (2.0 * PI)/n;
  double phi;
  double x, y;
  glBegin(GL_LINE_LOOP);
    //glVertex3d(r * cos(0), r * sin(0), 0);
    glVertex3d(r * cos(0), 0, r * sin(0));
    for(t = 0.0; t < 2.0 * PI + step; t += step) 
      //glVertex3d(r * cos(t), r * sin(t), 0);
      glVertex3d(r * cos(t), 0, r * sin(t));
  glEnd();

  glBegin(GL_LINE_LOOP);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      glVertex3d(0, 0, 0);
      //glVertex3d(r * cos(t), r * sin(t), 0);
      glVertex3d(r * cos(t), 0, r * sin(t));
    }
  glEnd();
  
  glBegin(GL_LINE_LOOP);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      glVertex3d(0, h, 0);
      x = r * cos(t);
      y = r * sin(t);
      //glVertex3d(x, y, 0);
      glVertex3d(x, 0, y);
    }
  glEnd();
}

void pravac() {
  double t;
  double x1 = (1.0/3.0) * YMIN - 2.5;
  double x2 = (1.0/3.0) * YMAX - 2.5;
  glBegin(GL_LINES);
    glVertex3d(x1, YMIN, 0);
    glVertex3d(x2, YMAX, 0);
    //glVertex3d(x1, 0, YMIN);
    //glVertex3d(x2, 0, YMAX);
  glEnd();
}

void iscrtaj(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3d(1.0, 1.0, 1.0);
  glTranslated(0.0, -4.0, 0.0);
  glTranslated(-2.5, 0.0, 0.0);
  glRotated(kut, 2.5, 7.5, 0.0);
  glTranslated(2.5, 0.0, 0.0);
  cone(2.5, 7.5, 24);
  glColor3d(0.0, 1.0, 1.0);
  pravac();
  
  glutSwapBuffers();
} 

void skaliraj(int w, int h) {
  double xmin = -10.0, xmax = 10.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xmin, xmax, -yrange / 2.0, yrange / 2.0, xmin, xmax);
}

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

  glutCreateWindow("GLStozac");

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);
  glutMainLoop();
  return 0;
} // main
