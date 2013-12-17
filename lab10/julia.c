// julia - Hip - 2009-12-20 - modificirano: 2013-01-14
// Julia-ovi skupovi (Julia sets) - granice područja
// konvergencije za funkciju
//         f(z) = lambda * z * (1 - z)
// najzanimljivije je područje 2.0 < lambda < 4.0
// (općenito, lambda može biti i kompleksan)
// 'l' - smanjuje lambda
// 'L' - povećava lambda

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double lambda = 2.0; // parametar
int npoints = 100000; // broj točaka
int sign = 1;

typedef struct {
  double x; // realni dio kompleksnog broja
  double y; // imaginarni dio kompleksnog broja
} complex;

complex iteriraj(double lambda, complex z) {
complex w, znext;
double wabs;

  w.x = 1.0 - 4.0 * z.x / lambda;     // Re(w)
  w.y = -4.0 * z.y / lambda;          // Im(w)
  wabs = sqrt(w.x * w.x + w.y * w.y); // |w|

  // slučajno odabiremo jedan od dva korijena
  if(rand() < RAND_MAX / 2) sign = 1; else sign = -1;  
  if(w.y > 0.0) {
    // Im(w) > 0 znači da je phi < 180 stupnjeva, pa je korijen u I. ili III. kvadrantu 
    znext.x = (1.0 + sign * sqrt((wabs + w.x) / 2.0)) / 2.0;
    znext.y = sign * sqrt((wabs - w.x) / 2.0) / 2.0;
  } else {
    // Im(w) < 0 znači da je phi > 180 stupnjeva, pa je korijen u II. ili IV. kvadrantu
    znext.x = (1.0 - sign * sqrt((wabs + w.x) / 2.0)) / 2.0;
    znext.y = sign * sqrt((wabs - w.x) / 2.0) / 2.0;
  }

  return znext;
} // iteriraj

void iscrtaj(void) {
  complex z = {0.7, 0.1};
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // nekoliko praznih iteracija
  for(i = 0; i < 100; i++)
    z = iteriraj(lambda, z);

  // iscrtavanje točaka
  glColor3f(1.0f, 1.0f, 0.0f);
  for(i = 0; i < npoints; i++) {
    z = iteriraj(lambda, z);
    glBegin(GL_POINTS);
      glVertex2d(z.x, z.y);
    glEnd();
  }

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  float a = 0.5f, b;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(w > h) {
    b = a * (float)w / (float)h;
    gluOrtho2D(0.0f, 2.0f * b, -a, a);
  } else {
    b = a * (float)h / (float)w;
    gluOrtho2D(0.0f, 2.0f * a, -b, b);
  }
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 'l') { lambda -= 0.01; }
  if(c == 'L') { lambda += 0.01; }
  printf("lambda = %lf\n", lambda);
  glutPostRedisplay();
} // tipka

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(argv[0]);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);

  glutMainLoop();
  return 0;
} // main

