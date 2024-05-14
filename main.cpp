#include <iostream>
#include <matrix.h>

int main(){
    matrix m;
    m.cut([](int x){return x*x/1000;},[](int x){return 0;});
    m.output("./1.bmp");
    return 0;
}