// GLelipse.c

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define XMIN -10.0
#define XMAX 10.0
#define YMIN -10.0
#define YMAX 10.0

void elipsa(double a, double b) {
  double t;

  glBegin(GL_LINE_LOOP);
    glVertex2d(a, 0);
    for(t = 0.0; t < 2.0 * M_PI; t += M_PI / 100.0) 
      glVertex2d(a * cos(t), b * sin(t));
  glEnd();
} // elipsa

// y = -2x + 4;
void pravac() {
  double t;
  double y1 = -2 * XMIN + 4;
  double y2 = -2 * XMAX + 4;
  glBegin(GL_LINES);
    glVertex2d(XMIN, y1);
    glVertex2d(XMAX, y2);
  glEnd();
}
/*
public void rotiraj(double x1, double y1, double z1, 
            double x2, double y2, double z2, 
            double kut) {
    calcCoefficients(x1, y1, z1, x2, y2, z2);
    MT3D m1 = new MT3D();
      m1.pomakni(-x1, -y1, -z1);
      this.rotirajX(Math.toDegrees(Math.asin(this.b / this.d)));
      this.mult(m1);
      m1.rotirajY(Math.toDegrees(Math.asin(this.a)) * (-1));
      m1.mult(this);
      this.rotirajZ(kut);
      this.mult(m1);
      m1.rotirajY(Math.toDegrees(Math.asin(this.a)));
      m1.mult(this);
      this.rotirajX(Math.toDegrees(Math.asin((this.b / this.d))) * (-1));
      this.mult(m1);
      m1.pomakni(x1, y1, z1);
      m1.mult(this);
      this.m = m1.getM();
  }
  
  private void calcCoefficients(double x1, double y1, double z1, 
             double x2, double y2, double z2) {
    double tempX = Math.pow(x2 - x1, 2);
    double tempY = Math.pow(y2 - y1, 2);
    double tempZ = Math.pow(z2 - z1, 2);
    double denominator = Math.sqrt(tempX + tempY + tempZ);
    this.a = (x2 - x1) / denominator;
    this.b = (y2 - y1) / denominator;
    this.c = (z2 - z1) / denominator;
    this.d = Math.sqrt(Math.pow(this.b, 2) + Math.pow(this.c, 2));
  }
  */
// ova je rutina ekvivalent rutini paint u Javi:
void iscrtaj(void) {
  // punjenje zaslona bojom pozadine koja se postavlja s glClearColor()
  glClear(GL_COLOR_BUFFER_BIT);

  // operacije se odnose na matricu transformacija i pogleda (MODELVIEW)
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // koordinatne osi
  glColor3d(0.0, 0.0, 0.0); // crna
  glBegin(GL_LINES);
    glVertex2d(XMIN, 0.0);
    glVertex2d(XMAX, 0.0);
    glVertex2d(0.0, YMIN);
    glVertex2d(0.0, YMAX);
  glEnd();

  glColor3d(1.0, 0.0, 0.0);
  pravac();

  elipsa(3.0, 1.0);

  double alfa = atan(-2) * 180 / 3.1415926;
  glTranslated(0.0, 4.0, 0.0);
  glRotated(alfa, 0.0, 0.0, 1.0);
  glScaled(1.0, -1.0, 1.0);
  glRotated(-alfa, 0.0, 0.0, 1.0);
  glTranslated(0.0, -4.0, 0.0);
  elipsa(3.0, 1.0);  
  
  glFlush();
} // iscrtaj

void skaliraj(int w, int h) {
// sistem daje vrijednosti w i h koje predstavljaju širinu i visinu prozora
// rutina se automatski poziva prilikom inicijalizacije, ali i kada dođe do
// promjene veličine prozora u koji se iscrtava, 

  double xmin = XMIN, xmax = XMAX;
  double xrange, yrange;

  // iscrtavanje u čitav prozor
  glViewport(0, 0, w, h);

  // operacije se odnose na matricu projekcije (PROJECTION)
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // gluOrtho2D ekvivalentno je rutini GKS koju ste implementirali u Javi!
  gluOrtho2D(XMIN, XMAX, YMIN, YMAX);

  // varijanta koja čuva proporcije, tj. omjer visine i širine objekata
  // xrange = xmax - xmin;
  // yrange = h * xrange / w;
  // gluOrtho2D(xmin, xmax, -yrange / 2.0, yrange / 2.0);

} // skaliraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
} // tipka

int main(int argc, char** argv) {
  glutInit(&argc, argv); // -geometry 600x600+60+30
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(60, 30);
  glutInitWindowSize(600, 600);
  glutCreateWindow("GLelipse");

  glClearColor(1.0, 1.0, 0.0, 0.0);

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutMainLoop();
  return 0;
} // main