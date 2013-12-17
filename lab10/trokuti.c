// trokuti - Hip - 2009-12-19
// 'n' - dubina rekurzije + 1
// 'N' - dubina rekurzije - 1

#include <GL/glut.h>
#include <stdlib.h>

#define SQRT3 1.732050807568877

// maksimalna dubina rekurzije
#define MAXDUBINA 8

int dubina = 0; // dubina rekurzije

typedef struct { double x; double y; } vrh;

void trokut(int n, vrh v1, vrh v2, vrh v3) {
vrh v12, v23, v31;

  if(n) {
    v12.x = (v1.x + v2.x) / 2.0;
    v12.y = (v1.y + v2.y) / 2.0;

    v23.x = (v2.x + v3.x) / 2.0;
    v23.y = (v2.y + v3.y) / 2.0;

    v31.x = (v3.x + v1.x) / 2.0;
    v31.y = (v3.y + v1.y) / 2.0;

    trokut(n - 1, v1, v12, v31);
    trokut(n - 1, v12, v2, v23);
    trokut(n - 1, v31, v23, v3);
  } else {
    glBegin(GL_TRIANGLES);
      glVertex2d(v1.x, v1.y);
      glVertex2d(v2.x, v2.y);
      glVertex2d(v3.x, v3.y);
    glEnd();
  }
} // trokut

void iscrtaj(void) {
vrh v1 = {0.0, 2.0},
    v2 = {SQRT3, -1.0},
    v3 = {-SQRT3, -1.0};

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 0.0);
  trokut(dubina, v1, v2, v3); 

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  float a = 2.0, b;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(w > h) {
    b = a * (float)w / (float)h;
    glOrtho(-b + 0.5, b - 0.5, -a + 1.0, a, -a, a);
  } else {
    b = a * (float)h / (float)w;
    glOrtho(-a + 0.5, a - 0.5, -b + 1.0, b, -a, a);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 'n') { if(++dubina > MAXDUBINA) dubina = MAXDUBINA; }
  if(c == 'N') { if(--dubina < 0) dubina = 0; }
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

