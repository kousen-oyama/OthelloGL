#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#include"GL/glut.h"

extern const int BoardSize;
extern const int Black;
extern const int White;
extern const int Wall;

class Coord{
private:
public:
	Coord(){};
	Coord(int i, int j);
	void set(int i, int j);
public:
	int x;
	int y;
};

class Board{
private:
	std::vector<std::vector<int>> board;
public:
	Board();
	~Board();
	void clear();
	void inits();
	void set(const Coord& coord, const int state);
	int get(const Coord& coord) const;
};

class Turn{
private:
	int turn;
public:
	Turn();
	~Turn(){};
	void clear();
	void update();
	int get() const;
};

class Order{
private:
	int order;
public:
	Order();
	~Order();
	void clear();
	void update();
	int get() const;
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
	
class Game{
private:
public:
	Turn turn;
	Order order;
	Score score;
	Board board;
public:
	Game(){};
	~Game(){};
};



