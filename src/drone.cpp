#include <drone.h>
#include <cstring>
#include <cmath>

double pos::dist(pos& _pos){
    int dx = this->x - _pos.x;
    int dy = this->y - _pos.y;
    return std::sqrt(dx*dx + dy*dy);
}

double pos::dist(int x,int y){
    int dx = this->x - x;
    int dy = this->y - y;
    return std::sqrt(dx*dx + dy*dy);
}

drone::drone(int number){
    this->number = number;
    this->_pos.x = 0;
    this->_pos.y = 0;
}

drone::drone(int number,pos &_pos){
    this->number = number;
    std::memcpy(&this->_pos,&_pos,sizeof(pos));
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

void drone::move(int dx,int dy){
    this->_pos.x += dx;
    this->_pos.y += dy;
}