#include "main.hpp"

MenuScene::MenuScene() = default;
MenuScene::~MenuScene() = default;
void MenuScene::Init()
{
    ;
}
void MenuScene::Draw()
{
    ;
    putimage_alpha(0, 0, &img_menu_background);
    menu_btn_start.Draw(_T("Start"));
	menu_btn_quit.Draw(_T("Quit"));
    // outtextxy(100, 100, "Menu Scene");
}
void MenuScene::Update()
{
    ;
}
void MenuScene::ProcessMessage(const ExMessage &msg)
{
    menu_btn_start.ProcessMessage(msg);
    menu_btn_quit.ProcessMessage(msg);
}
void MenuScene::Quit()
{
    ;
}