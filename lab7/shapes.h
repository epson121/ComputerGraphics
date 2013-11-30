#define PI 3.1415926
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/**
* r - radius of the base
* h - height of the cylinder
* n - number of sides for the base and body
*/
void cylinder(double r, double h, int n) {

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
        glColor3d(1.0, 0.0, 0.0);
        i1 = 1;
      } else {
        glColor3d(1.0, 0.2, 1.0);
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
        glColor3d(1.0, 0.0, 0.0);
        i1 = 1;
      } else {
        glColor3d(1.0, 0.2, 1.0);
        i1 = 0;
      }
      glVertex3d(0, 0, 0);
      glVertex3d(r * cos(t), -r * sin(t), 0);
      glVertex3d(r * cos(t+step), -r * sin(t+step), 0);
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
      glVertex3d(r * cos(t), -r * sin(t), 0);
      glVertex3d(r * cos(t), -r * sin(t), h);
    }
  glEnd();
  
}

/**
* r - radius of the base
* h - height of the cone
* n - number of sides for the base and body
*/
void cone(double r, double h, int n) {

  double t;
  double step = (2.0 * PI)/n;
  double phi;
  double x, y;
  
  int i1 = 0;
  int i2 = 0;
  
  // base
  glBegin(GL_TRIANGLES);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i1 == 0) {
        glColor3d(1.0, 0.0, 0.0);
        i1 = 1;
      } else {
        glColor3d(1.0, 0.2, 1.0);
        i1 = 0;
      }
      glVertex3d(0, 0, 0);
      glVertex3d(r * cos(t), -r * sin(t), 0);
      glVertex3d(r * cos(t+step), -r * sin(t+step), 0);
    }
  glEnd();
  
  // body
  glBegin(GL_TRIANGLES);
    for(t = 0.0; t < 2.0 * PI + step; t += step) {
      if (i2 == 0) {
        glColor3d(1.0, 1.0, 0.0);
        i2 = 1;
      } else {
        glColor3d(1.0, 1.0, 1.0);
        i2 = 0;
      }
      glVertex3d(0, 0, h);
      glVertex3d(r * cos(t), r * sin(t), 0);
      glVertex3d(r * cos(t+step), r * sin(t+step), 0);
    }
  glEnd();
  
}

/**
* r - radius
* m - number of meridians
* n - number of parallels
*/
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
        z2 = r * cos(theta + step1);
         if (i1 == 0) {
            i1 = 1;
          } else {
            i1 = 0;
          }
        // inner loop (creates the one "ring" (to rule them all))
        for (phi = 0; phi <= 2 * PI; phi += step2) {
          if (i1 == 0) {
            glColor3d(1.0, 0.0, 0.0);
            i1 = 1;
          } else {
            glColor3d(1.0, 0.2, 1.0);
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

/**
* r - radius
* m - number of meridians
* n - number of parallels
*/
void half_sphere(double r, int m, int n) {
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
     for (theta = 0; theta < PI / 2; theta += step1) {
        z1 = r * cos(theta);
        z2 = r * cos(theta + step1);
        if (i1 == 0) {
            i1 = 1;
          } else {
            i1 = 0;
          }
        // inner loop (creates the one "ring" (to rule them all))
        for (phi = 0; phi <= 2 * PI; phi += step2) {
          if (i1 == 0) {
            glColor3d(1.0, 0.0, 0.0);
            i1 = 1;
          } else {
            glColor3d(1.0, 0.2, 1.0);
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
