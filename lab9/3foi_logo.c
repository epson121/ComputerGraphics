// Lstozac.c // Luka Rajcevic // 2011-11-21 // 2013-12-02

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926

float bijelo[] = {1.0f, 1.0f, 1.0f, 1.0f};
float crno[] = {0.0f, 0.0f, 0.0f, 1.0f};
float smedje[] = {238.0f / 255.0f, 154.0f / 255.0f, 73.0f / 255.0f};
float crveno1[] = {200.0f / 200.0f, 0.0f / 255.0f, 0.0f / 255.0f};
float crveno2[] = {200.0f / 200.0f, 50.0f / 255.0f, 20.0f / 255.0f};
float orange[] = {255.0f / 255.0f, 140.0f / 255.0f, 0.0f};
int px = 20;
int py = 20; 
int pz = 25;
int kx = 0;
int ky = 0; 
int kz = 0;

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

  gluLookAt(px, py, pz, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0);

    glPushMatrix(); // pamtimo da smo u ishodištu
    // postavljamo svjetlo 0 na odgovarajuću poziciju
    glTranslated(0.0, 0.0, 20.0);
    svjetlo0();
    glTranslated(20.0, 0.0, 20.0);
    svjetlo0();
    glTranslated(-20.0, 0.0, 20.0);
    svjetlo0();
    // položaj svjetla 0 označit ćemo bijelom kockicom
    glMaterialfv(GL_FRONT, GL_EMISSION, bijelo);
    kocka(0.5);
  glPopMatrix(); // vraćamo se u ishodište
  
  double cubeSize = 2.5;
  // letter F (base)
  glRotated(kx, 1.0, 0.0, 0.0);
  glRotated(ky, 0.0, 1.0, 0.0);
  glRotated(kz, 0.0, 0.0, 1.0);
  glPushMatrix();
    glTranslated(-4*cubeSize, -0.5 * cubeSize, 0.0);
    glPushMatrix();
      int i;
      for (i = 0; i < 5; i++) {
        if (i % 2 == 0)
          glMaterialfv(GL_FRONT, GL_EMISSION, crveno1);
        else
          glMaterialfv(GL_FRONT, GL_EMISSION, crveno2);
        kocka(cubeSize);
        glTranslated(0.0, 0.0, cubeSize);
      }
      glTranslated(0.0, cubeSize/3, 0.0);
      kocka(cubeSize);
      glTranslated(0.0, cubeSize, cubeSize/6);
      kocka(cubeSize);
    glPopMatrix();

    // letter F strikethrough
    glPushMatrix();
      glTranslated(0.0, cubeSize, cubeSize*3);
      kocka(cubeSize);
      glTranslated(0.0, -cubeSize*2, 0.0);
      kocka(cubeSize);
    glPopMatrix();


    //letter O
    glPushMatrix();
      glTranslated(0.0, 4*cubeSize, 0.0);
      kocka(cubeSize);
      glTranslated(0.0, cubeSize, cubeSize);
      kocka(cubeSize);

      // orange part
      glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, orange);
        glTranslated(0.0, -cubeSize*0.8, cubeSize*0.2);
        kocka(cubeSize*0.7);
        glTranslated(0.0, 0.0, cubeSize*0.7);
        kocka(cubeSize*0.7);
      glPopMatrix();
      
      glMaterialfv(GL_FRONT, GL_EMISSION, crveno1);
      glTranslated(0.0, 0.0, cubeSize);
      kocka(cubeSize);
      glTranslated(0.0, -cubeSize, cubeSize);
      kocka(cubeSize);
      glTranslated(0.0, -cubeSize, -cubeSize);
      kocka(cubeSize);
      glTranslated(0.0, 0.0, -cubeSize);
      kocka(cubeSize);
    glPopMatrix();

    glPushMatrix();
      glTranslated(0.0, 7*cubeSize, 0.0);
      i = 0;
      for (i = 0; i < 4; i++) {
         if (i % 2 == 0)
          glMaterialfv(GL_FRONT, GL_EMISSION, crveno1);
        else
          glMaterialfv(GL_FRONT, GL_EMISSION, crveno2);
        kocka(cubeSize);
        glTranslated(0.0, 0.0, cubeSize);
      }
      glTranslated(0.0, 0.0, cubeSize);
      kocka(cubeSize);
    glPopMatrix();
  glPopMatrix();

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  double xmin = -20.0, xmax = 20.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(xmin, xmax, -yrange / 2.0, yrange / 2.0, 10.0, 100.0);
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == '0') glEnable(GL_LIGHT0);
  if(c == '=') glDisable(GL_LIGHT0);
  if(c == 'v') { if(++verzija > 3) verzija = 0; }
  if(c == 'N') { if(++nn > 50) nn = 50; }
  if(c == 'n') { if(--nn < 3) nn = 3; }
  if(c == 'a') { px += 1; }
  if(c == 'A') { px -= 1; }
  if(c == 's') { py += 1; }
  if(c == 'S') { py -= 1; }
  if(c == 'w') { pz += 1; }
  if(c == 'W') { pz -= 1; }
} // tipka

void SpecialInput(int key, int x, int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      ky += 3;
      break;  
    case GLUT_KEY_DOWN:
      ky -= 3;
      break;
    case GLUT_KEY_LEFT:
      kx -= 3;
      break;
    case GLUT_KEY_RIGHT:
      kx += 3;
    break;
  }
}


void rotirajT(int id)
{
  kz += 3.0;
  glutPostRedisplay();
  // čekaj 50 milisekundi i ponovo pozovi rotirajT
  glutTimerFunc(50, rotirajT, 0);
} // rotirajT

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(640, 480);
  glutCreateWindow("Anemometer");

  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);


  glEnable(GL_LIGHTING); // omogućava osvjetljavanje
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glEnable(GL_LIGHT0); // uključuje svjetlo 0

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutSpecialFunc(SpecialInput);
  //glutIdleFunc(rotiraj);
  glutTimerFunc(50, rotirajT, 0); // prvi poziv rutine rotirajT

  glutMainLoop();
  return 0;
} // main

