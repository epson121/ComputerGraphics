// uranjanje.c / Ivan Hip / 2011-11-28

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double alpha = 0.8; // parametar prozirnosti
double udaljenost = 6.0, visina = 2.0; // položaj kamere
double pz = 0.86; // pozicija kugle - z-koordinata
double korakZ = 0.02; // korak promjene z-koordinate

float bijelo[] = {1.0, 1.0, 1.0, 1.0};
float zuto[] = {0.75, 0.75, 0.0, 1.0};
float crno[] = {0.0, 0.0, 0.0, 1.0};
float voda[] = {0.0, 0.8, 0.8, 0.5};

void kugla(double R, int nphi, int ntheta) {
  double t, r, z;
  double theta, step_theta = M_PI / ntheta;
  double r1, r2, z1, z2;
  int i;

  // bliža kapica
  theta = M_PI / 2.0 - step_theta;
  r = R * cos(theta);
  z = R * sin(theta);
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, R);
    t = 0.0;
    for(i = 0; i <= nphi; i++) {
      glNormal3d(r * cos(t) / R, r * sin(t) / R, z / R);      
      glVertex3d(r * cos(t), r * sin(t), z);
      t += 2.0 * M_PI / nphi;
    }
  glEnd();

  // plašt
  for(theta = M_PI / 2.0 - 2.0 * step_theta; theta > -M_PI / 2.0;
      theta -= step_theta) {
    r1 = R * cos(theta); r2 = R * cos(theta + step_theta);
    z1 = R * sin(theta); z2 = R * sin(theta + step_theta);  
 
    glBegin(GL_QUAD_STRIP);
      t = 0.0; 
      for(i = 0; i <= nphi; i++) {
        glNormal3d(r2 * cos(t) / R, r2 * sin(t) / R, z2 / R);
        glVertex3d(r2 * cos(t), r2 * sin(t), z2);
        glNormal3d(r1 * cos(t) / R, r1 * sin(t) / R, z1 / R);
        glVertex3d(r1 * cos(t), r1 * sin(t), z1);
        t += 2.0 * M_PI / nphi;
      }
    glEnd();
  }

  // dalja kapica
  theta = -M_PI / 2.0 + step_theta;
  r = R * cos(theta);
  z = R * sin(theta);
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(0.0, 0.0, -R);
    t = 0.0;
    for(i = 0; i <= nphi; i++) {
      glNormal3d(r * cos(t) / R, r * sin(t) / R, z / R);
      glVertex3d(r * cos(t), r * sin(t), z);
      t -= 2.0 * M_PI / nphi;
    }
  glEnd();
} // kugla

void povrsina(double a) {
  glBegin(GL_QUADS); // kvadrat u xy-ravnini stranice 2*a
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(-a, -a, 0.0);
    glVertex3d(a, -a, 0.0);
    glVertex3d(a, a, 0.0);
    glVertex3d(-a, a, 0.0);
  glEnd();
} // povrsina
 
void svjetlo0(void) {
  GLfloat pozicija[] = {0.0, 0.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, bijelo);
  glLightfv(GL_LIGHT0, GL_SPECULAR, bijelo);
  glLightfv(GL_LIGHT0, GL_POSITION, pozicija);
} // svjetlo0

void iscrtaj(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, -udaljenost, visina, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  glPushMatrix(); // postavljanje izvora svjetlosti
    glTranslated(2.0, -4.0, 2.0);
    svjetlo0();
  glPopMatrix();

  glPushMatrix(); // iscrtavanje kugle
    glTranslatef (0.0, 0.0, pz);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bijelo);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    kugla(0.70, 32, 32);
  glPopMatrix ();

  // iscrtavanje vode
  voda[3] = alpha;
  glMaterialfv(GL_FRONT, GL_DIFFUSE, voda);
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  povrsina(4.0);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (GLfloat) w/(GLfloat) h, 1.0, 50.0);
} // skaliraj

void strelice(int c, int x, int y) {
  if(c == GLUT_KEY_END) exit(0);
  if(c == GLUT_KEY_UP) pz += korakZ;
  if(c == GLUT_KEY_DOWN) pz -= korakZ;
  if(c == GLUT_KEY_PAGE_UP) 
    if(alpha < 1.0) alpha += 0.02; else alpha = 1.0;
  if(c == GLUT_KEY_PAGE_DOWN) 
    if(alpha > 0.0) alpha -= 0.02; else alpha = 0.0;
  glutPostRedisplay();
} // strelice

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(0, 0);
   glutCreateWindow(argv[0]);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glutReshapeFunc(skaliraj);
   glutSpecialFunc(strelice);
   glutDisplayFunc(iscrtaj);
   glutMainLoop();
   return 0;
} // main

