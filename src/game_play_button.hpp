#pragma once

#include "button.hpp"
#include "tool.hpp"
#include "classes.hpp"
// #include "game_stage.hpp"
// #include "level.hpp"

extern SceneManager scene_manager;

class GamePlayButton : public Button
{
	public:
		GamePlayButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~GamePlayButton();
	protected:
		void OnClick() override;
};
