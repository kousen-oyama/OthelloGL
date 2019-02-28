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

template<typename T> class Score{
private:
	//score[0]¹õÀÐ¡¢score[1]ÇòÀÐ
	T score[3];
public:
	T& operator[](int color){
		return this->score[color+1];
	}
	const T& operator[](int color) const{
		return this->score[color+1];
	}
};
	
class Game{
private:
	Score<int> score;
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
	std::vector<std::vector<Coord>> possible;
	std::vector<std::vector<Coord>> log;
private:
	void clearPossible();
	void clearLog();
	void clearScore();
	int check(const Coord& coord) const;
	void makePossible();
	void flip(const Coord& coord);
	bool isFlip(const Coord& coord) const;
public:
	Turn turn;
	Order order;
	Board board;
public:
	Game();
	~Game();
	bool move(const Coord& coord);
	int getScore(int color) const; 
};



