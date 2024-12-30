#pragma once

#include "classes.hpp"
#include "tool.hpp"

extern IMAGE img_btn_default;
extern IMAGE img_btn_hovered;
extern IMAGE img_btn_pushed;

class Button
{
	public:
		Button(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed);
		~Button();
		void Draw(LPCTSTR str);
		virtual void ProcessMessage(const ExMessage &msg);
	protected:
		virtual void OnClick() = 0;//在子类按钮按下时重写逻辑
		enum class Stage
		{
			Default = 0,//默认
			Hovered,//光标
			Pushed,//按下
		};
		Stage stage = Stage::Default;
	private:
		RECT position;
		IMAGE btn_default;
		IMAGE btn_hovered;
		IMAGE btn_pushed;
		bool CheckCursorInButton(int x, int y);//判断光标是否在按钮上
};