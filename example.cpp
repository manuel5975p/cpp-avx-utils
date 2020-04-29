#include "avx.hpp"
#include <iostream>
int main(){
	vec8f a; //Initialize to 0
	vec8f b(0.0f); //Initialize to 0
	vec8f c(1,2,3,4,5,6,7,8); //Initialize to given values
    vec4d c_pd(1,2,3,4);      //Same for doubles with 4 args
    std::cout << "c = " << c  << "\n";

    float values[8]{8,7,6,5,4,3,2,1};
    vec8f d(values); //Load 8 floats from given address
    std::cout << "d = " << d << "\n";

    vec8f e = c + d; //Arithmetic operations + assignment   
    e += a;
    std::cout << "e = " << e << "\n";
    

    vec4d f(0,10,20,30);
    vec4d g = f.swizzle<3,2,1,0>(); //Swizzle with zero-based indices
    std::cout << "g = " << g << "\n";

    vec4d h = f.xywz();             //vec4d allows for glsl-style swizzle with length 4
    std::cout << "h = " << h<< "\n";

    vec4d bigger(2,3,4,5);
    vec4d smaller(1,2,3,4);
    vec4i comp = (bigger > smaller);//Vector based comparison

    if(comp.all()){                 //Check if all comparisons yield true  
        std::cout << "bigger > smaller\n";
    }
}