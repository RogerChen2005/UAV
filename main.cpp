#include <iostream>
#include <matrix.h>

int speed = 2;

int main(){
    matrix m(1000,500,20,30,5);
    m.addDrone();
    m.addDrone({500,500});
    m.step_forward(1600);
    m.output("./1.bmp");
    return 0;
}