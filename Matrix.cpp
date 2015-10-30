#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"

//Costruttore
Matrix::Matrix(int h, int w){
    srand(time(NULL));
    this->h = h;
    this->w = w;
    this->m = new short*[h];
    for (int i=0; i<h; i++) {
        this->m[i] = new short[w];
        for (int j=0; j<w; j++) {
                this->m[i][j] = floor(rand()%2);
        }
    }
}

void Matrix::print(){
    // Print::matrix((short**)&m[0][0],h,w);
    std::cout << "\n";
    int h = this->h;
    int w = this->w;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            std::cout << this->m[i][j] << " ";
        }
        std::cout << "\n";
    }
}

short Matrix::get(int i, int j){
    return this->m[mod(i,h)][mod(j,w)];
}

void Matrix::set(int i, int j, short v){
    i = mod(i,this->h);
    j = mod(j,this->w);
    this->m[i][j] = v;
}


void Matrix::forEach(std::function<void(int,int,short*,int,int)> f) {
    for (int i=0; i<this->h; i++) {
        for (int j=0; j<this->w; j++) {
            int alive = countAlive(i, j);
            f(i,j,&this->m[i][j],alive,8-alive);
        }
    }
}

int Matrix::countAlive(int x, int y){
    int count = 0;
    for (int i=x-1;i<=x+1;i++){
        for (int j=y-1;j<y+1;j++){
            if (i!=x && j!=y && get(i,j)==1){
                count++;
            }
        }
    }
    return count;
}

short Matrix::mod(int a, int b){
    return (a%b+b)%b;
}
