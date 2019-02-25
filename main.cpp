#include<iostream>
#include"game.hpp"
#include"GL/glut.h"

const int BoardSize=8;

const int Black=0;
const int White=1;
const int Wall=2;

void inits();
void resize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void display();

void glutDispBoard();
void glutDispStone();

Game game;
Board board;

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutCreateWindow("OtelloGL");
	gluOrtho2D(0, 800, 800, 0);
	inits();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}


void inits(){
	static const int WindowSizeWight=800;
	static const int WindowSizeHeight=800;

	static const int WindowPositionWight=100;
	static const int WindowPositionHeight=100;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(WindowPositionWight, WindowPositionHeight);
	glutInitWindowSize(WindowSizeWight, WindowSizeHeight);
	glClearColor(0, 0.5, 0, 1);

	//---点を丸く打つための処理---
	//点にアンチエリアシング処理を行う 
	glEnable(GL_POINT_SMOOTH);
	//アンチエリアシング処理の品質を最高にする 
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//アルファブレンディングを有効にする 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
	case 'q':
	case 'Q':
	case '\033':
		std::exit(0);
	default:
		break;
	}	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutDispBoard();
	glFlush();
}

void glutDispBoard(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	//盤面のマス目作成
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(3);
	glBegin(GL_LINES);
    
	for(int i = 0; i <= BoardSize; i++){
		glVertex2i(80 + 80 * i, 720);
		glVertex2i(80 + 80 * i, 80);
        
		glVertex2i(80, 80 + 80 * i);
		glVertex2i(720, 80 + 80 * i);
	}
	glEnd();
    
	//盤面上の4点の描画
	glColor3d(0.0, 0.0, 0.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2i(240, 240);
	glVertex2i(240, 560);
	glVertex2i(560, 240);
	glVertex2i(560, 560);
	glEnd();
    
	glFlush();  //描画実行
}
void glutDispStone(){

}

