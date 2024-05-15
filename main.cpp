#include <iostream>
#include <matrix.h>

int speed = 2;

int main(){
    matrix m(1000,500,20,30,5);
    m.addDrone();
    m.step_forward(2000);
    m.output("./1.bmp");
    return 0;
}