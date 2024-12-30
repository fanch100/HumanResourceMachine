#include "main.hpp"

const int button_width = 100;
const int button_height = 100;

const int window_width = 1280;//窗口长宽
const int window_height = 720;

const int block_width = 40;
const int block_height = 40;

const int player_width = 40;
const int player_height = 40;

const int slider_width = 60;
const int slider_height = 30;

const int space_width = 50;
const int space_height = 50;

const int move_speed = 10;

const int INF = 0x3f3f3f3f;
const double eps = 1e-6;

bool is_game_started = false;
bool is_game_quited = false;

IMAGE img;
int level_value = 0;
Level* cur_level = nullptr;
int level_number;
std::ifstream fin;
std::ofstream fout;

IMAGE img_menu_background;
IMAGE img_select_level_background;
IMAGE img_game_background;

IMAGE img_block;
IMAGE img_player;

IMAGE img_btn_default;
IMAGE img_btn_hovered;
IMAGE img_btn_pushed;

Scene menu_scene;
Scene level_select_scene;
Scene game_scene;

void init_select_level();
void load_resources()
{
	loadimage(&img_menu_background,_T("images/menu_background.png"), 1280, 720, true);
	loadimage(&img_select_level_background, _T("images/img_select_level_background.jpg"), 1280, 720, true);
	loadimage(&img_game_background, _T("images/game_background.png"), 1280, 720, true);
	loadimage(&img_block, _T("images/block.png"), block_width, block_height, true);
	loadimage(&img_player, _T("images/player.png"), player_width, player_height, true);
	loadimage(&img_btn_default, _T("images/btn_default.png"), button_width, button_height, true);
	loadimage(&img_btn_hovered, _T("images/btn_hovered.png"), button_width, button_height, true);
	loadimage(&img_btn_pushed, _T("images/btn_pushed.png"), button_width, button_height, true);
	init_select_level();
}

// class Animation
// {
// public:
// 	Animation(LPCSTR path, int num, int interval)
// 	{
// 		interver_ms = interval;

// 		TCHAR path_file[256];
// 		for (int i = 0; i < num; i++)
// 		{
// 			sprintf(path_file, "%s%d.png", path, i);
// 			images.push_back(path_file);
// 		}
// 	}
// private:
// }

struct Point
{
	int x, y;
};
std::vector<LevelSelectButton> level_select_btn_list;


// std::vector<Slider*> slider_list;

struct Operation
{
	int type, value;
};
std::vector<Operation> operation_list;


std::vector<Level> level_list;
void init_select_level()
{
	fin.open("level_info/level_number.bin");
	fin >> level_number;
	fin.close();
	fin.clear();
	fin.seekg(0, std::ios::beg);
	int mid = (level_number+1)/2;
	for (int i = 1; i <= level_number; i++)
	{
		std::string path = "level_info/level_" + std::to_string(i) + ".bin";
		level_list.push_back(Level(_T(path.c_str())));
		level_select_btn_list.push_back(LevelSelectButton({(window_width-button_width)/2+ i*200 - mid*200, window_height/2+100, (window_width-button_width)/2+ i*200 - mid*200 + button_width, window_height/2+100+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"), i));
	}
}


int main()
{
	initgraph(1280, 720);
	ExMessage msg;
	load_resources();

	BeginBatchDraw();
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd,"Hello");
	
	
	for (int i = 0; i < 2; i++)
	{
		std::string path = "images/pixil-frame-" + std::to_string(1) + ".png";
		loadimage(&img, _T(path.c_str()));
		putimage(0 + i*100,0 + i*100,&img);
	}

	putimage_alpha(0, 0, &img_menu_background);
	
	loadimage(&img,_T("images/btn_default.png"));
	putimage_alpha(0, 0, &img_btn_default);
	

	setbkmode(TRANSPARENT);//显示透明文字
	settextcolor(YELLOW);//设置字体颜色为蓝色
	settextstyle(20, 0, _T("monospace"));//设置字体
	outtextxy(50, 30, _T("HumanResourceMachine"));//输出文字


	StartButton menu_btn_start = StartButton({window_width/2-200, window_height/2+100, window_width/2-200+button_width, window_height/2+100+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
	// QuitButton menu_btn_quit = QuitButton({window_width/2+200-button_width, window_height/2+100, window_width/2+200, window_height/2+100+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
	QuitButton menu_btn_quit = QuitButton({window_width-button_width, window_height-button_height, window_width, window_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
	while (true)
	{
		DWORD start_time = GetTickCount();
		//信息处理
		while(peekmessage(&msg))
		{
			switch (game_stage)
			{
				case GameStage::Menu:
					menu_btn_start.ProcessMessage(msg);
					menu_btn_quit.ProcessMessage(msg);
					break;
				case GameStage::LevelSelect:
					for (int i=0; i<level_number; ++i)
					{
						level_select_btn_list[i].ProcessMessage(msg);
					}
					menu_btn_quit.ProcessMessage(msg);
					break;
				case GameStage::Game:
					switch(msg.message)
					{
						int x, y;
						case WM_LBUTTONDOWN:
							x = msg.x, y = msg.y;
							circle(x, y, 100);
							SetWindowText(hwnd,"Hello World!");
							
							break;
						case WM_LBUTTONUP:
							x = msg.x, y = msg.y;
							circle(x+100, y+100, 100);
							// PostMessage(hwnd, WM_CLOSE, 0, 0);
							SetWindowText(hwnd,"Hello World!");
							break;
					}
					menu_btn_quit.ProcessMessage(msg);
					cur_level->ProcessMessage(msg);
					break;
			}
		}
		// 逻辑处理
		switch (game_stage)
		{
			case GameStage::Menu:
				break;
			case GameStage::LevelSelect:
				break;
			case GameStage::Game:
				
				break;
		}
		// 绘制
		switch (game_stage)
		{
			case GameStage::Menu:
				// loadimage(&img,_T("images/background_menu.png"), 1280, 720, true);
				// putimage_alpha(0, 0, &img);
				menu_btn_start.Draw(_T("Start"));
				menu_btn_quit.Draw(_T("Quit"));
				break;
			case GameStage::LevelSelect:
				putimage_alpha(0, 0, &img_select_level_background);
				for (int i=0; i<level_number; ++i)
				{
					level_select_btn_list[i].Draw(_T(std::to_string(i+1).c_str()));
				}
				menu_btn_quit.Draw(_T("Quit"));
				break;
			case GameStage::Game:
				putimage_alpha(0, 0, &img_game_background);
				menu_btn_quit.Draw(_T("Quit"));
				cur_level->Draw();
				
				break;
		}

		if (is_game_quited == true) break;
		FlushBatchDraw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;//单位为ms
		if (delta_time < 1000 / 60)//60帧每秒
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
	// Delete();
	return 0;
}