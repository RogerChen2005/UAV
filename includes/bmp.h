#pragma once
#include <pos.h>
#include <vector>

struct rgb{
    unsigned char r,g,b;
    void change (const unsigned char r,const unsigned char g,const unsigned char b);
};

class bmp
{
private:
    rgb *_data;
    int width,height;
public:
    bmp(char ** data,int width,int height);
    ~bmp();
    void exports(const char * filename);
    void draw(std::vector<pos>& path,double h);
    void draw(pos* path,int length);
};


