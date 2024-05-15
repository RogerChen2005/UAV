#include <matrix.h>
#include <cstring>
#include <bmp.h>
#include <iostream>
#include <pos.h>

matrix::matrix()
{
    this->width = MATRIX_WIDTH_DEFAULT;
    this->height = MATRIX_HEIGHT_DEFAULT;
    this->map = new char *[MATRIX_HEIGHT_DEFAULT];
    this->r1 = RADIUS_DEFAULT;
    this->r2 = RADIUS_DEFAULT_EXPAND;
    this->speed = MATRIX_SPEED_DEFAULT;
    for (int i = 0; i < MATRIX_HEIGHT_DEFAULT; i++)
    {
        this->map[i] = new char[MATRIX_WIDTH_DEFAULT];
        std::memset(this->map[i], 0, sizeof(char) * MATRIX_WIDTH_DEFAULT);
    }
}

matrix::matrix(const int width, const int height, double r1, double r2, int speed)
{
    this->width = width;
    this->height = height;
    this->r1 = r1;
    this->r2 = r2;
    this->map = new char *[height];
    this->speed = speed;
    for (int i = 0; i < height; i++)
    {
        this->map[i] = new char[width];
        std::memset(this->map[i], 0, sizeof(char) * width);
    }
}

matrix::~matrix()
{
    for (int i = 0; i < this->height; i++)
    {
        delete[] this->map[i];
    }
    delete[] this->map;
}

int matrix::getHeight()
{
    return this->height;
}

int matrix::getWidth()
{
    return this->width;
}

void matrix::addDrone()
{
    drone drone_t(this->drones.size());
    this->drones.push_back(drone_t);
}

void matrix::addDrone(const pos &_pos)
{
    drone drone_t(this->drones.size(), _pos);
    this->drones.push_back(drone_t);
}

char matrix::at(int x, int y)
{
    return this->map[y][x];
}

void matrix::cut(std::function<int(int)> const &top, const std::function<int(int)> &bottom)
{
    for (int i = 0; i < this->width; i++)
    {
        int _bottom = bottom(i);
        int _top = top(i);
        if (_bottom < 0)
            _bottom = 0;
        if (_top >= this->height)
            _top = this->height - 1;
        for (int j = _bottom; j <= _top; j++)
        {
            this->map[i][j] = 1;
        }
    }
}

void matrix::cut(std::function<int(int)> const &top, const std::function<int(int)> &bottom, int start, int end)
{

    if (end >= this->width)
        end = this->width - 1;
    if (start < 0)
        start = 0;
    for (int i = start; i <= end; i++)
    {
        int _bottom = bottom(i);
        int _top = top(i);
        if (_bottom < 0)
            _bottom = 0;
        if (_top >= this->height)
            _top = this->height - 1;
        for (int j = _bottom; j <= _top; j++)
        {
            this->map[j][i] = 1;
        }
    }
}

void matrix::clear(drone &_drone)
{
    pos &_pos = _drone.getPos();
    int r1 = this->r1;
    this->cut(
        [&_pos, r1](int x) -> int
        {
            int d = _pos.x-x;
            int y = _pos.y + std::ceil(std::sqrt(r1*r1-d*d));
            return y; },
        [&_pos, r1](int x) -> int
        {
            int d = _pos.x-x;
            int y = _pos.y - std::ceil(std::sqrt(r1*r1-d*d));
            return y; },
        _pos.x - r1, _pos.x + r1);
}

void matrix::clearAll()
{
    for (drone &x : this->drones)
    {
        this->clear(x);
    }
}

// double matrix::calculate_direction(drone &_drone)
// {
//     pos &_pos = _drone.getPos();
//     int cnt = 0;
//     double angle_sum = 0.0;
//     int left = _pos.x - this->r2, right = _pos.x + this->r2;
//     for (int x = left; x <= right; x++)
//     {
//         int dx = x - _pos.x;
//         int c = std::ceil(std::sqrt(this->r2 * this->r2 - dx * dx));
//         int bottom = _pos.y - c, top = _pos.y + c;
//         for (int y = bottom; y <= top; y++)
//         {
//             int dy = y - _pos.y;
//             int distance = std::ceil(std::sqrt(dx * dx + dy * dy));
//             if (distance > r1)
//             {
//                 cnt++;
//                 if (x > 0 && x < this->width && y > 0 && y < this->height)
//                 {
//                     if (!this->map[y][x])
//                         angle_sum += std::atan2(dy, dx);
//                 }
//             }
//         }
//     }
//     return angle_sum / cnt;
// }

double matrix::calculate_direction(drone &_drone)
{
    pos &_pos = _drone.getPos();
    double angle_max = 0.0;
    double income_max = 0.0;
    int q = 12;
    for (int i = 0; i <= q; i++)
    {
        double angle = M_PI * (2.0 * i / q - 1.0);
        double income = 0.0;
        int mx = (int)(_pos.x + std::cos(angle) * this->speed*3 + 0.5);
        int my = (int)(_pos.y + std::sin(angle) * this->speed*3 + 0.5);
        int left = mx - this->r2, right = mx + this->r2;
        for (int x = left; x <= right; x++)
        {
            int dx = x - mx;
            int c = std::ceil(std::sqrt(this->r2 * this->r2 - dx * dx));
            int bottom = my - c, top = my + c;
            for (int y = bottom; y <= top; y++)
            {
                if (x > 0 && x < this->width && y > 0 && y < this->height)
                {
                    if (!this->map[y][x]) continue;
                }
                income += 0.2;
            }
        }
        left = mx - this->r1, right = mx + this->r1;
        for (int x = left; x <= right; x++)
        {
            int dx = x - mx;
            int c = std::ceil(std::sqrt(this->r1 * this->r1 - dx * dx));
            int bottom = my - c, top = my + c;
            for (int y = bottom; y <= top; y++)
            {
                if (x > 0 && x < this->width && y > 0 && y < this->height)
                {
                    if (!this->map[y][x]){
                        income += 1.0;
                        continue;
                    }
                }
                income -= 0.2;
            }
        }
        if(income > income_max){
            income_max = income;
            angle_max = angle;
        }
    }
    return angle_max;
}

void matrix::step_forward(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        for (auto &drone : this->drones)
        {
            this->clear(drone);
            double direction = this->calculate_direction(drone);
            double temp = std::sin(direction);
            drone.move(std::cos(direction) * this->speed, std::sin(direction) * this->speed);
        }
    }
    return;
}

void matrix::output(const char *filename)
{
    bmp _bmp(this->map, this->width, this->height);
    const int length = this->drones.size();
    for (int i = 0; i < length; i++)
    {
        _bmp.draw(this->drones[i].path, 1.0 * (i + 1) / length);
    }
    _bmp.exports(filename);
}