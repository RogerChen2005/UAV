#include <pos.h>
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
