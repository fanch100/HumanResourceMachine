#pragma once

#include "classes.hpp"
#include "scene.hpp"
#include "tool.hpp"

extern MenuScene menu_scene;
extern LevelSelectScene level_select_scene;
extern GameScene game_scene;

class SceneManager 
{
    public:
        SceneManager();
        ~SceneManager();
        enum class GameScene
        {
            Menu = 0,
            LevelSelect,
            Game
        };
        void Update();
        void Draw();
        void ProcessMessage(const ExMessage &msg);
        void ChangeScene(GameScene type);
        void SetScene(Scene *scene);
        //Scene *GetCurrentScene();
    private:
        Scene *current_scene = nullptr;
};