#include "classes.hpp"
#include "tool.hpp"

extern const int operation_width;
extern const int operation_height;

class Operation
{
	public:
		Operation(RECT pos, int value, int type);
		~Operation();
		void Draw(int color);
		void DrawTriangle();
		int GetValue();
		int GetType();
	private:
		RECT position;
		int value;
        int type;
};