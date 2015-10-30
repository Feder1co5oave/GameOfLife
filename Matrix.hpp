#include <functional>
class Matrix
{
short **m;
int w,h;
public:
        Matrix(int h, int w);
        void print();
        short get(int i, int j);
        void set(int i, int j, short v);
        void forEach(std::function<void(int,int,short*,int,int)> f);
private:
        short mod (int x, int y);
        int countAlive(int x, int y);
};
