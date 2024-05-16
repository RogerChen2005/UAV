#include <drone.h>
#include <cstring>
#include <iostream>

drone::drone(int number){
    this->remain_step = 0;
    this->number = number;
    this->_pos.x = 0;
    this->_pos.y = 0;
    this->path.push_back(this->_pos);
}

drone::drone(int number,const pos &_pos){
    this->remain_step = 0;
    this->number = number;
    std::memcpy(&this->_pos,&_pos,sizeof(pos));
    this->path.push_back(this->_pos);
}

pos& drone::getPos(){
    return this->_pos;
}

void drone::setPos(pos &_pos){
    std::memcpy(&this->_pos,&_pos,sizeof(pos));
}

void drone::setPos(int x,int y){
    this->_pos.x = x;
    this->_pos.y = y;
}

void drone::move(double dx,double dy,int step){
    if(step > 0){
        this->each_move.x = int(dx+0.5);
        this->each_move.y = int(dy+0.5);
        this->remain_step = step;
        this->isMoving();
    }
    else std::cerr << "Step should > 0" << std::endl;
}

bool drone::isMoving(){
    if(this->remain_step > 0){
        this->_pos += this->each_move;
        this->path.push_back(this->_pos);
        this->remain_step--;
        return true;
    }   
    else return false;
}