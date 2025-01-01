#pragma once


#include "classes.hpp"
#include "button.hpp"

// #include "tool.hpp"
// #include "game_stage.hpp"
// #include "level.hpp"

extern GameStage game_stage;
extern bool is_game_started;
extern int level_value;
extern std::vector<Level> level_list;
extern Level* cur_level;
extern IMAGE img_level_complete;

extern const int button_width;
extern const int button_height;

class LevelSelectButton : public Button
{
	public:
		LevelSelectButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed, int val);
		~LevelSelectButton();
		void Draw(LPCTSTR str) override;
	protected:
		void OnClick() override;
		
	private:
		int value;
};