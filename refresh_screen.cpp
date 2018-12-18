#include <GL/glut.h>

void refresh_screen(void){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(.0f,.0f,.0f);
	glutSwapBuffers();
	
}
