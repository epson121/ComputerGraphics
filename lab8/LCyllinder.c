// Lstozac.c // Ivan Hip // 2011-11-21 // 2013-12-02

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926

float bijelo[] = {1.0f, 1.0f, 1.0f, 1.0f};
float crno[] = {0.0f, 0.0f, 0.0f, 1.0f};
float smedje[] = {238.0f / 255.0f, 154.0f / 255.0f, 73.0f / 255.0f};

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

void cylinder(double r, double h, int n) {

  double t;
  double step = (2.0 * PI)/n;
  double phi;
  double x, y;
  
  int i1 = 0;
  int i2 = 0;
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

 // baza stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala je u smjeru z za sve trokute
    glVertex3d(0.0, 0.0, h); // središte baze je u ishodištu
    t = 0.0;
    for(i = 0; i <= n; i++) {
      glVertex3d(r * cos(t), r * sin(t), h);
      t += 2.0 * M_PI / n;
    }
  glEnd();

  // body
  
  glBegin(GL_QUAD_STRIP);
     for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i1 == 0) {
        glColor3d(1.0, 0.6, 0.1);
        i1 = 1;
      } else {
        glColor3d(1.0, 0.8, 0.4);
        i1 = 0;
      }
      glNormal3d(cos(t), -sin(t), 0);
      glVertex3d(r * cos(t), -r * sin(t), 0);
      glNormal3d(cos(t), -sin(t), 0);
      glVertex3d(r * cos(t), -r * sin(t), h);
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
  gluLookAt(0.0, 40.0, 0.0, 0.0, 0.0, h / 2.0, 0.0, 0.0, 1.0);

  glPushMatrix(); // pamtimo da smo u ishodištu
    // postavljamo svjetlo 0 na odgovarajuću poziciju
    glTranslated(-8.0, 20.0, 3.0);
    svjetlo0();
    // položaj svjetla 0 označit ćemo bijelom kockicom
    glMaterialfv(GL_FRONT, GL_EMISSION, bijelo);
    kocka(0.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  glPopMatrix(); // vraćamo se u ishodište

  // rotacija stošca oko osi koja prolazi kroz plašt
  glTranslated(0.0, r, 0.0);
  glRotated(kut, 0.0, -r, h);
  glTranslated(0.0, -r, 0.0);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, smedje);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bijelo);
  glMaterialf(GL_FRONT, GL_SHININESS, 20.0); 

  /*switch(verzija) {
    case 0 : stozacV0(r, h, nn); break;
    case 1 : stozacV1(r, h, nn); break;
    case 2 : stozacV2(r, h, nn); break;
    case 3 : stozacV3(r, h, nn);
  }*/
  cylinder(6, 18, 15);

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
  kut += 3.0;
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

