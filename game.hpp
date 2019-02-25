#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#include"GL/glut.h"

extern const int BoardSize;
extern const int Black;
extern const int Whitw;
extern const int Wall;

struct Coord{
	int x;
	int y;
};

class Board{
private:
public:
	Board(){};
	~Board(){};
	std::vector<std::vector<int>> board;
	void clear();
	void inits();
	void set(const Coord coord, const int state);
	void get(const Coord coord);
};

class Turn{
private:
	int turn;
public:
	Turn():turn(0){};
	~Turn(){};
	void clear();
	void Change();
	int get();
};

class Game{
private:
	Turn turn;
public:
	Game(){};
	~Game(){};
};

class Score{
private:
	int score;
public:
	Score():score(0){}
	~Score(){}
	void clear();
	void add();
	int get(int num);
};


