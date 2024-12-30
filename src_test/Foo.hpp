#pragma once

#include "classes.hpp"

extern int X;
class Foo
{
    int x, y;
public:
    Foo(int x, int y);
    int getX();
    void setX();

    virtual void outXY() = 0;
protected:
    int getY();
private:
    
};
