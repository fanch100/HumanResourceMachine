#pragma once

#include "button.hpp"
#include "tool.hpp"
#include "classes.hpp"
// #include "game_stage.hpp"
// #include "level.hpp"

extern GameScene game_scene;

class GameInputButton : public Button
{
	public:
		GameInputButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~GameInputButton();
	protected:
		void OnClick() override;
};
