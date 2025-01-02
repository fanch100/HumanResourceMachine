#include "classes.hpp"

void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();			// Get the width of the image
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
}

void outtextxy_shaded(int x, int y, LPCTSTR str, COLORREF color)
{
    settextcolor(RGB(45, 45, 45));
    outtextxy(x+1, y+1, str);
    settextcolor(color);
    outtextxy(x, y, str);
}
