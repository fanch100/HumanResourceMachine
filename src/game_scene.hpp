#pragma once

#include "classes.hpp"
#include "scene.hpp"
// #include "button.hpp"
// #include "scene_manager.hpp"

extern IMAGE img_game_background;
extern IMAGE block;

extern GameQuitButton game_btn_quit;
extern GamePlayButton game_play_btn;
extern GameFileInputButton game_file_input_btn;

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
        std::vector<Operation> operation_list;
    private:
        TextBox* input_box = nullptr;
};