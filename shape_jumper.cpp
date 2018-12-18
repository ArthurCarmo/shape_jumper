#include <GL/glut.h>
#include "sjfwd.h"

int main(){

	glutInit(&argc, argv);

	// Dois buffers, janela 600x450
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600,450);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Shape Jumper");
	
	// Funções de desenho e entrada do teclado 
	glutDisplayFunc(refresh_screen);
	glutKeyboardFunc(keyboard_input);
	glutMainLoop();

	return 0;
	
}
