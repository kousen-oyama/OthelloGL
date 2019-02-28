#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include<cstdio>
#include"game.hpp"

const int BoardSize=8;
const int Black=-1;
const int White=1;
const int Empty=0;
const int Wall=2;

Coord::Coord(){
	
}

Coord::Coord(int i, int j):x(i),y(j){
	
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

Order::Order():order(-1){
	
}

Order::Order(int num):order(num){
	
}

Order::~Order(){
	
}

void Order::clear(){
	this->order=-1;
}

void Order::update(){
	this->order=-this->order;
}

int Order::get() const{
	return this->order;
}

Game::Game(){
	this->score[Black]=2;
	this->score[White]=2;
	this->clearPossible();
	this->makePossible();
}

Game::~Game(){
	
}

void Game::clearPossible(){
	this->possible.clear();
}

void Game::clearLog(){
	this->log.clear();
}

void Game::clearScore(){
	this->score[Black]=0;
	this->score[White]=0;	
}

int Game::check(const Coord& coord, const Order& obj) const{
	
	const int stone=this->board.get(coord);
	if(stone!=Empty)
		return NONE;

	int x,y;
	unsigned dir=NONE;
	Coord val;

	val.x=coord.x;
	val.y=coord.y-1;
	if(this->board.get(val)==-obj.get()){
		val.y--;
		while(this->board.get(val)==-obj.get())
			val.y--;
		if(this->board.get(val)==obj.get())
			dir|=UPPER;
	}

	val.x=coord.x;	
	val.y=coord.y+1;
	if(this->board.get(val)==-obj.get()){
		val.y++;
		while(this->board.get(val)==-obj.get())
			val.y++;
		if(this->board.get(val)==obj.get())
			dir|=LOWER;
	}

	val.x=coord.x-1;
	val.y=coord.y;	
	if(this->board.get(val)==-obj.get()){
		val.x--;
		while(this->board.get(val)==-obj.get())
			val.x--;
		if(this->board.get(val)==obj.get())
			dir|=LEFT;
	}

	val.x=coord.x+1;
	val.y=coord.y;	
	if(this->board.get(val)==-obj.get()){
		val.x++;
		while(this->board.get(val)==-obj.get())
			val.x++;
		if(this->board.get(val)==obj.get())
			dir|=RIGHT;
	}

	val.x=coord.x+1;
	val.y=coord.y-1;	
	if(this->board.get(val)==-obj.get()){
		val.x++;
		val.y--;
		while(this->board.get(val)==-obj.get()){
			val.x++;
			val.y--;
		}
		if(this->board.get(val)==obj.get())
			dir|=UPPER_RIGHT;
	}

	val.x=coord.x-1;
	val.y=coord.y-1;	
	if(this->board.get(val)==-obj.get()){
		val.x--;
		val.y--;
		while(this->board.get(val)==-obj.get()){
			val.x--;
			val.y--;
		}
		if(this->board.get(val)==obj.get())
			dir|=UPPER_LEFT;
	}

	val.x=coord.x-1;
	val.y=coord.y+1;	
	if(this->board.get(val)==-obj.get()){
		val.x--;
		val.y++;
		while(this->board.get(val)==-obj.get()){
			val.x--;
			val.y++;
		}
		if(this->board.get(val)==obj.get())
			dir|=LOWER_LEFT;
	}

	val.x=coord.x+1;
	val.y=coord.y+1;	
	if(this->board.get(val)==-obj.get()){
		val.x++;
		val.y++;
		while(this->board.get(val)==-obj.get()){
			val.x++;
			val.y++;
		}
		if(this->board.get(val)==obj.get())
			dir|=LOWER_RIGHT;
	}
	
	return dir;
}

bool Game::isFlip(const Coord &coord) const{
	bool flag=false;
	
	std::for_each(this->possible.at(this->turn.get()).begin(), this->possible.at(this->turn.get()).end(), [&](auto& val){
			if(coord.x==val.x&&coord.y==val.y){
				flag=true;
				return;
			}
		});
	return flag;
}

void Game::makePossible(){
	
	Coord coord;
	std::vector<Coord> vec;
	
	for(int i=1;i<=BoardSize;i++){
		coord.y=i;
		for(int j=1;j<=BoardSize;j++){
			coord.x=j;
			if(this->check(coord,this->order))
				vec.push_back(coord);
		}
	}
	this->possible.push_back(vec);
}

void Game::flip(const Coord& coord){
	//座標を保存しておくように変更する
	int dir=this->check(coord, this->order);
	Coord val;

	this->board.set(coord, this->order.get());

	if(dir&UPPER){
		val.x=coord.x;
		val.y=coord.y-1;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.y--;
		}
	}

	if(dir&LOWER){
		val.x=coord.x;
		val.y=coord.y+1;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.y++;
		}
	}

	if(dir&LEFT){
		val.x=coord.x-1;
		val.y=coord.y;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.x--;
		}
	}

	if(dir&RIGHT){
		val.x=coord.x+1;
		val.y=coord.y;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.x++;
		}
	}

	if(dir&UPPER_RIGHT){
		val.x=coord.x+1;
		val.y=coord.y-1;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.x++;
			val.y--;
		}
	}

	if(dir&UPPER_LEFT){
		val.x=coord.x-1;
		val.y=coord.y-1;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.x--;
			val.y--;
		}
	}

	if(dir&LOWER_LEFT){
		val.x=coord.x-1;
		val.y=coord.y+1;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.x--;
			val.y++;
		}
	}

	if(dir&LOWER_RIGHT){
		val.x=coord.x+1;
		val.y=coord.y+1;
		while(this->board.get(val)!=this->order.get()){
			this->board.set(val, this->order.get());
			val.x++;
			val.y++;
		}
	}
	
	this->turn.update();
	this->order.update();
	this->makePossible();
}

bool Game::move(const Coord &coord){

	std::cout<<std::boolalpha;
	std::cout<<this->isFlip(coord)<<std::endl;

	if(!isFlip(coord))
		return false;

	this->flip(coord);

	if(this->finish()){
		std::cout<<std::endl<<"--finish---"<<std::endl;
		return false;
	}
	
	if(this->pass())
		std::cout<<"---pass---"<<std::endl;
	
	return true;
}

bool Game::pass(){
	
	if(this->possible.size())
		return false;

	this->order.update();
	this->turn.update();
	this->makePossible();
	
	return true;
}

bool Game::finish() const{
	if(this->turn.get()==MaxTurn)
		return true;

	Coord coord;
	Order order(this->order.get());
	
	bool flag=true;
	
	for(int i=1;i<=BoardSize;i++){
		coord.x=i;
		for(int j=1;j<=BoardSize;j++){
			coord.y=j;
			if(this->check(coord, order))
				flag=false;
		}
	}

	return flag;
}

int Game::getScore(const int color) const{
	return this->score[color];
}

