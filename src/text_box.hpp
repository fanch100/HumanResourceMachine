#pragma once

#include "classes.hpp"
#include "tool.hpp"

class TextBox
{                             // 文本框最大内容长度
public:
    TextBox();
    void Init(RECT pos, int max);
    ~TextBox();
    TCHAR* GetText();

    bool CheckCursorInTextBox(int x, int y);
    void Draw();

    void ProcessMessage(const ExMessage &msg);
private:
    RECT position;
    TCHAR* text = NULL;                              // 控件内容
    size_t maxlen = 0;
    bool is_input = false;             // 是否输入中
};