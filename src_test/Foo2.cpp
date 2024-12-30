#include "Foo2.hpp"
extern int X;
Foo2::Foo2(int x, int y): Foo(x,y)
{
    
}
Foo2::~Foo2()= default;
void Foo2::outXY()
{
    std::cout << X << " " << getY() << std::endl;
}