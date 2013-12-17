// plazma - Hip - 2009-12-21
// 'n' - povechava dubinu rekurzije
// 'N' - smanjuje dubinu rekurzije
// - za ponovno iscrtavanje pritisnuti
//   bilo koju tipku

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define XMAX 1024
#define YMAX 1024

int max_dubina = 0; // dubina rekurzije
double s = 0.1; // skaliranje
double z[XMAX][YMAX];

GLubyte pix[XMAX][YMAX][3];

void initZ(double a, double b, double c, double d) {
  int i, j;

  for(i = 0; i < XMAX; i++)
    for(j = 0; j < YMAX; j++) z[i][j] = 0.0;
  z[0][0] = a;
  z[XMAX - 1][0] = b;
  z[XMAX - 1][YMAX - 1] = c;
  z[0][YMAX - 1] = d;
} // initZ

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

void iteriraj(int dubina, int x0, int x1, int y0, int y1) {
  int xm, ym;
  double r;

  if(dubina) {
    if(x1 - x0 > 1) {
      xm = (x0 + x1) / 2;
      if(z[xm][y0] == 0.0) {
        r = s * gauss() * (double)(x1 - x0);
        z[xm][y0] = 0.5 * (z[x0][y0] + z[x1][y0]) + r;
      }
      if(z[xm][y1] == 0.0) {      
        r = s * gauss() * (double)(x1 - x0);
        z[xm][y1] = 0.5 * (z[x0][y1] + z[x1][y1]) + r;
      }
    }
    if(y1 - y0 > 1) {
      ym = (y0 + y1) / 2;
      if(z[x0][ym] == 0.0) {
        r = s * gauss() * (double)(y1 - y0);
        z[x0][ym] = 0.5 * (z[x0][y0] + z[x0][y1]) + r;
      }
      if(z[x1][ym] == 0.0) {
        r = s * gauss() * (double)(y1 - y0);
        z[x1][ym] = 0.5 * (z[x1][y0] + z[x1][y1]) + r;
      }
    }
    if((x1 - x0 > 1) && (y1 - y0 > 1)) {
      xm = (x0 + x1) / 2; ym = (y0 + y1) / 2;
      if(z[xm][ym] == 0.0) {        
        r = s * gauss() * (double)(x1 - x0 + y1 - y0) / 2.0;
        z[xm][ym] = 0.25 * (z[x0][y0] + z[x1][y0] +
          z[x1][y1] + z[x0][y1]) + r;
        iteriraj(dubina - 1, x0, xm, y0, ym);
        iteriraj(dubina - 1, xm, x1, y0, ym);
        iteriraj(dubina - 1, x0, xm, ym, y1);
        iteriraj(dubina - 1, xm, x1, ym, y1);
      }
    }
  }
} // iteriraj

void iscrtaj(void) {
  int i, j;
  double a;
  GLubyte b;

  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  initZ(-1.0, 1.0, -1.0, 1.0);
  iteriraj(max_dubina, 0, XMAX - 1, 0, YMAX - 1);

  for(i = 0; i < XMAX; i++) {
    for(j = 0; j < YMAX; j++) {
      a = z[i][j] + 128.0;
      if(a < 0.0) b = 0; else
        if(a > 255.0) b = 255;
          else b = (GLubyte)a;
      pix[i][j][0] = b;
      pix[i][j][1] = b / 2;
      pix[i][j][2] = 0;
    }
  }

  glWindowPos2i(0, 0);
  glDrawPixels(XMAX, YMAX, GL_RGB,
    GL_UNSIGNED_BYTE, pix);

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

