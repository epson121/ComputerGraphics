#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1415926

void prsten(double r, double r2, double h, int n) {
  double t;
  int i;

  // baza stošca
  glBegin(GL_QUAD_STRIP);
    t = 2.0 * PI;
    for(i = 0; i <= n; i++) {
      glNormal3d(-cos(t), -sin(t), -1); // normale u xy ravnini - od središta
      glVertex3d(r * cos(t), r * sin(t), h);
      glVertex3d(r2 * cos(t), r2 * sin(t), h);
      t -= 2.0 * PI / n;
    }
  glEnd();

  // plašt valjka
  glBegin(GL_QUAD_STRIP);
    t = 2.0 * PI;
    for(i = 0; i <= n; i++) {
      glNormal3d(cos(t), -sin(t), -1); // normale u xy ravnini - od središta
      glVertex3d(r * cos(t), -r * sin(t), h);
      glNormal3d(cos(t), -sin(t), 0.0);
      glVertex3d(r * cos(t), -r * sin(t), 0.0);
      t -= 2.0 * PI / n;
    }
  glEnd();

  glBegin(GL_QUAD_STRIP);
    t = 2.0 * PI;
    for(i = 0; i <= n; i++) {
      glNormal3d(-cos(t), -sin(t), -1); // normale u xy ravnini - od središta
      glVertex3d(r2 * cos(t), r2 * sin(t), h);
      glNormal3d(-cos(t), -sin(t), 0.0);
      glVertex3d(r2 * cos(t), r2 * sin(t), 0.0);
      t -= 2.0 * PI / n;
    }
  glEnd();

  // baza stošca
  glBegin(GL_QUAD_STRIP);
    t = 2.0 * PI;
    for(i = 0; i <= n; i++) {
      glNormal3d(-cos(t), -sin(t), -1.0); // normale u xy ravnini - od središta
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glVertex3d(r2 * cos(t), r2 * sin(t), 0.0);
      t -= 2.0 * PI / n;
    }
  glEnd();
}

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
}

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

void cone(double r, double h, int n) {
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
  // outer loop (from bottom to top)cd 
     for (theta = 0; theta < PI / 2 ; theta += step1) {
        z1 = r * cos(theta);
        z2 = r * cos(theta + step1);
        if (i1 == 0) {
            i1 = 1;
          } else {
            i1 = 0;
          }
        // inner loop (creates the one "ring" (to rule them all))
        for (phi = 0; phi <= 2 * PI + step2; phi += step2) {
          if (i1 == 0) {
            glColor3d(1.0, 1.0, 0.0);
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

          glNormal3d(cos(phi) * sin(theta), sin(theta) * sin(phi), cos(theta));
          glVertex3d(x1, y1, z1);
          glNormal3d(cos(phi) * sin(theta+step1), sin(theta+step1) * sin(phi), cos(theta+step1));
          glVertex3d(x2, y2, z2);
        }
     }
  glEnd();
}

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
     for (theta = 0; theta < PI  ; theta += step1) {
        z1 = r * cos(theta);
        z2 = r * cos(theta + step1);
        if (i1 == 0) {
            i1 = 1;
          } else {
            i1 = 0;
          }
        // inner loop (creates the one "ring" (to rule them all))
        for (phi = 0; phi <= 2 * PI + step2; phi += step2) {
          if (i1 == 0) {
            glColor3d(1.0, 1.0, 0.0);
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

          glNormal3d(cos(phi) * sin(theta), sin(theta) * sin(phi), cos(theta));
          glVertex3d(x1, y1, z1);
          glNormal3d(cos(phi) * sin(theta+step1), sin(theta+step1) * sin(phi), cos(theta+step1));
          glVertex3d(x2, y2, z2);
        }
     }
  glEnd();
}

void elliptic_cylinder(double a, double b, double h, int n) {
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
      glVertex3d(a * cos(t), b * sin(t), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();

 // baza stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala je u smjeru z za sve trokute
    glVertex3d(0.0, 0.0, h); // središte baze je u ishodištu
    t = 0.0;
    for(i = 0; i <= n; i++) {
      glVertex3d(a * cos(t), b * sin(t), h);
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
      glVertex3d(a * cos(t), -b * sin(t), 0);
      glNormal3d(cos(t), -sin(t), 0);
      glVertex3d(a * cos(t), -b * sin(t), h);
    }
  glEnd(); 
}
