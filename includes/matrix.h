#pragma once

#include <drone.h>
#include <vector>
#include <cmath>
#include <functional>
#include <ref.h>

extern int speed;

class matrix
{
private:
    char **map;
    int width, height, speed;
    double r1, r2;
    std::vector<drone> drones;

public:
    matrix();
    matrix(int width, int height, double r1, double r2,int speed);
    ~matrix();
    int getWidth();
    int getHeight();
    void addDrone();
    void addDrone(const pos& _pos);
    char at(int x,int y);
    int step_forward(int steps);
    void cut(std::function<int(int)> const  & top, const std::function<int(int)> & bottom);
    void cut(std::function<int(int)> const  & top, const std::function<int(int)> & bottom,int start,int end);
    void clear(drone & _drone);
    void clearAll();
    void calculate_direction(drone &_drone,double* angle,int* step);
    double calculate_region(pos& _pos,double angle,int speed);
    int calculate_coverage();
    void output(const char* filename);
};