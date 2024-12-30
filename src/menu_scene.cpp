#include "main.hpp"

MenuScene::MenuScene() = default;
MenuScene::~MenuScene() = default;
void MenuScene::Init()
{
    std:: cout << "Menu Scene Init" << std::endl;
}
void MenuScene::Draw()
{
    // std:: cout << "Menu Scene Draw" << std::endl;
    putimage_alpha(0, 0, &img_menu_background);
    printf("w=%d h=%d\n",img_menu_background.getwidth(), img_menu_background.getheight());
    // outtextxy(100, 100, "Menu Scene");
}
void MenuScene::Update()
{
    // std:: cout << "Menu Scene Update" << std::endl;
}
void MenuScene::ProcessMessage(const ExMessage &msg)
{
    // std:: cout << "Menu Scene ProcessMessage" << std::endl;
}
void MenuScene::Quit()
{
    std:: cout << "Menu Scene Quit" << std::endl;
}