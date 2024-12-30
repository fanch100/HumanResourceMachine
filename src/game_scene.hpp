#pragma once

#include "classes.hpp"
#include "scene.hpp"
// #include "button.hpp"
// #include "scene_manager.hpp"

extern IMAGE game_background;
extern IMAGE block;

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
};