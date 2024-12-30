#pragma once

#include "button.hpp"
#include "game_stage.hpp"

extern GameStage game_stage;

class StartButton : public Button
{
	public:
		StartButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~StartButton();
	protected:
		void OnClick() override;
};