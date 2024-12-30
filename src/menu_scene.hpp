#pragma once

#include "classes.hpp"
#include "scene.hpp"

// #include "scene_manager.hpp"
// #include "button.hpp"
// #include "tool.hpp"

extern IMAGE img_menu_background;

extern StartButton menu_btn_start;
extern MenuQuitButton menu_btn_quit;

class MenuScene : public Scene
{
    public:
        MenuScene();
        ~MenuScene();
        void Init();
        void Draw();
        void Update();
        void ProcessMessage(const ExMessage &msg);
        void Quit();
    private:
};