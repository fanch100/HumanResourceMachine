#include "classes.hpp"
#include "stage.hpp"
#include "stage_manager.hpp"
#include "menu_stage.hpp"
#include "select_level_stage.hpp"
#include "game_stage.hpp"
#include "tool.hpp"

const int button_width = 100;
const int button_height = 100;

const int window_width = 1280;//窗口长宽
const int window_height = 720;

const int block_width = 50;
const int block_height = 50;

const int block_move_speed = 10;

const int FPS = 1;

int level_value;

namespace Global

{
	bool is_game_started = false;
	bool is_game_quited = false;
	enum class Stage
	{
		Menu = 0,
		LevelSelect,
		Game
	};
	Stage stage = Stage :: Menu;
	IMAGE img;
	int level_value = 0;
}

//载入游戏图片
IMAGE menu_background;
IMAGE game_background;

IMAGE block;

IMAGE btn_default;
IMAGE btn_hovered;
IMAGE btn_pushed;

void load_resources()
{
	loadimage(&menu_background,_T("images/menu_background.png"), 1280, 720, true);
	loadimage(&game_background, _T("images/game_background.png"), 1280, 720, true);
	loadimage(&block, _T("images/block.png"), block_width, block_height, true);
	loadimage(&btn_default, _T("images/btn_default.png"), button_width, button_height, true);
	loadimage(&btn_hovered, _T("images/btn_hovered.png"), button_width, button_height, true);
	loadimage(&btn_pushed, _T("images/btn_pushed.png"), button_width, button_height, true);
}

Stage* menu_scene = nullptr;
Stage* select_level_scene = nullptr;
Stage* game_scene = nullptr;

StageManager stage_manager;

int main()
{
    LPCTSTR title = _T("Hello World!");

	initgraph(1280, 720);
    load_resources();
	ExMessage msg;
	
    menu_scene = new MenuStage();
    select_level_scene = new SelectLevelStage();
    game_scene = new GameStage();

    stage_manager.SetStage(menu_scene);

	BeginBatchDraw();
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd,"Hello");

	// StartButton btn_start = StartButton({200, 200, 200+button_width, 200+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
	// QuitButton btn_quit = QuitButton({window_width - button_width, window_height - button_height, window_width, window_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
	while (true)
	{
		DWORD start_time = GetTickCount();
		//信息处理
		while(peekmessage(&msg))
		{
			stage_manager.ProcessMessage(msg);
			
			// switch (Global::stage)
			// {
			// 	case Global::Stage::Menu:
			// 		btn_start.ProcessMessage(msg);
			// 		btn_quit.ProcessMessage(msg);
			// 		break;
			// 	case Global::Stage::LevelSelect:
			// 		btn_quit.ProcessMessage(msg);
			// 		break;
			// 	case Global::Stage::Game:
			// 		switch(msg.message)
			// 		{
			// 			int x, y;
			// 			case WM_LBUTTONDOWN:
			// 				x = msg.x, y = msg.y;
			// 				circle(x, y, 100);
			// 				SetWindowText(hwnd,"Hello World!");
							
			// 				break;
			// 			case WM_LBUTTONUP:
			// 				x = msg.x, y = msg.y;
			// 				circle(x+100, y+100, 100);
			// 				// PostMessage(hwnd, WM_CLOSE, 0, 0);
			// 				SetWindowText(hwnd,"Hello World!");
			// 				break;
			// 		}
			// 		btn_quit.ProcessMessage(msg);
			// 		break;
			// }
		}
		// 逻辑处理
		// switch (Global::stage)
		// {
		// 	case Global::Stage::Menu:
		// 		break;
		// 	case Global::Stage::LevelSelect:
		// 		break;
		// 	case Global::Stage::Game:
				
		// 		break;
		// }
        stage_manager.Update();
		// 绘制
		// switch (Global::stage)
		// {
		// 	case Global::Stage::Menu:
		// 		// loadimage(&Global::img,_T("images/background_menu.png"), 1280, 720, true);
		// 		// putimage_alpha(0, 0, &Global::img);
		// 		btn_start.draw(_T("Start"));
		// 		btn_quit.draw(_T("Quit"));
		// 		break;
		// 	case Global::Stage::LevelSelect:
		// 		loadimage(&Global::img,_T("images/background_menu.png"), 1280, 720, true);
		// 		putimage_alpha(0, 0, &Global::img);
		// 		btn_quit.draw(_T("Quit"));
		// 		break;
		// 	case Global::Stage::Game:
		// 		loadimage(&Global::img,_T("images/background_game.png"), 1280, 720, true);
		// 		putimage_alpha(0, 0, &Global::img);
		// 		btn_quit.draw(_T("Quit"));
		// 		for (Block block : block_list) block.draw(RED);
		// 		break;
		// }
        stage_manager.Draw();
		// if (Global::is_game_quited == true) break;
		FlushBatchDraw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time ;//单位为ms
		if (delta_time < 1000 / FPS)//60帧每秒
		{
			Sleep(1000 / FPS - delta_time);
		}
	}
	EndBatchDraw();
	return 0;
}