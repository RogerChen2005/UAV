#include <matrix.h>
#include <iostream>

matrix::matrix(){
    this->width = MATRIX_WIDTH_DEFAULT;
    this->height = MATRIX_HEIGHT_DEFAULT;
    this->map = new char* [MATRIX_WIDTH_DEFAULT];
    for(int i = 0;i < MATRIX_WIDTH_DEFAULT;i++){
        this->map[i] = new char[MATRIX_WIDTH_DEFAULT];
    }
}

matrix::matrix(const int width,const int height){
    this->width = width;
    this->height = height;
    this->map = new char* [width];
    for(int i = 0;i < width;i++){
        this->map[i] = new char[height];
    }
}

matrix::~matrix(){
    for(int i = 0;i < this->height;i++){
        delete[] this->map[i];
    }
    delete[] this->map;
}

int matrix::getHeight(){
    return this->height;
}

int matrix::getWidth(){
    return this->width;
}