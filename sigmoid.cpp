#include <iostream>
#include <cmath>

float sig(float n){
    float res = 1/(1 + std::exp(-n));
    return res;
    //return std::max(0.0f, n);
}
