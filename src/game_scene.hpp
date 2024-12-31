#pragma once

#include "classes.hpp"
#include "scene.hpp"
// #include "button.hpp"
// #include "scene_manager.hpp"

extern IMAGE img_game_background;
extern IMAGE block;

extern GameQuitButton game_btn_quit;

class GameScene : public Scene
{
    public:
        GameScene();
        ~GameScene();
        void Init();
        void Draw();
        void Update();
        void ProcessMessage(const ExMessage &msg);
        void Quit();
    private:
        TextBox* input_box = nullptr;
};