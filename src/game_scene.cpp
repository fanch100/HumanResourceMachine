#include "main.hpp"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;
void GameScene::Init()
{
    std::cout << "Game Scene Init" << std::endl;
}
void GameScene::Draw()
{
    putimage_alpha(0, 0, &img_game_background);
    game_btn_quit.Draw(_T("Quit"));
    cur_level->Draw();
    std::cout << "Game Scene Draw" << std::endl;
}
void GameScene::Update()
{
    std::cout << "Game Scene Update" << std::endl;
}
void GameScene::ProcessMessage(const ExMessage &msg)
{
    // switch(msg.message)
    // {
    //     int x, y;
    //     case WM_LBUTTONDOWN:
    //         x = msg.x, y = msg.y;
    //         circle(x, y, 100);
    //         SetWindowText(hwnd,"Hello World!");
    //         break;
    //     case WM_LBUTTONUP:
    //         x = msg.x, y = msg.y;
    //         circle(x+100, y+100, 100);
    //         // PostMessage(hwnd, WM_CLOSE, 0, 0);
    //         SetWindowText(hwnd,"Hello World!");
    //         break;
    // }
    game_btn_quit.ProcessMessage(msg);
    cur_level->ProcessMessage(msg);
    std::cout << "Game Scene ProcessMessage" << std::endl;
}
void GameScene::Quit()
{
    std::cout << "Game Scene Quit" << std::endl;
}