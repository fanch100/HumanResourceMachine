#include "main.hpp"



GameStopButton::GameStopButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
GameStopButton::~GameStopButton() = default;
void GameStopButton::OnClick()
{
    std:: cout << "GameStopButton::OnClick()" << std::endl;
}
