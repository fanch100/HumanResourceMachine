#pragma once

#include "classes.hpp"
#include "scene.hpp"

// #include "scene_manager.hpp"
// #include "button.hpp"
// #include "tool.hpp"

extern IMAGE menu_background;

class LevelSelectScene : public Scene
{
    public:
        LevelSelectScene();
        ~LevelSelectScene();
        void Init();
        void Draw();
        void Update();
        void ProcessMessage(const ExMessage &msg);
        void Quit();
    private:
};