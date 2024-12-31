#include "classes.hpp"
#include "tool.hpp"

extern IMAGE img_block;

extern const double eps;
extern const int move_speed;
extern const int block_width;
extern const int block_height;

class Block
{
	public:
		Block(RECT pos, int color, int value);
        Block(const Block& block);
		~Block();
		void Draw(int color);
		bool Move(int x, int y);
		void SetValue(int value);
		int GetValue();
		RECT GetPosition();
		void SetPosition(RECT pos);
		bool is_hiding = false;
	private:
		RECT position;
		int value;
};