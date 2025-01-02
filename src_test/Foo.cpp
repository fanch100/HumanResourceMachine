
#include "Foo.hpp"


Foo::Foo(int x, int y): x(x),y(y)
{
}
Foo& Foo::operator=(const Foo& foo)
{
    std::cout << "Foo::operator=" << std::endl;
    this->x = foo.x;
    this->y = foo.y;
    return *this;
}
Foo::Foo(const Foo& foo)
{
    std::cout << "Foo::Foo(const Foo& foo)"  << foo.x << ' ' << foo.y << std::endl;
    *this = foo;
}
void Foo::outXY()
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