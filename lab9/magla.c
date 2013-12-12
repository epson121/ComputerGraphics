// magla.c / Ivan Hip / 2011-11-28

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// koliko se tekstura koristi u programu
#define NTEX 2

GLuint tekstura[NTEX];

// poccetna pozicija
double px = 0.0, py = 0.0, pz = 2.5;

typedef struct {
  int dimX, dimY;
  GLubyte* pixmap;
} slika;

slika slika0, slika1;

void greska(char* tekst) {
  printf("\nGRESKA: %s\n\n", tekst);
  exit(0);
} // greska

void ucitajPPM(slika* sl, char* datoteka) {
  FILE *fin;
  char line[256];
  int slikaX, slikaY, imax, ix, iy, i, ib;
  GLubyte *pixmap;

  if(!(fin = fopen(datoteka, "r"))) greska("ne mogu otvoriti datoteku!");
  fgets(line, 256, fin); if(strcmp(line, "P3\n")) greska("nije PPM format!");
  fgets(line, 256, fin); if(line[0] != '#') greska("ocekujemo komentar!");
  fscanf(fin, "%d%d", &slikaX, &slikaY);
  printf("dimX = %d   dimY = %d\n", slikaX, slikaY);
  fscanf(fin, "%d", &imax); if(imax != 255) greska("ocekujemo imax = 255!");

  pixmap = (GLubyte *)malloc(slikaY * slikaX * 3 * sizeof(GLubyte));

  for(iy = 0; iy < slikaY; iy++)  
    for(ix = 0; ix < slikaX; ix++)
      for(i = 0; i < 3; i++) {
        fscanf(fin, "%d", &ib);
        pixmap[((slikaY - 1 - iy) * slikaX + ix) * 3 + i] = (GLubyte)ib;
      } 
  fclose(fin);

  sl->dimX = slikaX; sl->dimY = slikaY;
  sl->pixmap = pixmap;
} // ucitajPPM

void pripremiTex0() {
   glBindTexture(GL_TEXTURE_2D, tekstura[0]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slika0.dimX, slika0.dimY, 
                0, GL_RGB, GL_UNSIGNED_BYTE, slika0.pixmap);
} // pripremiTex0

void pripremiTex1() {
   glBindTexture(GL_TEXTURE_2D, tekstura[1]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slika1.dimX, slika1.dimY, 
                0, GL_RGB, GL_UNSIGNED_BYTE, slika1.pixmap);
} // pripremiTex1

void hodnik() {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  // pod
  glBindTexture(GL_TEXTURE_2D, tekstura[1]);
  glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); glVertex3d(-2.5,  0.0, 0.0);
    glTexCoord2d(0.0, 4.0); glVertex3d( 2.5,  0.0, 0.0);
    glTexCoord2d(4.0, 4.0); glVertex3d( 2.5, 60.0, 0.0);
    glTexCoord2d(4.0, 0.0); glVertex3d(-2.5, 60.0, 0.0);
  glEnd();

  // zidovi
  glBindTexture(GL_TEXTURE_2D, tekstura[1]);
  glBegin(GL_QUADS);
    // lijevi zid
    glTexCoord2d(0.0, 0.0); glVertex3d(-2.5,  0.0, 0.0);
    glTexCoord2d(4.0, 0.0); glVertex3d(-2.5, 60.0, 0.0);
    glTexCoord2d(4.0, 4.0); glVertex3d(-2.5, 60.0, 5.0);
    glTexCoord2d(0.0, 4.0); glVertex3d(-2.5,  0.0, 5.0);
    // desni zid
    glTexCoord2d(0.0, 0.0); glVertex3d( 2.5,  0.0, 0.0);
    glTexCoord2d(4.0, 0.0); glVertex3d( 2.5, 60.0, 0.0);
    glTexCoord2d(4.0, 4.0); glVertex3d( 2.5, 60.0, 5.0);
    glTexCoord2d(0.0, 4.0); glVertex3d( 2.5,  0.0, 5.0);
  glEnd();

  // kraj hodnika
  glBindTexture(GL_TEXTURE_2D, tekstura[0]);
  glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); glVertex3d(-2.5, 60.0, 0.0);
    glTexCoord2d(1.0, 0.0); glVertex3d( 2.5, 60.0, 0.0);
    glTexCoord2d(1.0, 1.0); glVertex3d( 2.5, 60.0, 5.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(-2.5, 60.0, 5.0);
  glEnd();

  glDisable(GL_TEXTURE_2D);  
} // hodnik

void pripremiMaglu() {
  GLfloat sivaMagla[4] = {0.5, 0.5, 0.5, 1.0};

  glEnable(GL_FOG);
  // LINEAR: prigushenje = (end - z) / (end - start)
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, sivaMagla);
  glFogf(GL_FOG_START, 0.0);
  glFogf (GL_FOG_END, 30.0);
  glClearColor(0.5, 0.5, 0.5, 1.0);  // boja magle
} // pripremiMaglu

void iscrtaj(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(px, py, pz, 0.0, 100.0, 2.5, 0.0, 0.0, 1.0);
 
  hodnik(); // crtamo hodnik

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
} // skaliraj

void strelice(int c, int x, int y) {
  if(c == GLUT_KEY_END) exit(0);
  if(c == GLUT_KEY_LEFT) { if(px > -2.0) px -= 0.1; glutPostRedisplay(); }
  if(c == GLUT_KEY_RIGHT) { if(px < 2.0) px += 0.1; glutPostRedisplay(); }
  if(c == GLUT_KEY_UP) { if(py < 55.0) py += 0.2; glutPostRedisplay(); }
  if(c == GLUT_KEY_DOWN) { if(py > 0.0) py -= 0.2; glutPostRedisplay(); }
} // strelice

int main(int argc, char** argv) {
   ucitajPPM(&slika0, "slike/bricks.ppm");
   ucitajPPM(&slika1, "slike/bricks.ppm");

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(0, 0);
   glutCreateWindow(argv[0]);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glEnable(GL_DEPTH_TEST);

   glGenTextures(NTEX, tekstura);
   pripremiTex0();
   pripremiTex1();
   pripremiMaglu();

   glutDisplayFunc(iscrtaj);
   glutReshapeFunc(skaliraj);
   glutSpecialFunc(strelice);
   glutMainLoop();
   return 0; 
} // main

