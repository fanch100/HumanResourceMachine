#include "HumanResourceMachine.hpp"
int X;
int main()
{
    // TODO
    Foo2 foo2(1,2);
    X=123;
    foo2.setX();
    foo2.outXY();
    Foo foo(1,2);
    Foo foo1 = foo;
    std::vector<Foo> vec;
    vec.push_back(Foo(2,3));
    std:: cout << vec[0].getX() << std::endl;
    return 0;
}
