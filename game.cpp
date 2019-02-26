#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include"game.hpp"

const int BoardSize=8;
const int Black=0;
const int White=1;
const int Wall=2;

Coord::Coord(int i, int j){
	this->x=i;
	this->y=j;
}

void Coord::set(int i, int j){
	this->x=i;
	this->y=j;
}

Board::Board(){
	inits();
}

Board::~Board(){
	
}

void Board::inits(){
	this->board.resize(BoardSize+2);
	std::for_each(this->board.begin(), this->board.end(), [](auto& vec){
			vec.resize(BoardSize+2);
		});
	std::for_each(this->board.begin(), this->board.end(), [](auto& vec){
			std::fill(vec.begin(), vec.end(), Wall);
		});
	std::for_each(this->board.begin()+1, this->board.end()-1, [](auto& vec){
			std::fill(vec.begin()+1, vec.end()-1, Wall);
		});
	/*
	 board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = BLACK;
   board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = BLACK;
    
   board[BOARD_SIZE / 2][BOARD_SIZE / 2] = WHITE;
   board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = WHITE;
	*/
	this->board.at(BoardSize/2-1).at(BoardSize/2)=Black;
	this->board.at(BoardSize/2).at(BoardSize/2-1)=Black;
	
	this->board.at(BoardSize/2).at(BoardSize/2)=White;
	this->board.at(BoardSize/2-1).at(BoardSize/2-1)=White;
}

void Board::clear(){
	this->board.clear();
}

void Board::set(const Coord& coord, const int state){
	this->board.at(coord.y).at(coord.x)=state;
}

int Board::get(const Coord& coord) const{
	return this->board.at(coord.y).at(coord.x);
}

Turn::Turn():turn(0){
	
}

void Turn::clear(){
	turn=0;
}

void Turn::update(){
	this->turn++;
}

int Turn::get() const{
	return this->turn;
}

Order::Order():order(0){
	
}

Order::~Order(){
	
}

void Order::clear(){
	this->order=0;
}

void Order::update(){
	this->order=this->order%2;
}

int Order::get() const{
	return this->order;
}
