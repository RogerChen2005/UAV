#include <iostream>
#include <matrix.h>

int speed = 2;

int main(){
    matrix m(2000,1000,20,30,10);
    m.cut([](int x){
        return x * 0.3;
    },[](int x){
        return 0;
    });
    m.cut([](int x){
        return 2000;
    },[](int x){
        return 1000 - (x-1000) * 0.7;
    });
    m.addDrone();
    m.addDrone({500,500});
    m.addDrone({1000,200});
    m.step_forward(2000);
    m.output("./1.bmp");
    return 0;
}