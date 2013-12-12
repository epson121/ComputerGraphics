// Hip, 2009-11-22

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int dimX, dimY;
  GLubyte* pixmap;
} slika;

slika slika1;

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

void iscrtaj(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 0);

   glDrawPixels(slika1.dimX, slika1.dimY, GL_RGB,
     GL_UNSIGNED_BYTE, slika1.pixmap);

   glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
} // skaliraj

int main(int argc, char** argv) {
   char imeslike[64];

   printf("Ime datoteke sa slikom: ");
   scanf("%s", imeslike);
   ucitajPPM(&slika1, imeslike);

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(0, 0);
   glutCreateWindow(argv[0]);

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glutDisplayFunc(iscrtaj);
   glutReshapeFunc(skaliraj);
   glutMainLoop();
   return 0; 
} // main

