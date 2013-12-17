// iskra - Hip - 2009-12-20
// 'n' - povechava dubinu rekurzije
// 'N' - smanjuje dubinu rekurzije
// - za ponovno iscrtavanje pritisnuti
//   bilo koju tipku

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define XMAX 1000

int max_dubina = 0; // dubina rekurzije
double s = 0.2; // skaliranje
double y[XMAX];

void initY(double a, double b) {
  int i;

  for(i = 0; i < XMAX; i++) y[i] = 0.0;
  y[0] = a;
  y[XMAX - 1] = b;
} // initY

// Box-Muller (Numerical Recipes)
double gauss() {
  static int zaliha = 0;
  static double na_zalihi = 0.0;
  double v1, v2, rsq, fac;

  if(zaliha) {
    zaliha = 0;
    return na_zalihi;
  } else {
    do {
      v1 = 2.0 * rand() / (double)RAND_MAX - 1.0;
      v2 = 2.0 * rand() / (double)RAND_MAX - 1.0;
      rsq = v1 * v1 + v2 * v2;
    } while(rsq >= 1.0);
    fac = sqrt(-2.0 * log(rsq) / rsq);
    na_zalihi = v1 * fac; zaliha = 1;
    return v2 * fac;
  }
} // gauss

void iteriraj(int dubina, int x0, int x1) {
  int xm;
  double r;

  if(dubina) 
    if(x1 - x0 > 1) {
      xm = (x1 + x0) / 2;
      if(y[xm] == 0.0) {
        r = s * gauss() * (double)(x1 - x0);
        y[xm] = 0.5 * (y[x0] + y[x1]) + r;
        iteriraj(dubina - 1, x0, xm);
        iteriraj(dubina - 1, xm, x1);
      }
    }
} // iteriraj

void iscrtaj(void) {
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  initY(-100.0, 100.0);
  iteriraj(max_dubina, 0, XMAX - 1);

  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_LINE_STRIP);
    for(i = 0; i < XMAX; i++) {
      if(y[i] != 0.0) 
        glVertex2d((double)i, y[i]);
    }
  glEnd();

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  float a = XMAX - 0, b;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  b = a * (float)h / (float)w;
  glOrtho(0, XMAX, -b / 2.0, b / 2.0, -1.0, 1.0);
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 'n') max_dubina++;
  if(c == 'N') if(--max_dubina < 0) max_dubina = 0;
  glutPostRedisplay();
} // tipka

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(argv[0]);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);

  glutMainLoop();
  return 0;
} // main

