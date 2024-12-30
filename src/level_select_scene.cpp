#include "main.hpp"


LevelSelectScene::LevelSelectScene() = default;
LevelSelectScene::~LevelSelectScene() = default;
void LevelSelectScene::Init()
{
    std::cout << "SelectLevel Scene Init" << std::endl;
}
void LevelSelectScene::Draw()
{
    putimage_alpha(0, 0, &img_level_select_background);
    for (int i=0; i<level_number; ++i)
    {
        level_select_btn_list[i].Draw(_T(std::to_string(i+1).c_str()));
    }
    level_select_btn_quit.Draw(_T("Quit"));
    std::cout << "SelectLevel Scene Draw" << std::endl;
}
void LevelSelectScene::Update()
{
    std::cout << "SelectLevel Scene Update" << std::endl;
}
void LevelSelectScene::ProcessMessage(const ExMessage &msg)
{
    for (int i=0; i<level_number; ++i)
    {
        level_select_btn_list[i].ProcessMessage(msg);
    }
    level_select_btn_quit.ProcessMessage(msg);
    std::cout << "SelectLevel Scene ProcessMessage" << std::endl;
}
void LevelSelectScene::Quit()
{
    std::cout << "SelectLevel Scene Quit" << std::endl;
}