#include <iostream>
#include <functional>
#include "Matrix.hpp"

int main(int argc, char * argv[]) {
        srand(time(NULL));
        // number of threads to be used
        // int nw = std::atoi(argv[1]);
        int h = 30;
        int w = 30;
        Matrix *m = new Matrix(h,w);
        m->print();


        // m->set(-23,40,100);
        // std::cout << m->get(-23,40)<<std::endl;
        // m->print();

        m->forEach([&](int i, int j, short *v, int alive, int death){
                if (*v==1) {
                        if(alive<2) *v=0;
                        if(alive>3) *v=0;
                }
                if (*v==0){
                        if (alive==3) *v=1;
                }
        });
        m->print();
        return(0);
}
