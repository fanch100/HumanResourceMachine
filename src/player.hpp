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
		void SetPosition(RECT pos);
		RECT GetPosition();
		void SetBlock(Block* block);
		Block* GetBlock();
	private:
		RECT position;
		Block* block = nullptr;
};