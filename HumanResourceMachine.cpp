#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int button_width = 100;
const int button_height = 100;

const int window_width = 1280;//窗口长宽
const int window_height = 720;

const int block_width = 40;
const int block_height = 40;

const int block_move_speed = 10;

const int INF = 0x3f3f3f3f;

bool is_game_started = false;
bool is_game_quited = false;
enum class GameStage
{
	Menu = 0,
	LevelSelect,
	Game
};
GameStage game_stage = GameStage :: Menu;
IMAGE img;
int level_value = 0;
int level_number;
std::ifstream fin;
std::ofstream fout;

IMAGE img_menu_background;
IMAGE img_game_background;

IMAGE img_block;

IMAGE img_btn_default;
IMAGE img_btn_hovered;
IMAGE img_btn_pushed;

void init_select_level();
void load_resources()
{
	loadimage(&img_menu_background,_T("images/menu_background.png"), 1280, 720, true);
	loadimage(&img_game_background, _T("images/game_background.png"), 1280, 720, true);
	loadimage(&img_block, _T("images/block.png"), block_width, block_height, true);
	loadimage(&img_btn_default, _T("images/btn_default.png"), button_width, button_height, true);
	loadimage(&img_btn_hovered, _T("images/btn_hovered.png"), button_width, button_height, true);
	loadimage(&img_btn_pushed, _T("images/btn_pushed.png"), button_width, button_height, true);
	init_select_level();
}

void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();			// Get the width of the image
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
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
void init_game();
class Block
{
	public:
		Block(RECT pos, int color, LPCTSTR path_block)
		{
			position = pos;
			loadimage(&img, path_block);
		}
		~Block() = default;
		void draw(int color)
		{
			// setlinecolor(color);
			// setfillcolor(color);
			putimage_alpha(position.left, position.top, &img_block);
			settextcolor(color);//设置字体颜色
			settextstyle(20, 0, _T("monospace"));//设置字体
			//outtextxy(position.left+10, position.top+40, str);//输出文字
			// drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
			drawtext(_T("123978"), &position, DT_CENTER);
		}
		void move()
		{
			
		}
	private:
		RECT position;
		int value;
		IMAGE img;
};
class Button
{
	public:
		Button(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed)
		{
			position = pos;
			loadimage(&btn_default, path_btn_default);
			loadimage(&btn_hovered, path_btn_hovered);
			loadimage(&btn_pushed, path_btn_pushed);
		}
		~Button() = default;
		void draw(LPCTSTR str)
		{
			switch (stage)
			{
				case Stage::Default:
					putimage(position.left, position.top, &img_btn_default);
					break;
				case Stage::Hovered:
					putimage(position.left, position.top, &img_btn_hovered);
					break;
				case Stage::Pushed:
					putimage(position.left, position.top, &img_btn_pushed);
					break;
			}

			settextstyle(20, 0, _T("monospace"));//设置字体
			//outtextxy(position.left+10, position.top+40, str);//输出文字
			drawtext(str, &position, DT_CENTER);
		}
		virtual void ProcessMessage(ExMessage msg)
		{
			switch (msg.message)
			{
				case WM_MOUSEMOVE:
					if (stage == Stage::Default && CheckCursorInButton(msg.x, msg.y))
						stage = Stage::Hovered;
					else if (stage == Stage::Hovered && !CheckCursorInButton(msg.x, msg.y))
						stage = Stage::Default;
					break;
				case WM_LBUTTONDOWN:
					if (stage == Stage::Hovered)
						stage = Stage::Pushed;
					break;
				case WM_LBUTTONUP:
					if (stage == Stage::Pushed)
						OnClick();
					break;
				default:
					break;
			}
		}
	protected:
		virtual void OnClick() = 0;//在子类按钮按下时重写逻辑
		enum class Stage
		{
			Default = 0,//默认
			Hovered,//光标
			Pushed,//按下
		};
		Stage stage = Stage::Default;
	private:
		RECT position;
		IMAGE btn_default;
		IMAGE btn_hovered;
		IMAGE btn_pushed;
		bool CheckCursorInButton(int x, int y)//判断光标是否在按钮上
		{
			return position.left <= x && x <= position.right && position.top <= y && y <= position.bottom;
		}
};
class StartButton : public Button
{
	public:
		StartButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
		{
			
		}
		~StartButton() = default;
	protected:
		void OnClick() override
		{
			is_game_started = true;
			//init_game();//记得删
			game_stage = GameStage::LevelSelect;
		}
};
class QuitButton : public Button
{
	public:
		QuitButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed)
		{
			
		}
		~QuitButton() = default;
	protected:
		void OnClick() override
		{
			is_game_quited = true;
		}
};
class LevelSelectButton : public Button
{
	public:
		LevelSelectButton(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed, int val) : Button(pos, path_btn_default, path_btn_hovered, path_btn_pushed),value(val){ }
		~LevelSelectButton() = default;
	protected:
		void OnClick() override
		{
			game_stage = GameStage::Game;
			level_value = value;
			init_game();
		}
	private:
		int value;
};
std::vector<LevelSelectButton> level_select_btn_list;

class Slider
{
	public:
		Slider(RECT pos, LPCTSTR path_btn_default, LPCTSTR path_btn_hovered, LPCTSTR path_btn_pushed)
		{
			position = pos;
			loadimage(&btn_default, path_btn_default);
			loadimage(&btn_hovered, path_btn_hovered);
			loadimage(&btn_pushed, path_btn_pushed);
		}
		~Slider() = default;
		void draw(LPCTSTR str)
		{
			switch (stage)
			{
				case Stage::Default:
					putimage(position.left, position.top, &img_btn_default);
					break;
				case Stage::Hovered:
					putimage(position.left, position.top, &img_btn_hovered);
					break;
				case Stage::Pushed:
					putimage(position.left, position.top, &img_btn_pushed);
					break;
			}

			settextstyle(20, 0, _T("monospace"));//设置字体
			//outtextxy(position.left+10, position.top+40, str);//输出文字
			drawtext(str, &position, DT_CENTER);
		}
		virtual void ProcessMessage(ExMessage msg)
		{
			switch (msg.message)
			{
				case WM_MOUSEMOVE:
					if (stage == Stage::Default && CheckCursorInSlider(msg.x, msg.y))
						stage = Stage::Hovered;
					else if (stage == Stage::Hovered && !CheckCursorInSlider(msg.x, msg.y))
						stage = Stage::Default;
					break;
				case WM_LBUTTONDOWN:
					if (stage == Stage::Hovered)
						stage = Stage::Pushed;
					break;
				case WM_LBUTTONUP:
					if (stage == Stage::Pushed)
						OnClick();
					break;
				default:
					break;
			}
		}
	protected:
		virtual void OnClick() = 0;//在子类按钮按下时重写逻辑
		enum class Stage
		{
			Default = 0,//默认
			Hovered,//光标
			Pushed,//按下
		};
		Stage stage = Stage::Default;
	private:
		RECT position;
		IMAGE btn_default;
		IMAGE btn_hovered;
		IMAGE btn_pushed;
		bool CheckCursorInSlider(int x, int y)
		{
			return position.left <= x && x <= position.right && position.top <= y && y <= position.bottom;
		}
};

class Level{
	public:
		Level(LPCTSTR path)
		{
			fin.open(path);

			if (!fin.is_open()) std::cerr << "File not found!" << std::endl;
			if (fin.eof()) std::cerr << "File reach the End!" << std::endl;
			size_t tmp;
			fin >> input_size;
			std::cout << "path is " << path << std::endl;
			std::cout << "input_size=" << input_size << std::endl;
			for (size_t i=1; i<=input_size; ++i) 
			{
				fin >> tmp;
				this->std_input.push_back(tmp);
			}
			fin >> output_size;
			std::cout << "output_size=" << output_size << std::endl;
			for (size_t i=1; i<=output_size; ++i) 
			{
				fin >> tmp;
				this->std_output.push_back(tmp);
			}
			fin >> tmp;
			this->available_space=tmp;
			fin >> is_useful;
			fin.close();
			fin.clear();
			fin.seekg(0, std::ios::beg);
		}
		~Level() = default;
	protected:
		int is_useful;
		int available_space;
		int input_size, output_size;
		std::vector<int> std_input,std_output;
};
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
		std::cout << "i=" << i << std::endl;
		std::string path = "level_info/level_" + std::to_string(i) + ".bin";
		level_list.push_back(Level(_T(path.c_str())));
		level_select_btn_list.push_back(LevelSelectButton({(window_width-button_width)/2+ i*200 - mid*200, window_height/2+100, (window_width-button_width)/2+ i*200 - mid*200 + button_width, window_height/2+100+button_height}, _T("images/btn_default.png"), _T("images/btn_hovered.png"), _T("images/btn_pushed.png"), i));
	}
	
}
std::vector<Block> block_list;
void init_game()
{
	std:: cout << "game_id is "  << level_value << std::endl;
	int cur_block_top = 400, cur_block_left = 20;
	for (int i = 0; i < 10; i++)
	{
		RECT pos = {cur_block_left, cur_block_top, cur_block_left + block_width, cur_block_top + block_height};
		block_list.push_back(Block(pos, 0, _T("images/block.png")));
		cur_block_top += block_height + 10;
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
				menu_btn_start.draw(_T("Start"));
				menu_btn_quit.draw(_T("Quit"));
				break;
			case GameStage::LevelSelect:
				putimage_alpha(0, 0, &img_menu_background);
				for (int i=0; i<level_number; ++i)
				{
					level_select_btn_list[i].draw(_T(std::to_string(i+1).c_str()));
				}
				menu_btn_quit.draw(_T("Quit"));
				break;
			case GameStage::Game:
				putimage_alpha(0, 0, &img_game_background);
				menu_btn_quit.draw(_T("Quit"));
				for (Block block : block_list) block.draw(RED);
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
	return 0;
}