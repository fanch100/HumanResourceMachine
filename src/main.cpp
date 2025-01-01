#include "main.hpp"

const int button_width = 100;
const int button_height = 100;

const int window_width = 1280;//窗口长宽
const int window_height = 720;

const int block_width = 40;
const int block_height = 40;

const int player_width = 60;
const int player_height = 60;

const int slider_width = 60;
const int slider_height = 30;

const int space_width = 60;
const int space_height = 60;

const int operation_width = 200;
const int operation_height = 50;

const Point inbox_pos = {20, 300};
const Point outbox_pos = {600, 300};

const int move_speed = 5;

const int INF = 0x3f3f3f3f;
const double eps = 1e-6;

bool is_game_started = false;
bool is_game_quited = false;

GameStage game_stage = GameStage :: Menu;
IMAGE img;
int level_value = 0;
Level* cur_level = nullptr;
int level_number;
std::ifstream fin;
std::ofstream fout;

IMAGE img_menu_background;
IMAGE img_level_select_background;
IMAGE img_game_background;

IMAGE img_block;
IMAGE img_player;
IMAGE img_space;

IMAGE img_btn_default;
IMAGE img_btn_hovered;
IMAGE img_btn_pushed;

IMAGE img_game_play_btn_default;
IMAGE img_game_play_btn_hovered;
IMAGE img_game_play_btn_pushed;

SceneManager scene_manager;
MenuScene menu_scene;
LevelSelectScene level_select_scene;
GameScene game_scene;

std::unordered_map<std::string, int> operation_name_to_number;
std::unordered_map<int, std::string> operation_number_to_name;


void load_resources()
{
	loadimage(&img_menu_background,_T("images/menu_background.png"), 1280, 720, true);
	loadimage(&img_level_select_background, _T("images/img_level_select_background.jpg"), 1280, 720, true);
	loadimage(&img_game_background, _T("images/game_background.png"), 1280, 720, true);

	loadimage(&img_block, _T("images/block.png"), block_width, block_height, true);
	loadimage(&img_player, _T("images/player.png"), player_width, player_height, true);
	loadimage(&img_space, _T("images/space.png"), space_width, space_height, true);

	loadimage(&img_btn_default, _T("images/btn_default.png"), button_width, button_height, true);
	loadimage(&img_btn_hovered, _T("images/btn_hovered.png"), button_width, button_height, true);
	loadimage(&img_btn_pushed, _T("images/btn_pushed.png"), button_width, button_height, true);

    loadimage(&img_game_play_btn_default, _T("images/game_play_btn_default.png"), button_width, button_height, true);
	loadimage(&img_game_play_btn_hovered, _T("images/game_play_btn_hovered.png"), button_width, button_height, true);
	loadimage(&img_game_play_btn_pushed, _T("images/game_play_btn_pushed.png"), button_width, button_height, true);
	init_select_level();
    init_map();
}


void init_map()
{
    operation_name_to_number["inbox"] = 1;
    operation_name_to_number["outbox"] = 2;
    operation_name_to_number["copyfrom"] = 3;
    operation_name_to_number["copyto"] = 4;
    operation_name_to_number["add"] = 5;
    operation_name_to_number["sub"] = 6;
    operation_name_to_number["jump"] = 7;
    operation_name_to_number["jumpifzero"] = 8;

    operation_number_to_name[1] = "inbox";
    operation_number_to_name[2] = "outbox";
    operation_number_to_name[3] = "copyfrom";
    operation_number_to_name[4] = "copyto";
    operation_number_to_name[5] = "add";
    operation_number_to_name[6] = "sub";
    operation_number_to_name[7] = "jump";
    operation_number_to_name[8] = "jumpifzero";
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

std::vector<LevelSelectButton> level_select_btn_list;


// // std::vector<Slider*> slider_list;


// std::vector<Operation> operation_list;


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
StartButton menu_btn_start = StartButton({(window_width-button_width)/2-200, window_height/2+100, (window_width-button_width)/2-200+button_width, window_height/2+100+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
MenuQuitButton menu_btn_quit = MenuQuitButton({(window_width-button_width)/2+200, window_height/2+100, (window_width-button_width)/2+200+button_width, window_height/2+100+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
LevelSelectQuitButton level_select_btn_quit = LevelSelectQuitButton({window_width-button_width, window_height-button_height, window_width, window_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
GameQuitButton game_btn_quit = GameQuitButton({window_width-button_width, window_height-button_height, window_width, window_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"));
GamePlayButton game_play_btn = GamePlayButton({900, 600, 900 + button_width, 600 + button_height}, _T("images/game_play_btn_default.png"), _T("images/game_play_btn_hovered.png"), _T("images/game_play_btn_pushed.png"));
GameStopButton game_stop_btn = GameStopButton({900, 650, 900 + button_width, 650 + button_height}, _T("images/game_play_btn_default.png"), _T("images/game_play_btn_hovered.png"), _T("images/game_play_btn_pushed.png"));
GameFileInputButton game_file_input_btn = GameFileInputButton({1000, 600, 1000 + button_width, 600 + button_height}, _T("images/game_play_btn_default.png"), _T("images/game_play_btn_hovered.png"), _T("images/game_play_btn_pushed.png"));

int main()
{
    std::freopen("./texts/test.out","w",stdout);

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
	
	loadimage(&img,_T("images/btn_default.png"));
	putimage_alpha(0, 0, &img_btn_default);
	

	setbkmode(TRANSPARENT);//显示透明文字
	settextcolor(YELLOW);//设置字体颜色为蓝色
	settextstyle(20, 0, _T("monospace"));//设置字体
	outtextxy(50, 30, _T("HumanResourceMachine"));//输出文字
    scene_manager.SetScene(&menu_scene);

	
	while (true)
	{
		DWORD start_time = GetTickCount();
		//信息处理
		while(peekmessage(&msg))
		{
            scene_manager.ProcessMessage(msg);
		}
		// 逻辑处理
        //scene_manager.Update();
		// 绘制
        scene_manager.Draw();


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