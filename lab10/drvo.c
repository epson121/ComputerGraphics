// polikocka.c // Ivan Hip // 2011-11-14

#define PI 3.1415926
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
double kut = 0.0;

void osi(double a) {
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(a, 0.0, 0.0); // x-os
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, a, 0.0); // y-os
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, a); // z-os
  glEnd();
} // osi

int dep = 3;
double rad = 1;
double height = 5;
double radCoeff = 0.7;
double heightCoeff = 0.8;
double shrinkCoeff = 0.9;

void sphere(double r, int m, int n) {
  double step1 = PI/(n+1);
  double step2 = PI/(m+1);
  double t, theta = 0, phi = 0;
  int i1 = 0, i2 = 0;

  double x1, y1, z1;
  double x2, y2, z2;
  double x3, y3;
  double x4, y4;

  // whole sphere
  glBegin(GL_QUAD_STRIP);
  // outer loop (from bottom to top)
     for (theta = 0; theta <= PI; theta += step1) {
        z1 = r * cos(theta);
        z2 = -r * cos(theta + step1);
         if (i1 == 0) {
            i1 = 1;
          } else {
            i1 = 0;
          }
        // inner loop (creates the one "ring" (to rule them all))
        for (phi = 0; phi <= 2 * PI; phi += step2) {
          if (i1 == 0) {
            glColor3d(0.0, 1.0, 0.0);
            i1 = 1;
          } else {
            glColor3d(0.0, 0.8, 0.0);
            i1 = 0;
          }
          // upper left
          x1 = r * cos(phi) * sin(theta);
          y1 = r * sin(theta) * sin(phi);
          // lower left
          x2 = r * cos(phi) * sin(theta+step1);
          y2 = r * sin(theta+step1) * sin(phi);
          // upper right
          x3 = r * cos(phi+step2) * sin(theta);
          y3 = r * sin(theta) * sin(phi+step2);
          //lower right
          x4 = r * cos(phi+step2) * sin(theta+step1);
          y4 = r * sin(theta+step1) * sin(phi+step2);
          glVertex3d(x1, y1, z1);
          glVertex3d(x2, y2, z2);
          glVertex3d(x3, y3, z1);
          glVertex3d(x4, y4, z2);
        }
     }
  glEnd();
}

void cylinder(int depth, double r, double h, int n) {
  if (depth == 0) {
    sphere(0.5, 20, 20);
    return;
  }
  double t;
  double step = (2.0 * PI)/n;
  double phi;
  double x, y;
  
  int i1 = 0;
  int i2 = 0;
  
  // base  one
  glBegin(GL_TRIANGLES);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i1 == 0) {
        glColor3d(0.7, 0.3, 0.3);
        i1 = 1;
      } else {
        glColor3d(0.7, 0.3, 0.2);
        i1 = 0;
      }
      glVertex3d(0, 0, h);
      glVertex3d(r * cos(t), r * sin(t), h);
      glVertex3d(r * cos(t+step), r * sin(t+step), h);
    }
  glEnd();

  // base two

  glBegin(GL_TRIANGLES);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i1 == 0) {
        glColor3d(0.7, 0.4, 0.3);
        i1 = 1;
      } else {
        glColor3d(0.7, 0.4, 0.2);
        i1 = 0;
      }
      glVertex3d(0, 0, 0);
      glVertex3d(r * shrinkCoeff * cos(t), -r * shrinkCoeff * sin(t), 0);
      glVertex3d(r * shrinkCoeff * cos(t+step), -r * shrinkCoeff * sin(t+step), 0);
    }
  glEnd();

  // body
  glBegin(GL_QUAD_STRIP);
     for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i1 == 0) {
        glColor3d(0.7, 0.4, 0.3);
        i1 = 1;
      } else {
        glColor3d(0.7, 0.4, 0.2);
        i1 = 0;
      }
      glVertex3d(r * cos(t), -r * sin(t), 0);
      glVertex3d(r * shrinkCoeff * cos(t), -r * shrinkCoeff * sin(t), h);
    }
  glEnd();
  glTranslated(0, 0, h);
  glRotated(45, 1.0, 0.0, 0.0);
  glPushMatrix();
    cylinder(depth-1, r * radCoeff, h * heightCoeff, n);
  glPopMatrix();
  glPushMatrix();
    glRotated(120, 0.0, 1.0, 0.0);
    cylinder(depth-1, r * radCoeff, h * heightCoeff, n);
  glPopMatrix();
  glPushMatrix();
    glRotated(240, 0.0, 1.0, 0.0);
    cylinder(depth-1, r * radCoeff, h * heightCoeff, n);
  glPopMatrix();
}


void iscrtaj(void) {
  double a = 8.0; // duljina stranice kocke
  double d = 0.5; // odmak od osi

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3d(1.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(25, 0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  double sphere_radius = 1;
  double cone_height = 8;
  double top_cylinder_radius = 1;
  double cylinder_hand_length = 5;
  // base cone
  glRotated(kut, 0.0, 0.0, 1.0);
  cylinder(dep, rad, height, 20);


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
  if(c == 'n') ++dep; 
  if(c == 'N') --dep;
  if(c == 'r') rad -= 0.1;
  if(c == 'R') rad += 0.1;
  if(c == 'h') height -= 0.1;
  if(c == 'H') height += 0.1;
  if(c == 'a') radCoeff -= 0.1;
  if(c == 'A') radCoeff += 0.1;
  if(c == 'c') heightCoeff -= 0.1;
  if(c == 'C') heightCoeff += 0.1;
  if(c == 's') shrinkCoeff -= 0.05;
  if(c == 'S') shrinkCoeff += 0.05;
  glutPostRedisplay();
} // tipka

void rotiraj(void) {
   kut += 0.5;
   glutPostRedisplay();
} // rotiraj

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(800, 600);
  glutCreateWindow("anemometer");

  glShadeModel(GL_FLAT);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);

  glutMainLoop();
  return 0;
} // main
