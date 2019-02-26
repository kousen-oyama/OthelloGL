#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include"game.hpp"

const int BoardSize=8;
const int Black=0;
const int White=1;
const int Empty=2;
const int Wall=3;

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
			std::fill(vec.begin()+1, vec.end()-1, Empty);
		});
	
	this->board.at(BoardSize/2).at(BoardSize/2+1)=Black;
	this->board.at(BoardSize/2+1).at(BoardSize/2)=Black;
	
	this->board.at(BoardSize/2+1).at(BoardSize/2+1)=White;
	this->board.at(BoardSize/2).at(BoardSize/2)=White;
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
	this->turn=0;
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

Score::Score():score(0){
	
}

Score::~Score(){
	
}

void Score::clear(){
	this->score=0;
}


void Score::add(const int num){
	this->score+=num;
}

int Score::get() const{
	return this->score;
}

Game::Game(){
	this->score.resize(2);
	this->score.at(Black).add(2);
	this->score.at(White).add(2);
}

Game::~Game(){
	
}

void Game::clearPossible(){
	this->possible.clear();
}

int Game::check(const Coord& coord) const{
	const int stone=this->board.get(coord);
	if(stone!=Empty)
		return NONE;
	int x,y;
	unsigned dir=NONE;
	
}



