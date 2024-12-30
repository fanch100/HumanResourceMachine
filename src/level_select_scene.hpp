#pragma once

#include "classes.hpp"
#include "scene.hpp"

// #include "scene_manager.hpp"
// #include "button.hpp"
// #include "tool.hpp"

extern IMAGE img_level_select_background;
extern int level_number;
extern std::vector<LevelSelectButton> level_select_btn_list;
extern LevelSelectQuitButton level_select_btn_quit;

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