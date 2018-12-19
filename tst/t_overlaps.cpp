#include <GL/glut.h>

#include "../rectangle.h"
#include "../circle.h"
#include "../triangle.h"


GLfloat win;
GLsizei view_w, view_h;

//triangle main_rec(point(0, 10), point(20, 30), point(40, 10));
//rectangle main_rec(10, 10, 15, 20);
//circle main_rec(10, 10, 20);

shape *main_rec = new rectangle(10, 10, 15, 20);

rectangle  prop1(80, 70, 50, 50), prop2(-70, -70, 20, 15);	  
circle prop3(60, -70, 15);
triangle prop4(point(-100, 35), point(-50, 100), point(-50, 35));

bool key_arr[255] = { 0 };

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;            

	// Inicializa o sistema de coordenadas
	glutReshapeWindow(w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-win, win, -win, win);
}

void key_release(unsigned char c, int a, int b){
	if(c == 'w') key_arr['w'] = false;
	if(c == 's') key_arr['s'] = false;
	if(c == 'a') key_arr['a'] = false;
	if(c == 'd') key_arr['d'] = false;
}

void key_press(unsigned char c, int a, int b){
	if(c == 27) exit(0);
	if(c == 'w') key_arr['w'] = true;
	if(c == 's') key_arr['s'] = true;
	if(c == 'a') key_arr['a'] = true;
	if(c == 'd') key_arr['d'] = true;
	if(c == 't') {
		shape *aux = main_rec;
		main_rec = new triangle(point(0, 10), point(20, 30), point(40, 10));
		delete aux;
	}
	if(c == 'r') {
		shape *aux = main_rec;
		main_rec = new rectangle(10, 10, 15, 20);
		delete aux;
	}
	if(c == 'c') {
		shape *aux = main_rec;
		main_rec = new circle(10, 10, 20);
		delete aux;
	}
}

void handle_movement() {
	if(key_arr['w']) main_rec->translade(0.0, 2);
	if(key_arr['s']) main_rec->translade(0.0, -2);
	if(key_arr['a']) main_rec->translade(-2, 0.0);
	if(key_arr['d']) main_rec->translade(2, 0.0);
	
	main_rec->fill = main_rec->overlaps(prop1) || main_rec->overlaps(prop2) || main_rec->overlaps(prop3) || main_rec->overlaps(prop4);
}

void Desenha(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
                   
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(.0f,.0f,.0f);
     
	main_rec->draw();
	prop1.draw();
	prop2.draw();
	prop3.draw();
     	prop4.draw();
     
	handle_movement();
     
	glutSwapBuffers(); 
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
	glutInitWindowSize(400,400);
	glutInitWindowPosition(10,10);
	glutCreateWindow("T_RECTANGLES");
	glutReshapeFunc(AlteraTamanhoJanela);
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(key_press);
	glutKeyboardUpFunc(key_release);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	win=150.0f;
	glutMainLoop();
	delete main_rec;
	return 0;
}
