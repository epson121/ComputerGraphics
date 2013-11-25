// GLelipse.c

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define XMIN -10.0
#define XMAX 10.0
#define YMIN -10.0
#define YMAX 10.0

void elipsa(double a, double b) {
  double t;

  glBegin(GL_LINE_LOOP);
    glVertex2d(a, 0);
    for(t = 0.0; t < 2.0 * M_PI; t += M_PI / 100.0) 
      glVertex2d(a * cos(t), b * sin(t));
  glEnd();
} // elipsa

// ova je rutina ekvivalent rutini paint u Javi:
void iscrtaj(void) {
  // punjenje zaslona bojom pozadine koja se postavlja s glClearColor()
  glClear(GL_COLOR_BUFFER_BIT);

  // operacije se odnose na matricu transformacija i pogleda (MODELVIEW)
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // koordinatne osi
  glColor3d(0.0, 0.0, 0.0); // crna
  glBegin(GL_LINES);
    glVertex2d(XMIN, 0.0);
    glVertex2d(XMAX, 0.0);
    glVertex2d(0.0, YMIN);
    glVertex2d(0.0, YMAX);
  glEnd();

  glTranslated(4.0, 0.0, 0.0);
  glRotated(-30.0, 0.0, 0.0, 1.0); // oko osi z
  glColor3d(1.0, 0.0, 0.0); // crvena
  elipsa(6.0, 3.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotated(-30.0, 0.0, 0.0, 1.0); // oko osi z
  glTranslated(4.0, 0.0, 0.0);
  glColor3d(0.0, 0.0, 1.0); // plava
  elipsa(6.0, 3.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(-1.0, 1.0, 1.0); // zrcaljenje na osi y
  glTranslated(3.0, 0.0, 0.0);
  glRotated(75.0, 0.0, 0.0, 1.0); // oko osi z
  glColor3d(0.0, 1.0, 0.0); // zelena
  elipsa(4.0, 1.0);

  glFlush();
} // iscrtaj

void skaliraj(int w, int h) {
// sistem daje vrijednosti w i h koje predstavljaju širinu i visinu prozora
// rutina se automatski poziva prilikom inicijalizacije, ali i kada dođe do
// promjene veličine prozora u koji se iscrtava, 

  double xmin = XMIN, xmax = XMAX;
  double xrange, yrange;

  // iscrtavanje u čitav prozor
  glViewport(0, 0, w, h);

  // operacije se odnose na matricu projekcije (PROJECTION)
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // gluOrtho2D ekvivalentno je rutini GKS koju ste implementirali u Javi!
  gluOrtho2D(XMIN, XMAX, YMIN, YMAX);

  // varijanta koja čuva proporcije, tj. omjer visine i širine objekata
  // xrange = xmax - xmin;
  // yrange = h * xrange / w;
  // gluOrtho2D(xmin, xmax, -yrange / 2.0, yrange / 2.0);

} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
} // tipka

int main(int argc, char** argv) {
  glutInit(&argc, argv); // -geometry 600x600+60+30
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(60, 30);
  glutInitWindowSize(600, 600);
  glutCreateWindow("GLelipse");

  glClearColor(1.0, 1.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutMainLoop();
  return 0;
} // main
