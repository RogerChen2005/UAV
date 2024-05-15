#pragma once

#include <drone.h>
#include <vector>
#include <cmath>
#include <functional>

#define MATRIX_WIDTH_DEFAULT 1000
#define MATRIX_HEIGHT_DEFAULT 1000
#define RADIUS_DEFAULT 5
#define RADIUS_DEFAULT_EXPAND 7
#define MATRIX_SPEED_DEFAULT 2

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
    void step_forward(int steps);
    void cut(std::function<int(int)> const  & top, const std::function<int(int)> & bottom);
    void cut(std::function<int(int)> const  & top, const std::function<int(int)> & bottom,int start,int end);
    void clear(drone & _drone);
    void clearAll();
    double calculate_direction(drone &_drone);
    void output(const char* filename);
};