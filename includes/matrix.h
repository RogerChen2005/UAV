#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_WIDTH_DEFAULT 1000
#define MATRIX_HEIGHT_DEFAULT 1000

class matrix
{
private:
    char **map;
    int width,height;
public:
    matrix();
    matrix(int width,int height);
    ~matrix();
    int getWidth();
    int getHeight();
};
#endif