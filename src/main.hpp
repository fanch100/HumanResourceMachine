#pragma once

#include "classes.hpp"
#include "tool.hpp"
#include "level.hpp"

#include "block.hpp"
#include "slider.hpp"
#include "player.hpp"

#include "button.hpp"
#include "start_button.hpp"
#include "level_select_button.hpp"
#include "menu_quit_button.hpp"
#include "level_select_quit_button.hpp"
#include "game_quit_button.hpp"

#include "scene.hpp"
#include "scene_manager.hpp"
#include "menu_scene.hpp"
#include "game_scene.hpp"
#include "level_select_scene.hpp"

#include "text_box.hpp"

void init_select_level();
void load_resources();
// class Animation
// {
// public:
// 	Animation(LPCSTR path, int num, int interval)
// 	{
// 		interver_ms = interval;

// 		TCHAR path_file[256];
// 		for (int i = 0; i < num; i++)
// 		{
// 			sprintf(path_file, "%s%d.png", path, i);
// 			images.push_back(path_file);
// 		}
// 	}
// private:
// }

// struct Point
// {
// 	int x, y;
// };

// std::vector<Slider*> slider_list;

// struct Operation
// {
// 	int type, value;
// };
// std::vector<Operation> operation_list;

// class Player
// {
// 	public:
// 		Player(RECT pos, int color, LPCTSTR path_player, int value)
// 		{
// 			position = pos;
// 			this->value = value;
// 			loadimage(&img, path_player);
// 		}
// 		~Player() = default;
// 		void Draw(int color)
// 		{
// 			// setlinecolor(color);
// 			// setfillcolor(color);
// 			putimage_alpha(position.left, position.top, &img_player);
// 			settextcolor(color);//设置字体颜色
// 			settextstyle(20, 0, _T("monospace"));//设置字体
// 			//outtextxy(position.left+10, position.top+40, str);//输出文字
// 			// drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
// 			drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
// 		}
// 		void Move(int x, int y)
// 		{
// 			int delta_x = x - position.left;
// 			int delta_y = y - position.top;
// 			double dis = std::sqrt(delta_x * delta_x + delta_y * delta_y);
// 			if (fabs(dis) > eps)
// 			{
// 				int final_x = (int)(delta_x * move_speed / dis) + position.left;
// 				int final_y = (int)(delta_y * move_speed / dis) + position.top;
// 				position = {final_x, final_y, final_x + block_width, final_y + block_height};
// 			}
// 		}
// 		void SetValue(int value)
// 		{
// 			this->value = value;
// 		}
// 		int GetValue()
// 		{
// 			return value;
// 		}
// 	private:
// 		RECT position;
// 		int value;
// 		IMAGE img;
// };


void init_select_level();


