#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
#include"GL/glut.h"

extern const int BoardSize;
extern const int Black;
extern const int Empty;
extern const int White;
extern const int Wall;

class Coord{
private:
public:
	Coord();
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
	Score();
	~Score();
	void clear();
	void add(const int num);
	int get() const;
};
	
class Game{
private:
	enum Direction{
		NONE=0,
		UPPER=1,
		UPPER_LEFT=2,
		LEFT=4,
		LOWER_LEFT=8,
		LOWER=16,
		LOWER_RIGHT=32,
		RIGHT=64,
		UPPER_RIGHT=128
	};
	std::vector<std::vector<int>> possible;
private:
	void clearPossible();
public:
	//score[0]πı¿–°¢score[1]«Ú¿–
	std::vector<Score> score;
	Turn turn;
	Order order;
	Board board;
public:
	Game();
	~Game();
	int check(const Coord& coord) const;
};



