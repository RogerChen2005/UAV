#pragma once

struct pos{
    int x,y;
    double dist(pos& _pos);
    double dist(int x,int y);
} ;

class drone
{
private:
    pos _pos;
    int number;
public:
    drone(int number);
    drone(int number,pos &_pos);
    pos& getPos();
    void setPos(pos &_pos);
    void setPos(int x,int y);
    void move(int dx,int dy);
};
