// starigrad.c / Ivan Hip / 2012-12-03

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// svakih koliko milisekundi pozvati iscrtavanje
#define MILS 50

int TIMER = 0; // FALSE
double korakR = 0.1; // korak rotacije

// koliko se tekstura koristi u programu
#define NTEX 2

GLuint tekstura[NTEX];
double kut = 0.0;

// dimenzija kocke
double a = 2.5;

typedef struct {
  int dimX, dimY;
  GLubyte* pixmap;
} slika;

slika slika0, slika1, slika2 = {256, 256, NULL};

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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slika0.dimX, slika0.dimY, 
    0, GL_RGB, GL_UNSIGNED_BYTE, slika0.pixmap);
} // pripremiTex0

void pripremiTex1() {
  // reskaliraj slika1 (350x350) u slika2 (256x256)
  slika2.pixmap = (GLubyte *)malloc(slika2.dimY *
    slika2.dimX * 3 * sizeof(GLubyte));
  gluScaleImage(GL_RGB,
    slika1.dimX, slika1.dimY, GL_UNSIGNED_BYTE, slika1.pixmap,
    slika2.dimX, slika2.dimY, GL_UNSIGNED_BYTE, slika2.pixmap);

  glBindTexture(GL_TEXTURE_2D, tekstura[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slika2.dimX, slika2.dimY, 
    0, GL_RGB, GL_UNSIGNED_BYTE, slika2.pixmap);
} // pripremiTex1

void kvadar(double ax, double ay, double az) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glBindTexture(GL_TEXTURE_2D, tekstura[0]);
  glBegin(GL_QUAD_STRIP);
    glTexCoord2d(0.0, 1.0); glVertex3d(0.0, 0.0, az);
    glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
    glTexCoord2d(0.5, 1.0); glVertex3d(ax, 0.0, az);
    glTexCoord2d(0.5, 0.0); glVertex3d(ax, 0.0, 0.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(ax, ay, az);
    glTexCoord2d(1.0, 0.0); glVertex3d(ax, ay, 0.0);
    glTexCoord2d(1.5, 1.0); glVertex3d(0.0, ay, az);
    glTexCoord2d(1.5, 0.0); glVertex3d(0.0, ay, 0.0);
    glTexCoord2d(2.0, 1.0); glVertex3d(0.0, 0.0, az);
    glTexCoord2d(2.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, tekstura[1]);
  glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(0.0, ay, 0.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(ax, ay, 0.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(ax, 0.0, 0.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, az);
    glTexCoord2d(1.0, 0.0); glVertex3d(ax, 0.0, az);
    glTexCoord2d(1.0, 1.0); glVertex3d(ax, ay, az);
    glTexCoord2d(0.0, 1.0);  glVertex3d(0.0, ay, az);
  glEnd();

  glDisable(GL_TEXTURE_2D);
} // kvadar

void ispisFPS() {
  static int t0 = 0, frames = 0, frames0 = 0;
  int t, i;
  static char strFPS[10]; 

  frames++;
  t = glutGet(GLUT_ELAPSED_TIME);
  if((t - t0) > 1000) {
    sprintf(strFPS, "FPS %5.0lf", 1000.0 *
      (double)(frames - frames0) / (double)(t - t0));
    frames0 = frames; t0 = t;
  }
  glColor3d(1.0, 1.0, 1.0); 
  glWindowPos2i(20, 20);
  for(i = 0; i < 9; i++) 
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strFPS[i]);
} // ispisFPS

void iscrtaj(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 
  glRotated(-kut, 1.0, 0.0, 0.0);
  glRotated(2.0 * kut, 0.0, 0.0, 1.0); 
  glTranslated(-a / 2.0, -a / 2.0, -a);
  kvadar(a, a, 2 * a);

  ispisFPS();
  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
} // skaliraj

void rotiraj() {
  kut += korakR;
  glutPostRedisplay();
} // rotiraj

void rotirajT(int n) {
  kut += korakR;
  glutPostRedisplay();
  if(TIMER) glutTimerFunc(MILS, rotirajT, 0);
} // rotiraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 'a') if(a > 0.5) a -= 0.5; else a = 0.5;
  if(c == 'A') if(a < 5.0) a += 0.5; else a = 5.0;
  if(c == 'z' && korakR > 0.0) korakR = 0.0;
    else if(c == 'z' && korakR == 0.0) korakR = 0.1;
  if(c == 't') {
    glutIdleFunc(NULL);
    TIMER = 1; // TRUE
    glutTimerFunc(MILS, rotirajT, 0);
  }
  if(c == 'i') {
    TIMER = 0; // FALSE
    glutIdleFunc(rotiraj);
  }
} // tipka

int main(int argc, char** argv) {
  int maxtex;

  ucitajPPM(&slika0, "slike/starigrad512.ppm");
  ucitajPPM(&slika1, "slike/starigrad350.ppm");

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(argv[0]);

  printf("\nVerzija OpenGL-a: %s\n", glGetString(GL_VERSION));
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxtex);
  printf("Maksimalna velicina teksture: %d\n", maxtex);

  glClearColor (0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);

  // alokacija teksturnih objekata - openGL vraća broj svake alocirane teksture
  printf("\nprije: tekstura[0] = %d\n", tekstura[0]);
  printf("prije: tekstura[1] = %d\n", tekstura[1]);
  glGenTextures(NTEX, tekstura);
  printf("poziv: glGenTextures()\n"); 
  printf("poslije: tekstura[0] = %d\n", tekstura[0]);
  printf("poslije: tekstura[1] = %d\n", tekstura[1]);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  pripremiTex0();
  pripremiTex1();

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  glutIdleFunc(rotiraj);
  glutMainLoop();
  return 0; 
} // main

