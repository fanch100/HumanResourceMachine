#pragma once

#include "button.hpp"
#include "tool.hpp"
#include "classes.hpp"
// #include "game_stage.hpp"
// #include "level.hpp"

extern SceneManager scene_manager;
extern GameScene game_scene;

class GameStopButton : public Button
{
	public:
		GameStopButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~GameStopButton();
	protected:
		void OnClick() override;
};
