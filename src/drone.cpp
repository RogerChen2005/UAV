#include <drone.h>
#include <cstring>
#include <cmath>

drone::drone(int number){
    this->number = number;
    this->_pos.x = 0;
    this->_pos.y = 0;
    this->path.push_back(this->_pos);
}

drone::drone(int number,const pos &_pos){
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

void drone::move(double dx,double dy){
    this->_pos.x += std::ceil(dx);
    this->_pos.y += std::ceil(dy);
    this->path.push_back(this->_pos);
}