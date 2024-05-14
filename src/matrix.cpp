#include <matrix.h>
#include <cstring>
#include <bmp.h>

matrix::matrix()
{
    this->width = MATRIX_WIDTH_DEFAULT;
    this->height = MATRIX_HEIGHT_DEFAULT;
    this->map = new char *[MATRIX_HEIGHT_DEFAULT];
    this->r1 = RADIUS_DEFAULT;
    this->r2 = RADIUS_DEFAULT_EXPAND;
    for (int i = 0; i < MATRIX_HEIGHT_DEFAULT; i++)
    {
        this->map[i] = new char[MATRIX_WIDTH_DEFAULT];
        std::memset(this->map[i], 0, sizeof(char) * MATRIX_WIDTH_DEFAULT);
    }
}

matrix::matrix(const int width, const int height, double r1, double r2)
{
    this->width = width;
    this->height = height;
    this->r1 = r1;
    this->r2 = r2;
    this->map = new char *[height];
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

char matrix::at(int x,int y){
    return this->map[y][x];
}

void matrix::cut(std::function<int(int)> const &top, const std::function<int(int)> &bottom)
{
    for (int i = 0; i < this->width; i++)
    {
        int _bottom = bottom(i);
        int _top = top(i);
        if(_bottom < 0) _bottom = 0;
        if(_top >= this->height) _top = this->height - 1;
        for (int j = _bottom; j <= _top; j++)
        {
            this->map[i][j] = 1;
        }
    }
}

void matrix::cut(std::function<int(int)> const &top, const std::function<int(int)> &bottom,int start,int end)
{
    if(end > this->width || start < 0) return;
    for (int i = start; i <= end; i++)
    {
        int _bottom = bottom(i);
        int _top = top(i);
        if(_bottom < 0) _bottom = 0;
        if(_top >= this->height) _top = this->height - 1;
        for (int j = _bottom; j <= _top; j++)
        {
            this->map[i][j] = 1;
        }
    }
}

void matrix::clear(drone & _drone)
{
    pos &_pos = _drone.getPos();
    int r1 = this->r1;
    this->cut(
        [&_pos,r1](int x) -> int
        {
            int d = _pos.x-x;
            int y = _pos.y + (int)std::sqrt(r1*r1-d*d);
            return y;},
        [&_pos,r1](int x) -> int
        {
            int d = _pos.x-x;
            int y = _pos.y - (int)std::sqrt(r1*r1-d*d);
            return y;},
        _pos.x - r1,_pos.x + r1);
}

double matrix::calculate_direction(drone & _drone){
    pos & _pos = _drone.getPos();
    int cnt = 0;
    double angle_sum = 0.0;
}

void matrix::step_forward()
{
    for (auto &i : this->drones)
    {
        double direction = this->calculate_direction(i);
    }
    return;
}

void matrix::output(const char* filename){
    bmp _bmp(this->map,this->width,this->height);
    _bmp.exports(filename);
}