#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

double zkamere = 25.0, kut = 0.0;

void kocka(double a) {
  glPushMatrix(); // spremamo poziciju prije lokalne transformacije
  glTranslated(-a / 2.0, -a / 2.0, -a / 2.0);
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
  glPopMatrix(); // vraćamo spremljenu poziciju prije povratka iz rutine
} // kocka

void trava(double d, int n) {
  double s = d / n;
  int i;

  glPushMatrix(); // spremamo poziciju prije lokalne transformacije
  glTranslated(-d / 2.0, -d / 2.0, 0.0);
  for(i = 0; i <= n; i++) {
    glBegin(GL_LINES);
      glVertex3d(i * s, 0.0, 0.0);
      glVertex3d(i * s, d, 0.0);
      glVertex3d(0.0, i * s, 0.0);
      glVertex3d(d, i * s, 0.0);
    glEnd();
  }
  glPopMatrix(); // vraćamo spremljenu poziciju prije povratka iz rutine
} // trava

void iscrtaj(void) {
  double a = 2.0; // duljina stranice kocke

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // transformacija u koordinatni sustav kamere (KSK)
  gluLookAt(10.0, -20.0, zkamere, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  glColor3d(0.0, 1.0, 0.0);
  trava(20.0, 40);

  glColor3d(1.0, 1.0, 0.0);
  glTranslated(0.0, 0.0, a / 2.0);
  kocka(a); // prva kocka od dolje

  glTranslated(0.0, 0.0, a);
  kocka(a); // druga kocka od dolje

  glTranslated(0.0, 0.0, a);
  glPushMatrix(); // prije nego zarotiramo donji krak spremamo poziciju
    glRotated(-2.0 * kut, 0.0, 0.0, 1.0); // krak rotiramo oko z osi
    kocka(a);
    glTranslated(a, 0.0, 0.0);
    glRotated(2.0 * kut, 1.0, 0.0, 0.0);
    kocka(a);
    glTranslated(a, 0.0, 0.0);
    kocka(a); // vanjska kocka koja se okreće oko osi kraka
  glPopMatrix(); // vraćamo se na spremljenu poziciju

  glColor3d(1.0, 0.0, 0.0);
  glTranslated(0.0, 0.0, a);
  glPushMatrix();
    glRotated(2.0 * kut, 0.0, 0.0, 1.0); // krak rotiramo oko z osi
    kocka(a); // četvrta kocka od dolje (ona je mirna)
  glPopMatrix();
  glColor3d(1.0, 1.0, 0.0);
  glTranslated(0.0, 0.0, a);
  // rotacija gornjeg kraka - nema potrebe spremati poziciju
  // jer je to zadnje što iscrtavamo
  glRotated(-2.0 * (kut), 0.0, 0.0, 1.0); // krak rotiramo oko z osi
  kocka(a);
  glTranslated(a, 0.0, 0.0);
  glRotated(2.0 * kut, 1.0, 0.0, 0.0);
  kocka(a);
  glTranslated(a, 0.0, 0.0);
  kocka(a); // vanjska kocka koja se okreće oko osi kraka

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  double xmin = -10.0, xmax = 10.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(xmin, xmax, -yrange / 2.0, yrange / 2.0, 10.0, 50.0);
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
} // tipka

void rotiraj(void) {
   kut += 2.0;
   if(kut > 360.0) {
     kut -= 360.0;
     zkamere -= 3.0; // poslije punog kruga spusti kameru
     if(zkamere < 0.0) exit(0);
   }
   glutPostRedisplay();
} // rotiraj

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("GL-F");

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);
  glutMainLoop();
  return 0;
} // main