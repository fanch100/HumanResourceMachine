#pragma once

#include "button.hpp"
#include "tool.hpp"
#include "classes.hpp"
// #include "game_stage.hpp"
// #include "level.hpp"

extern bool is_game_quited;

class MenuQuitButton : public Button
{
	public:
		MenuQuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~MenuQuitButton();
	protected:
		void OnClick() override;
};
