#include <matrix.h>
#include <cstring>
#include <bmp.h>
#include <iostream>
#include <pos.h>

const int q = 16;
const int max_try = 10;

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
            this->map[j][i] = 1;
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

double matrix::calculate_region(pos& _pos,double angle,int speed)
{
    double income = 0.0;
    int mx = (int)(_pos.x + std::cos(angle) * speed + 0.5);
    int my = (int)(_pos.y + std::sin(angle) * speed + 0.5);
    int inner_white_block=0,outer_white_block=0;
    int inner_black_block=0,outer_black_block=0;
    int inner_none_block=0,outer_none_block=0;
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
                if (!this->map[y][x]) outer_black_block++;
                else outer_white_block++;
            }
            else outer_none_block++;
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
                if (!this->map[y][x]) inner_black_block++;
                else inner_white_block++;
            }
            else inner_none_block++;
        }
    }
    outer_black_block -= inner_black_block;
    outer_white_block -= inner_white_block;
    outer_none_block -= inner_none_block;
    // income = 1.0 * inner_black_block + 0.5 * (outer_white_block + outer_none_block) \
    // + 0.2 * outer_black_block - 0.5 * inner_none_block;
    income = 1.0 * inner_black_block + 0.5 * outer_black_block;
    return income;
}

void matrix::calculate_direction(drone &_drone,double* angle,int* step)
{
    pos &_pos = _drone.getPos();
    double angle_max,income_max;
    int distance_max=-1;
    pos dot[4] = {{0,0},{0,this->height-1},{this->width-1,0},{this->width-1,this->height-1}};
    for(int i = 0;i < 4;i++){
        int dx = dot[i].x - _pos.x, dy = dot[i].y - _pos.y;
        int distance = std::ceil(std::sqrt(dx*dx+dy*dy));
        if(distance > distance_max) distance_max = distance;
    }
    int area = PI * (this->r2 * this->r2 - this->r1 * this->r1),cnt = 0;
    int accelerate = (distance_max-this->speed) / (max_try-1);
    do{
        if(++cnt >= max_try) break;
        angle_max = 0.0,income_max = 0.0;
        for (int i = 0; i <= q; i++)
        {
            double angle = PI * (2.0 * i / q - 1.0);
            double income = this->calculate_region(_pos,angle,this->speed + accelerate * (cnt-1));
            if (income > income_max)
            {
                income_max = income;
                angle_max = angle;
            }
        }
    }
    while(income_max / area < 0.52);
    *angle = angle_max;
    if(cnt == max_try) *step = 0;
    else *step = (this->speed + accelerate * (cnt-1)) / this->speed;
}


int matrix::step_forward(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        for (auto &drone : this->drones)
        {
            this->clear(drone);
            if(!drone.isMoving()){
                double direction;
                int step;
                this->calculate_direction(drone,&direction,&step);
                if(step)
                    drone.move(std::cos(direction) * this->speed, std::sin(direction) * this->speed,step);
            }
        }
    }
    return this->calculate_coverage();
}

int matrix::calculate_coverage(){
    int cnt = 0;
    for(int i = 0;i < this->width;i++){
        for(int j = 0;j < this->height;j++){
            if(!this->map[j][i]) cnt++;
        }
    }
    return cnt;
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