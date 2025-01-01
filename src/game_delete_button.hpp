#pragma once

#include "button.hpp"
#include "tool.hpp"
#include "classes.hpp"
// #include "game_stage.hpp"
// #include "level.hpp"

extern GameScene game_scene;

class GameDeleteButton : public Button
{
	public:
		GameDeleteButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~GameDeleteButton();
	protected:
		void OnClick() override;
};
