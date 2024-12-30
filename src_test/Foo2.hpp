#pragma once

#include "Foo.hpp"
#include "classes.hpp"

extern int X;

class Foo2 : public Foo 
{
public:
    Foo2(int x, int y);
    ~Foo2();
    void outXY() override; 
};
