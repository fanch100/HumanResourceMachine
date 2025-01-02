#pragma once

#include "classes.hpp"

extern int X;
class Foo
{
    int x, y;
public:
    Foo(int x, int y);
    Foo& operator=(const Foo& foo);
    Foo(const Foo& foo);
    int getX();
    void setX();
    virtual void outXY();
protected:
    int getY();
private:
    
};
