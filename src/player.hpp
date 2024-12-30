#pragma once

#include "classes.hpp"
#include "tool.hpp"

extern IMAGE img_player;

extern const double eps;
extern const int move_speed;
extern const int player_width;
extern const int player_height;

class Player
{
	public:
		Player(RECT pos, int color, LPCTSTR path_player, int value);
		~Player();
		void Draw(int color);
		void Move(int x, int y);
		void SetValue(int value);
		int GetValue();
	private:
		RECT position;
		int value;
		IMAGE img;
};