#pragma once

class bmp
{
private:
    char *_data;
    int width,height;
public:
    bmp(char ** data,int width,int height);
    ~bmp();
    void exports(const char * filename);
};


