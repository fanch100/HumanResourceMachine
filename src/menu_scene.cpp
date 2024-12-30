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
    menu_btn_start.Draw(_T("Start"));
	menu_btn_quit.Draw(_T("Quit"));
    // outtextxy(100, 100, "Menu Scene");
}
void MenuScene::Update()
{
    // std:: cout << "Menu Scene Update" << std::endl;
}
void MenuScene::ProcessMessage(const ExMessage &msg)
{
    std:: cout << "Menu Scene ProcessMessage" << std::endl;
    menu_btn_start.ProcessMessage(msg);
    menu_btn_quit.ProcessMessage(msg);
}
void MenuScene::Quit()
{
    std:: cout << "Menu Scene Quit" << std::endl;
}