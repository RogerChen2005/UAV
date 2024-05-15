#pragma once
#include <vector>
#include <pos.h>

class drone
{
private:
    pos _pos;
    int number;
public:
    std::vector<pos> path;
    drone(int number);
    drone(int number,const pos &_pos);
    pos& getPos();
    void setPos(pos &_pos);
    void setPos(int x,int y);
    void move(double dx,double dy);
};
