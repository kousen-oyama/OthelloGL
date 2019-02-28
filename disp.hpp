#pragma once

#include<iostream>
#include<algorithm>
#include<vector>
#include"game.hpp"
#include"GL/glut.h"

extern const int celSize;

extern const GLdouble black[];
extern const GLdouble white[];
extern const GLdouble green[];

extern void inits();
extern void resize(int w, int h);
extern void keyboard(unsigned char key, int x, int y);
extern void mouse(int button, int state, int x, int y);
extern void display();

extern void glutDispBoard();
extern void glutDispStone();
extern void glutDispScoreAndTurn();
extern void ConsoleDisp();

extern void renderString(const float x, const float y, const char* string);
