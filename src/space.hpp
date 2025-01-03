#include "classes.hpp"
#include "tool.hpp"

extern IMAGE img_space;

extern const int space_width;
extern const int space_height;

class Space
{
	public:
		Space(RECT pos, int color, int value);
		~Space();
		void Draw(int color);
		void SetValue(int value);
		int GetValue();
		Block* GetBlock();
		void SetBlock(Block* block);
		RECT GetPosition();
	private:
		RECT position;
		int value;//空地的编号
        Block* block = nullptr;
};