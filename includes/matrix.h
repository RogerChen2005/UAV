#pragma once

#include <drone.h>
#include <vector>
#include <cmath>
#include <functional>

#define MATRIX_WIDTH_DEFAULT 1000
#define MATRIX_HEIGHT_DEFAULT 1000
#define RADIUS_DEFAULT 5
#define RADIUS_DEFAULT_EXPAND 7

class matrix
{
private:
    char **map;
    int width, height;
    double r1, r2;
    std::vector<drone> drones;

public:
    matrix();
    matrix(int width, int height, double r1, double r2);
    ~matrix();
    int getWidth();
    int getHeight();
    void addDrone();
    char at(int x,int y);
    void step_forward();
    void cut(std::function<int(int)> const  & top, const std::function<int(int)> & bottom);
    void cut(std::function<int(int)> const  & top, const std::function<int(int)> & bottom,int start,int end);
    void clear(drone & _drone);
    double calculate_direction(drone &_drone);
    void output(const char* filename);
};