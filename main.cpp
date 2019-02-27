#include<iostream>
#include<algorithm>
#include<vector>
#include"game.hpp"
#include"GL/glut.h"

const int celSize=50;

void inits();
void resize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();

void glutDispBoard();
void glutDispStone();

void glutDispScoreAndTurn();

void ConsoleDisp();
void renderString(const float x, const float y, const char* string);

GLdouble black[]={0.0, 0.0, 0.0};
GLdouble white[]={1.0, 1.0, 1.0};
GLdouble green[]={0.0, 0.5, 0.0};

Game game;

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

void inits(){
	static const int WindowSizeWight=800;
	static const int WindowSizeHeight=800;

	static const int WindowPositionWight=100;
	static const int WindowPositionHeight=100;
	
	gluOrtho2D(0, 800, 800, 0); //座標系の設定
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(WindowPositionWight, WindowPositionHeight);
	glutInitWindowSize(WindowSizeWight, WindowSizeHeight);
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f); //盤の色を緑に設定

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

void mouse(int button, int state, int x, int y){
	const bool input=(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN);
	const bool isOut=(x<celSize||x>celSize*9||y<celSize||y>celSize*9);
	if(!input||isOut)  return;
	//入力された座標を処理する形式へ変換
	const int i=x/celSize;
	const int j=y/celSize;
	Coord coord(i,j);
	std::cout<<"("<<x<<","<<y<<") > "<<"("<<i<<","<<j<<")"<<std::endl;
	game.move(coord);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutDispBoard();
	glutDispStone();
	ConsoleDisp();
	glutDispScoreAndTurn();
	glFlush();
}

void glutDispBoard(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static const int lineSize=3;
	static const int pointSize=11;
	
	//盤面のマス目作成
	glColor3dv(black);
	glLineWidth(lineSize);
	glBegin(GL_LINES);
    
	for(int i = 0; i <= BoardSize; i++){
		glVertex2i(celSize + celSize * i, celSize * 9);
		glVertex2i(celSize + celSize * i, celSize);
        
		glVertex2i(celSize, celSize + celSize * i);
		glVertex2i(celSize * 9, celSize + celSize * i);
	}
	glEnd();
    
	//盤面上の4点の描画
	glColor3dv(black);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex2i(celSize*3, celSize*3);
	glVertex2i(celSize*3, celSize*7);
	glVertex2i(celSize*7, celSize*3);
	glVertex2i(celSize*7, celSize*7);
	glEnd();
}

void glutDispStone(){
	Coord coord(0, 0);
	int stone;
	
	const int num=celSize/2;
	static const int pointSize=40;
	
	glPointSize(pointSize);
	for(int i=1;i<=BoardSize;i++){
		for(int j=1;j<=BoardSize;j++){
			coord.set(i, j);
			stone=game.board.get(coord);
			if(stone==Empty||stone==Wall)
				continue;
			glColor3dv(stone+1?white:black);
			glBegin(GL_POINTS);
			glVertex2i(num+celSize*i, num+celSize*j);
			glEnd();
		}
	}
}

void glutDispScoreAndTurn(){
	
	std::cout<<"order:"<<(game.order.get()+1?"white":"black")<<std::endl;
  std::cout<<"turn :"<<game.turn.get()+1<<std::endl;
	std::cout<<"black:"<<game.getScore(Black)<<std::endl;
	std::cout<<"white:"<<game.getScore(White)<<std::endl;	
	
	/*
	glLoadIdentity();
	
	renderString(-0.6f, -0.6f, "BLACK:");
	renderString(-0.6f, -0.7f, "WHITE:");

 	glLoadIdentity();
	glTranslatef(0.0f, 0.0, 0.8f);
  */
	
}

void ConsoleDisp(){
	Coord coord(0, 0);
	int stone;
	
	static const int BLACK=-1;
	static const int WHITE=1;
	static const int EMPTY=0;
	
	std::cout<<" 12345678"<<std::endl;
	for(int i=1;i<=BoardSize;i++){
		std::cout<<i;
		for(int j=1;j<=BoardSize;j++){
			coord.set(i, j);
			switch(stone=game.board.get(coord)){
			case BLACK:
				std::cout<<"x";
				break;
			case WHITE:
				std::cout<<"o";
				break;
			case EMPTY:
				std::cout<<"-";
				break;
			default:
				break;
			}
		}
		std::cout<<std::endl;
	}
}

void renderString(const float x, const float y, const char* string){
	const float z = -1.0f;
	glColor3dv(black);
	glRasterPos3f(x, y, z);
	char* p = (char*) string;
	while (*p != '\0')
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
}
