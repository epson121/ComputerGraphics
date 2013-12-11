// Lstozac.c // Ivan Hip // 2011-11-21 // 2013-12-02

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float bijelo[] = {1.0f, 1.0f, 1.0f, 1.0f};
float crno[] = {0.0f, 0.0f, 0.0f, 1.0f};
float smedje[] = {238.0f / 255.0f, 154.0f / 255.0f, 73.0f / 255.0f};
float zlatno[] = {255.0f / 255.0f, 215.0f / 255.0f, 0.0f / 255.0f};
float zlatno2[] = {218.0f / 255.0f, 165.0f / 255.0f, 32.0f / 255.0f};

double kut = 0.0;
int verzija = 0, nn = 16;

void normiraj(double *v) {
  double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] /= d; v[1] /= d; v[2] /= d;
} // normiraj

void vprodukt(double *v, double a0, double a1, double a2,
              double b0, double b1, double b2) {
  v[0] = a1 * b2 - a2 * b1;
  v[1] = a2 * b0 - a0 * b2;
  v[2] = a0 * b1 - a1 * b0;
} // vprodukt

void kocka(double a) {
  glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, a, 0.0);
    glVertex3d(a, a, 0.0); glVertex3d(a, 0.0, 0.0);

    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, a); glVertex3d(a, 0.0, a);
    glVertex3d(a, a, a); glVertex3d(0.0, a, a);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(0.0, 0.0, a); glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(a, 0.0, a); glVertex3d(a, 0.0, 0.0);

    glNormal3d(1.0, 0.0, 0.0);    
    glVertex3d(a, a, a); glVertex3d(a, a, 0.0);

    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, a, a); glVertex3d(0.0, a, 0.0);

    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, a); glVertex3d(0.0, 0.0, 0.0);
  glEnd();
} // kocka

void stozac(double r, double h, int n) {
  double t;
  int i;

  // baza stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, -1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, 0.0); // središte baze je u ishodištu
    t = 0.0;
    for(i = 0; i <= n; i++) {
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();

  // plašt stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala u vrhu stošca u smjeru +z
    glVertex3d(0.0, 0.0, h); // vrh stošca na visini h
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      glNormal3d(cos(t), sin(t), 0.0); // normale u xy ravnini - od središta
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();
}

void valjak(double r, double h, int n) {
  double t;
  int i;

  // baza stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, -1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, 0.0); // središte baze je u ishodištu
    t = 0.0;
    for(i = 0; i <= n; i++) {
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();

  // plašt valjka
  glBegin(GL_QUAD_STRIP);
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      glNormal3d(cos(t), sin(t), 1); // normale u xy ravnini - od središta
      glVertex3d(r * cos(t), r * sin(t), h);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, h); // središte baze je u ishodištu na visin h
    t = 0.0;
    for(i = 0; i <= n; i++) {
      glVertex3d(r * cos(t), r * sin(t), h);
      t += 2.0 * M_PI / n;
    }
  glEnd();
}

void kugla(double r, int pola) {
  double step1 = M_PI / nn;
  double step2 = 2 * M_PI / nn;
  double t, theta = 0, phi = 0;
  double x, y, z1, z2;

  glBegin(GL_QUAD_STRIP);
     for (theta = 0; theta < M_PI / pola; theta += step1) {
        z1 = r * cos(theta);
        z2 = r * cos(theta + step1);
        for (phi = 0; phi <= 2 * M_PI + step2; phi += step2) {
          x = r * cos(phi) * sin(theta);
          y = r * sin(theta) * sin(phi);
          glNormal3d(cos(phi) * sin(theta), sin(theta) * sin(phi), cos(theta));
          glVertex3d(x, y, z1);
          x = r * cos(phi) * sin(theta + step1);
          y = r * sin(theta + step1) * sin(phi);
          glNormal3d(cos(phi) * sin(theta + step1), sin(theta + step1) * sin(phi), cos(theta + step1));
          glVertex3d(x, y, z2);
        }
     }
  glEnd();
}

void svjetlo0() {
  float pozicija[] = {0.0f, 0.0f, 0.0f, 1.0f};
  // četvrti parametar postavljen na 1.0f definira "positional light"
  // na poziciji koju određuju prva tri parametra

  glLightfv(GL_LIGHT0, GL_DIFFUSE, bijelo);
  glLightfv(GL_LIGHT0, GL_SPECULAR, bijelo);
  glLightfv(GL_LIGHT0, GL_POSITION, pozicija);
} // svjetlo0

void iscrtaj(void) {
  double r = 6.0, h = 18.0; // polumjer baze i visina stošca

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // kamera gleda pola visine stošca iznad ishodišta
//  gluLookAt(0.0, 40.0, 0.0, 0.0, 0.0, h / 2.0, 0.0, 0.0, 1.0);
  gluLookAt(30.0, 10.0, 30.0, 0.0, 0.0, h / 2.0, 0.0, 0.0, 1.0);

  glPushMatrix(); // pamtimo da smo u ishodištu
    // postavljamo svjetlo 0 na odgovarajuću poziciju
   // glTranslated(-8.0, 20.0, 3.0);
    glTranslated(-8.0, 15.0, 10.0);
    svjetlo0();
    // položaj svjetla 0 označit ćemo bijelom kockicom
    glMaterialfv(GL_FRONT, GL_EMISSION, bijelo);
    kocka(0.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  glPopMatrix(); // vraćamo se u ishodište

  glMaterialfv(GL_FRONT, GL_DIFFUSE, zlatno);
  glMaterialfv(GL_BACK, GL_DIFFUSE, zlatno2);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bijelo);
  glMaterialf(GL_FRONT, GL_SHININESS, 20.0);  

  double a = 5.0;
  stozac(a, 15, nn);
  glTranslated(0.0, 0.0, 12.5);
  glRotated(-kut, 0.0, 0.0, 1.0);
  valjak(1, 3, nn);

  glTranslated(0.0, 0.0, 1.5);
  glRotated(-90, 1.0, 0.0, 0.0);
  valjak(0.7, 12, nn);
  glPushMatrix();
  glTranslated(-3.2, 0.0, 12.0);
  glRotated(90, 0.0, 1.0, 0.0);
  kugla(2.5, 2);

  glPopMatrix();
  glRotated(240, 0.0, 1.0, 0.0);
  valjak(0.7, 12, nn);
  glPushMatrix();
  glTranslated(-3.2, 0.0, 12.0);
  glRotated(90, 0.0, 1.0, 0.0);
  kugla(2.5, 2);

  glPopMatrix();
  glRotated(-120, 0.0, 1.0, 0.0);
  valjak(0.7, 12, nn);
  glTranslated(-3.2, 0.0, 12.0);
  glRotated(90, 0.0, 1.0, 0.0);
  kugla(2.5, 2);

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
  if(c == 's') glShadeModel(GL_SMOOTH);
  if(c == 'f') glShadeModel(GL_FLAT);
  if(c == 'D') glEnable(GL_DEPTH_TEST);
  if(c == 'd') glDisable(GL_DEPTH_TEST);
  if(c == 'C') glEnable(GL_CULL_FACE);
  if(c == 'c') glDisable(GL_CULL_FACE);
  if(c == 'B') glCullFace(GL_BACK);
  if(c == 'b') glCullFace(GL_FRONT);
  if(c == '0') glEnable(GL_LIGHT0);
  if(c == '=') glDisable(GL_LIGHT0);
  if(c == 'v') { if(++verzija > 3) verzija = 0; }
  if(c == 'N') { if(++nn > 50) nn = 50; }
  if(c == 'n') { if(--nn < 3) nn = 3; }
} // tipka

//void rotiraj(void) {
//   kut += 0.5;
//   glutPostRedisplay();
//} // rotiraj

void rotirajT(int id)
{
  kut += 1.0;
  glutPostRedisplay();
  // čekaj 50 milisekundi i ponovo pozovi rotirajT
  glutTimerFunc(50, rotirajT, 0);
} // rotirajT

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(640, 480);
  glutCreateWindow("Lstozac");

  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glEnable(GL_LIGHTING); // omogućava osvjetljavanje
  glEnable(GL_LIGHT0); // uključuje svjetlo 0

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  //glutIdleFunc(rotiraj);
  glutTimerFunc(50, rotirajT, 0); // prvi poziv rutine rotirajT

  glutMainLoop();
  return 0;
} // main
