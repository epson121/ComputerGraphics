// Lstozac.c // Luka Rajcevic // 2011-11-21 // 2013-12-02

#include "shapes.h"

float bijelo[] = {1.0f, 1.0f, 1.0f, 1.0f};
float crno[] = {0.0f, 0.0f, 0.0f, 1.0f};
float smedje[] = {238.0f / 255.0f, 154.0f / 255.0f, 73.0f / 255.0f};
float crveno[] = {200.0f / 200.0f, 0.0f / 255.0f, 0.0f / 255.0f};
float sivo[] = {0.9f, 0.9f, 0.9f};
float zeleno[] = {0.0f, 1.0f, 0.0f};
float zuto[] = {1.0f, 1.0f, 0.0f};


double kut = 0.0;
double kut_offset = 3;
double k1 = 60;
double xx = 10;
int verzija = 0, nn = 16;

float smjer_snopa[] = {1.0f, -1.0f, -1.0f};
float phi = 30.0; // kut u stupnjevima


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

void svjetlo0() {
  float pozicija[] = {0.0f, 0.0f, 0.0f, 1.0f};
  // četvrti parametar postavljen na 1.0f definira "positional light"
  // na poziciji koju određuju prva tri parametra

  glLightfv(GL_LIGHT0, GL_DIFFUSE, bijelo);
  glLightfv(GL_LIGHT0, GL_SPECULAR, bijelo);
  glLightfv(GL_LIGHT0, GL_POSITION, pozicija);
} // svjetlo0

 void svjetlo1(float x, float y, float z) {
  //float pozicija[] = {2.0f, -5.0f, -2.0f, 1.0f};
  float pozicija[] = {0.0f, 0.0f, 0.0f, 1.0f};
  float smjer_snopa[] = {x, y, z};

  glLightfv(GL_LIGHT1, GL_POSITION, pozicija);
  glLightfv(GL_LIGHT1, GL_SPECULAR, zeleno);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, zeleno);

  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, smjer_snopa); 
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, phi);
} // svjetlo1


void iscrtaj(void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(30.0, 0, xx, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);


  glPushMatrix(); // pamtimo da smo u ishodištu
    // postavljamo svjetlo 0 na odgovarajuću poziciju
    glTranslated(10.0, 0.0, 10.0);
    svjetlo0();
    // položaj svjetla 0 označit ćemo bijelom kockicom
    glMaterialfv(GL_FRONT, GL_EMISSION, bijelo);
    kocka(0.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  glPopMatrix(); // vraćamo se u ishodište

  /*
  glPushMatrix();
    glTranslated(10.0, 0.0, 3.0);
    svjetlo1(-1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, bijelo);
    kocka(0.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  glPopMatrix();
  */

  glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
  //glMaterialfv(GL_BACK, GL_DIFFUSE, smedje);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bijelo);
  glMaterialf(GL_FRONT, GL_SHININESS, 20.0); 

  // cuboid
  double c_h = 0.3;
  double n = 6;
  double c_r = 3;

  double small_r = 0.2;
  double small_h = 3;

  double cyl_s1_r = 0.2;
  double cyl_s1_h = 0.35;
  double cyl_s1_n = 20;

  double cyl_s2_r = 0.18;
  double cyl_s2_h = 1.5;
  double cyl_s2_n = 20;

  double cyl_s3_r = 0.08;
  double cyl_s3_h = 4;
  double cyl_s3_n = 20;

  double sphere_r = 1;
  double sphere_m = 30;
  double sphere_n = 30;

  cylinder(c_r, c_h, n);
  glTranslated(0.0, 0.0, c_h);
  cylinder(c_r/3, c_h*3, n);
  glTranslated(0.0, 0.0, c_h*3);
  cylinder(c_r/9, c_h*15, n);

  glTranslated(0.0, 0.0, c_h*14);
  //glPushMatrix();
    


    glRotated(90, 0.0, 0.0, 1.0);
    glRotated(90, 0.0, 1.0, 0.0);

    // rotacija gornjih 6 valjaka
    glRotated(kut, 1.0, 0.0, 0.0);

    cylinder(small_r, small_h, n-2);
    glPushMatrix();
      glTranslated(0.0, 0.0, small_h);
      glRotated(90, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.0, -cyl_s1_h/2);
      cylinder(cyl_s1_r, cyl_s1_h, cyl_s1_n);
      glTranslated(0.0, 0.0, cyl_s1_h/2);
      glRotated(-90, 1.0, 0.0, 0.0);
      glRotated(90 - (5 * kut_offset), 0.0, 1.0, 0.0);
      cylinder(cyl_s2_r, cyl_s2_h, cyl_s2_n);
      glTranslated(0.0, 0.0, cyl_s2_h);
      cylinder(cyl_s3_r, cyl_s3_h, cyl_s3_n);
      glTranslated(0.0, 0.0, cyl_s3_h*0.72);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
      half_sphere(sphere_r, sphere_m, sphere_n);
    glPopMatrix();


    glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
    glRotated(60, 1.0, 0.0, 0.0);
    cylinder(small_r, small_h, n-2);
    glPushMatrix();
       glTranslated(0.0, 0.0, small_h);
      glRotated(90, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.0, -cyl_s1_h/2);
      cylinder(cyl_s1_r, cyl_s1_h, cyl_s1_n);
      glTranslated(0.0, 0.0, cyl_s1_h/2);
      glRotated(-90, 1.0, 0.0, 0.0);
      glRotated(90 - (5 * kut_offset), 0.0, 1.0, 0.0);
      cylinder(cyl_s2_r, cyl_s2_h, cyl_s2_n);
      glTranslated(0.0, 0.0, cyl_s2_h);
      cylinder(cyl_s3_r, cyl_s3_h, cyl_s3_n);
      glTranslated(0.0, 0.0, cyl_s3_h*0.72);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
      half_sphere(sphere_r, sphere_m, sphere_n);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
    glRotated(60, 1.0, 0.0, 0.0);
    cylinder(small_r, small_h, n-2);
    glPushMatrix();
      glTranslated(0.0, 0.0, small_h);
      glRotated(90, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.0, -cyl_s1_h/2);
      cylinder(cyl_s1_r, cyl_s1_h, cyl_s1_n);
      glTranslated(0.0, 0.0, cyl_s1_h/2);
      glRotated(-90, 1.0, 0.0, 0.0);
      glRotated(90 - (5 * kut_offset), 0.0, 1.0, 0.0);
      cylinder(cyl_s2_r, cyl_s2_h, cyl_s2_n);
      glTranslated(0.0, 0.0, cyl_s2_h);
      cylinder(cyl_s3_r, cyl_s3_h, cyl_s3_n);
      glTranslated(0.0, 0.0, cyl_s3_h*0.72);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
      half_sphere(sphere_r, sphere_m, sphere_n);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
    glRotated(60, 1.0, 0.0, 0.0); 
    cylinder(small_r, small_h, n-2);
    glPushMatrix();
       glTranslated(0.0, 0.0, small_h);
      glRotated(90, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.0, -cyl_s1_h/2);
      cylinder(cyl_s1_r, cyl_s1_h, cyl_s1_n);
      glTranslated(0.0, 0.0, cyl_s1_h/2);
      glRotated(-90, 1.0, 0.0, 0.0);
      glRotated(90 - (5 * kut_offset), 0.0, 1.0, 0.0);
      cylinder(cyl_s2_r, cyl_s2_h, cyl_s2_n);
      glTranslated(0.0, 0.0, cyl_s2_h);
      cylinder(cyl_s3_r, cyl_s3_h, cyl_s3_n);
      glTranslated(0.0, 0.0, cyl_s3_h*0.72);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
      half_sphere(sphere_r, sphere_m, sphere_n);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
    glRotated(60, 1.0, 0.0, 0.0);
    cylinder(small_r, small_h, n-2);
    glPushMatrix();
       glTranslated(0.0, 0.0, small_h);
      glRotated(90, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.0, -cyl_s1_h/2);
      cylinder(cyl_s1_r, cyl_s1_h, cyl_s1_n);
      glTranslated(0.0, 0.0, cyl_s1_h/2);
      glRotated(-90, 1.0, 0.0, 0.0);
      glRotated(90 - (5 * kut_offset), 0.0, 1.0, 0.0);
      cylinder(cyl_s2_r, cyl_s2_h, cyl_s2_n);
      glTranslated(0.0, 0.0, cyl_s2_h);
      cylinder(cyl_s3_r, cyl_s3_h, cyl_s3_n);
      glTranslated(0.0, 0.0, cyl_s3_h*0.72);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
      half_sphere(sphere_r, sphere_m, sphere_n);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
    glRotated(60, 1.0, 0.0, 0.0);
    cylinder(small_r, small_h, n-2);
    glPushMatrix();
       glTranslated(0.0, 0.0, small_h);
      glRotated(90, 1.0, 0.0, 0.0);
      glTranslated(0.0, 0.0, -cyl_s1_h/2);
      cylinder(cyl_s1_r, cyl_s1_h, cyl_s1_n);
      glTranslated(0.0, 0.0, cyl_s1_h/2);
      glRotated(-90, 1.0, 0.0, 0.0);
      glRotated(90 - (5 * kut_offset), 0.0, 1.0, 0.0);
      cylinder(cyl_s2_r, cyl_s2_h, cyl_s2_n);
      glTranslated(0.0, 0.0, cyl_s2_h);
      cylinder(cyl_s3_r, cyl_s3_h, cyl_s3_n);
      glTranslated(0.0, 0.0, cyl_s3_h*0.72);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
      half_sphere(sphere_r, sphere_m, sphere_n);
    glPopMatrix();

  //glPopMatrix();


  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  double xmin = -10.0, xmax = 10.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(xmin, xmax, -yrange / 2.0, yrange / 2.0, 20.0, 100.0);
} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 'a') {if ((kut_offset--) <= 0) kut_offset = 0;}
  if(c == 'A') {if ((kut_offset++) >= 6) kut_offset = 6;}
} // tipka

//void rotiraj(void) {
//   kut += 0.5;
//   glutPostRedisplay();
//} // rotiraj

void rotirajT(int id)
{
  kut += kut_offset;
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
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  //glutIdleFunc(rotiraj);
  glutTimerFunc(50, rotirajT, 0); // prvi poziv rutine rotirajT

  glutMainLoop();
  return 0;
} // main

