#pragma once

#include "scene.hpp"
#include "tool.hpp"

extern Scene menu_scene;
extern Scene level_select_scene;
extern Scene game_scene;

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
        Scene *GetCurrentScene();
    private:
        Scene *current_scene = nullptr;
};