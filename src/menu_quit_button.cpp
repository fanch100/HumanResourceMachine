#include "main.hpp"



MenuQuitButton::MenuQuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
{
    
}
MenuQuitButton::~MenuQuitButton() = default;
void MenuQuitButton::OnClick()
{
    is_game_quited = true;
}
