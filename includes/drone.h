#pragma once
#include <vector>
#include <pos.h>
#include <ref.h>

class drone
{
private:
    pos _pos,each_move;
    int number,remain_step;
public:
    std::vector<pos> path;
    drone(int number);
    drone(int number,const pos &_pos);
    pos& getPos();
    void setPos(pos &_pos);
    void setPos(int x,int y);
    void move(double dx,double dy,int step);
    bool isMoving();
};
