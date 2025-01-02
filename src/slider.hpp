#pragma once

#include "classes.hpp"
#include "tool.hpp"
// #include "game_stage.hpp"

extern const int window_width;
extern const int window_height;
extern const int slider_width;
extern const int slider_height;

extern std::unordered_map<std::string, int> operation_name_to_number;
extern std::unordered_map<int, std::string> operation_number_to_name;

class Slider
{
	public:
		Slider(RECT pos, int type);
		~Slider();
		void Draw();
		void ProcessMessage(const ExMessage &msg);
	protected:
		//virtual void OnClick() = 0;//在子类按钮按下时重写逻辑
		void OnClick();
		enum class Stage
		{
			Default = 0,//默认
			Hovered,//光标
			Pushed,//按下
		};
		enum class Type
		{
			Inbox = 0,
			Outbox,
			CopyFrom,
			CopyTo,
			Add,
			Sub,
			Jump,
			JumpIfZero
		};
		Stage stage;
	private:
		RECT position;
		int cur_x, cur_y;
		int type;
		bool CheckCursorInSlider(int x, int y);
};
