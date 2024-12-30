
#include "Foo.hpp"
Foo::Foo(int x, int y): x(x),y(y)
{
}
int Foo::getX()
{
    return this->x;
}
int Foo::getY()
{
    return this->y;
}
void Foo::setX()
{
    this->x = X;
}