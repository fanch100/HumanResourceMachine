#pragma once

#include "classes.hpp"
#include "tool.hpp"

class Scene
{
    public:
        Scene();
        ~Scene();
        virtual void Init();
        virtual void Draw();
        virtual void Update();
        virtual void ProcessMessage(const ExMessage &msg);
        virtual void Quit();
    private:
};