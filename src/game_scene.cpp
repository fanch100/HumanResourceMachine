#include "main.hpp"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;
void GameScene::Init()
{
    cur_level->InitGame();
    int cur_text_box_top = 400, cur_text_box_left = 900;
    input_box = new TextBox();
    input_box->Init(RECT{ cur_text_box_left, cur_text_box_top, cur_text_box_left + 100, cur_text_box_top + 100}, 100);
    std::cout << "Game Scene Init" << std::endl;
}
void GameScene::Draw()
{
    putimage_alpha(0, 0, &img_game_background);
    cur_level->Draw();
    if (input_box != nullptr)
    {
        input_box->Draw();
    }
    game_play_btn.Draw(_T("Play"));
    game_file_input_btn.Draw(_T("Input File"));
    game_btn_quit.Draw(_T("Quit"));
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
    
    cur_level->ProcessMessage(msg);
    if (input_box != nullptr)
    {
        input_box->ProcessMessage(msg);
    }
    game_play_btn.ProcessMessage(msg);
    game_file_input_btn.ProcessMessage(msg);
    game_btn_quit.ProcessMessage(msg);//quit最好设置在下面
    std::cout << "Game Scene ProcessMessage" << std::endl;
}
void GameScene::Quit()
{
    cur_level->QuitGame();
    if (input_box != nullptr) 
    {
        delete input_box;
        input_box = nullptr;
    }
    std::cout << "Game Scene Quit" << std::endl;
}