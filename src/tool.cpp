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
    outtextxy(x+3, y+3, str);
    settextcolor(color);
    outtextxy(x, y, str);
}

#include <string>

std::string TCHARToString(const TCHAR* tcharString)
{
#ifdef _UNICODE
    // Convert wchar_t* to std::string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(tcharString);
#else
    // Convert char* to std::string
    return std::string(tcharString);
#endif
}