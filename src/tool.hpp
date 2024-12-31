#pragma once

#include "classes.hpp"

void putimage_alpha(int x, int y, IMAGE* img);

void outtextxy_shaded(int x, int y, LPCTSTR str, COLORREF color);

#include <string>

std::string TCHARToString(const TCHAR* tcharString);