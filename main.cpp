#include<iostream>
#include<algorithm>
#include<vector>
#include"game.hpp"
#include"disp.hpp"
#include"GL/glut.h"

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutCreateWindow("OtelloGL");
	inits();
	glutDisplayFunc(display);
 	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
