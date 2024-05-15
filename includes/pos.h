#pragma once

struct pos{
    int x,y;
    double dist(pos& _pos);
    double dist(int x,int y);
    void operator = (const pos& _pos){
        this->x = _pos.x;
        this->y = _pos.y;
    }
} ;