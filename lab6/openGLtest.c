// GLtest.c

#include <GL/glut.h>

void iscrtaj(void) {
glClear(GL_COLOR_BUFFER_BIT);

glColor3d(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2d(-8.0, -4.0);
glVertex2d(-8.0, 4.0);
glVertex2d(8.0, -4.0);
glVertex2d(8.0, 4.0);
glEnd();

glFlush();
} // iscrtaj

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

glutInitWindowSize(400, 200);
glutCreateWindow("GLtest");

glClearColor(1.0, 1.0, 0.0, 0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-10.0, 10.0, -5.0, 5.0);

glutDisplayFunc(iscrtaj);
glutMainLoop();
return 0;
} // main
