#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include"game.hpp"

const int BoardSize=8;
const int Black=0;
const int Whitw=1;
const int Wall=2;

Coord::Coord(int i, int j){
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
}

void Board::clear(){
	this->board.clear();
}

void Board::set(const Coord& coord, const int state){
	this->board.at(coord.y).at(coord.x)=state;
}

int Board::get(const Coord& coord){
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

void Turn::get(){
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

int Order::get(){
	return this->order;
}
