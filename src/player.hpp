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
		Player(RECT pos);
		~Player();
		void Draw();
		void SetValue(int value);
		void SetPosition(RECT pos);
		int GetValue();
		RECT GetPosition();
		void SetBlock(Block* block);
		Block* GetBlock();
	private:
		RECT position;
		int value;
		Block* block = nullptr;
};