#include "level_select_scene.hpp"


LevelSelectScene::LevelSelectScene() = default;
LevelSelectScene::~LevelSelectScene() = default;
void LevelSelectScene::Init()
{
    std::cout << "SelectLevel Scene Init" << std::endl;
}
void LevelSelectScene::Draw()
{
    std::cout << "SelectLevel Scene Draw" << std::endl;
}
void LevelSelectScene::Update()
{
    std::cout << "SelectLevel Scene Update" << std::endl;
}
void LevelSelectScene::ProcessMessage(const ExMessage &msg)
{
    std::cout << "SelectLevel Scene ProcessMessage" << std::endl;
}
void LevelSelectScene::Quit()
{
    std::cout << "SelectLevel Scene Quit" << std::endl;
}