#pragma once

#include "button.hpp"
#include "tool.hpp"
#include "classes.hpp"
#include "game_stage.hpp"
#include "level.hpp"

extern bool is_game_quited;

class QuitButton : public Button
{
	public:
		QuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~QuitButton();
	protected:
		void OnClick() override;
};
