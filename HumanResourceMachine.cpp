#pragma once

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
//#include "Level.hpp"

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
IMAGE img_select_level_background;
IMAGE img_game_background;

IMAGE img_block;
IMAGE img_player;

IMAGE img_btn_default;
IMAGE img_btn_hovered;
IMAGE img_btn_pushed;

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
class Block
{
	public:
		Block(RECT pos, int color, LPCTSTR path_block, int value)
		{
			position = pos;
			this->value = value;
			loadimage(&img, path_block);
		}
		~Block() = default;
		void Draw(int color)
		{
			// setlinecolor(color);
			// setfillcolor(color);
			putimage_alpha(position.left, position.top, &img_block);
			settextcolor(color);//设置字体颜色
			settextstyle(20, 0, _T("monospace"));//设置字体
			//outtextxy(position.left+10, position.top+40, str);//输出文字
			// drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
			drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
		}
		void Move(int x, int y)
		{
			int delta_x = x - position.left;
			int delta_y = y - position.top;
			double dis = std::sqrt(delta_x * delta_x + delta_y * delta_y);
			if (fabs(dis) > eps)
			{
				int final_x = (int)(delta_x * move_speed / dis) + position.left;
				int final_y = (int)(delta_y * move_speed / dis) + position.top;
				position = {final_x, final_y, final_x + block_width, final_y + block_height};
			}
		}
		void SetValue(int value)
		{
			this->value = value;
		}
		int GetValue()
		{
			return value;
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
		virtual void ProcessMessage(const ExMessage &msg)
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
			is_game_started = true;
			level_value = value;
		}
	private:
		int value;
};
std::vector<LevelSelectButton> level_select_btn_list;

class Slider
{
	public:
		Slider(RECT pos, LPCTSTR str)
		{
			position = pos;
			cur_x = pos.left;
			cur_y = pos.top;
			stage = Stage::Default;
			this->str = str;
		}
		~Slider() = default;
		void Draw()
		{
			setfillcolor(RGB(45, 45, 45));
			solidrectangle(position.left+3, position.top+3, position.right+3, position.bottom+3);
			setfillcolor(BLUE);
			solidrectangle(position.left, position.top, position.right, position.bottom);
			settextstyle(20, 0, _T("monospace"));//设置字体
			//outtextxy(position.left+10, position.top+40, str);//输出文字
			drawtext(str, &position, DT_CENTER);
		}
		void ProcessMessage(const ExMessage &msg)
		{
			// switch (msg.message)
			// {
			// 	case WM_MOUSEMOVE:
			// 		if (stage == Stage::Default && CheckCursorInSlider(msg.x, msg.y))
			// 			stage = Stage::Hovered;
			// 		else if (stage == Stage::Hovered && !CheckCursorInSlider(msg.x, msg.y))
			// 			stage = Stage::Pushed;
			// 		// else if (stage == Stage::Default)
			// 		// {
			// 		// 	int delta_x = msg.x - cur_x;
			// 		// 	int delta_y = msg.y - cur_y;
			// 		// 	position = {position.left + delta_x, position.top + delta_y, position.right + delta_x, position.bottom + delta_y};
			// 		// 	std::cout << "msg:x: " << msg.x << " y: " << msg.y << std::endl;
			// 		// 	std::cout << "cur:x: " << cur_x << " y: " << cur_y << std::endl;
			// 		// 	std::cout << "delta:x: " << delta_x << " y: " << delta_y << std::endl;
			// 		// 	cur_x = msg.x;
			// 		// 	cur_y = msg.y;
			// 		// }
			// 		break;
			// 	case WM_LBUTTONDOWN:
			// 		if (stage == Stage::Hovered)
			// 		{
			// 			stage = Stage::Pushed;	
			// 			cur_x = msg.x;
			// 			cur_y = msg.y;
			// 		}
			// 		break;
			// 	// case WM_LBUTTONUP:
			// 	// 	if (stage == Stage::Pushed)
			// 	// 		OnClick();
			// 	// 	break;
			// 	default:
			// 		break;
			// }
			switch (msg.message)
			{
				case WM_MOUSEMOVE:
					if (stage == Stage::Pushed)
					{
						int delta_x = msg.x - cur_x;
						int delta_y = msg.y - cur_y;
						position = {position.left + delta_x, position.top + delta_y, position.right + delta_x, position.bottom + delta_y};
						cur_x = msg.x;
						cur_y = msg.y;
						// 确保滑块不会超出窗口边界
						if (position.left < 0) position.left = 0;
						if (position.top < 0) position.top = 0;
						if (position.right > window_width) position.right = window_width;
						if (position.bottom > window_height) position.bottom = window_height;
						position.right = position.left + slider_width;
						position.bottom = position.top + slider_height;
					}
					else if (stage == Stage::Default && CheckCursorInSlider(msg.x, msg.y))
						stage = Stage::Hovered;
					else if (stage == Stage::Hovered && !CheckCursorInSlider(msg.x, msg.y))
						stage = Stage::Default;
					break;
				case WM_LBUTTONDOWN:
					if (stage == Stage::Hovered)
					{
						stage = Stage::Pushed;
						cur_x = msg.x;
						cur_y = msg.y;
					}
					break;
				case WM_LBUTTONUP:
					if (stage == Stage::Pushed)
						stage = Stage::Hovered;
					break;
				default:
					break;
			}
		}
	protected:
		//virtual void OnClick() = 0;//在子类按钮按下时重写逻辑
		void OnClick(){return;};
		enum class Stage
		{
			Default = 0,//默认
			Hovered,//光标
			Pushed,//按下
		};
		enum class Type
		{
			Inbox = 0,
			Outbox,
			CopyFrom,
			CopyTo,
			Add,
			Sub,
			Jump,
			JumpIfZero
		};
		int type;
		Stage stage;
	private:
		LPCTSTR str;
		RECT position;
		int cur_x, cur_y;
		bool CheckCursorInSlider(int x, int y)
		{
			return position.left <= x && x <= position.right && position.top <= y && y <= position.bottom;
		}
};


// std::vector<Slider*> slider_list;

struct Operation
{
	int type, value;
};
std::vector<Operation> operation_list;
class Player
{
	public:
		Player(RECT pos, int color, LPCTSTR path_player, int value)
		{
			position = pos;
			this->value = value;
			loadimage(&img, path_player);
		}
		~Player() = default;
		void Draw(int color)
		{
			// setlinecolor(color);
			// setfillcolor(color);
			putimage_alpha(position.left, position.top, &img_player);
			settextcolor(color);//设置字体颜色
			settextstyle(20, 0, _T("monospace"));//设置字体
			//outtextxy(position.left+10, position.top+40, str);//输出文字
			// drawtext(_T((std::to_string(1)).c_str()), &position, DT_CENTER);
			drawtext(_T(std::to_string(value).c_str()), &position, DT_CENTER);
		}
		void Move(int x, int y)
		{
			int delta_x = x - position.left;
			int delta_y = y - position.top;
			double dis = std::sqrt(delta_x * delta_x + delta_y * delta_y);
			if (fabs(dis) > eps)
			{
				int final_x = (int)(delta_x * move_speed / dis) + position.left;
				int final_y = (int)(delta_y * move_speed / dis) + position.top;
				position = {final_x, final_y, final_x + block_width, final_y + block_height};
			}
		}
		void SetValue(int value)
		{
			this->value = value;
		}
		int GetValue()
		{
			return value;
		}
	private:
		RECT position;
		int value;
		IMAGE img;
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
		void Draw()
		{
			for (Block block : block_list) block.Draw(RED);
			for (Slider &slider : slider_list) slider.Draw();
		}
		void ProcessMessage(const ExMessage &msg)
		{
			for (Slider &slider : slider_list) slider.ProcessMessage(msg);
		}
		void init_game()
		{
			//箱子初始化
			
			std:: cout << "game_id is "  << level_value << std::endl;
			int cur_block_top = 400, cur_block_left = 20;
			for (int i : std_input)
			{
				RECT pos = {cur_block_left, cur_block_top, cur_block_left + block_width, cur_block_top + block_height};
				block_list.push_back(Block(pos, 0, _T("images/block.png"), i));
				cur_block_top += block_height + 10;
			}
			//操作滑块初始化
			
			int cur_slider_top = 100, cur_slider_left = 900;
			for (int i = 0; i < 8; i++)
			{
				RECT pos = {cur_slider_left, cur_slider_top, cur_slider_left + slider_width, cur_slider_top + slider_height};
				
				//slider_list.push_back(Slider(pos,_T(std::to_string(i).c_str())));
				slider_list.push_back(Slider(pos,_T("Block")));
				//Slider* slider = new Slider(pos,_T(String[i].c_str()));
				//slider_list.push_back(slider);
				cur_slider_top += slider_height + 10;
			}
			// puts("YES");
			//空地初始化
			int x = available_space;
			for (int i = 0; i < x; ++i)
			{
				free_space.push_back((Block*)nullptr);
			}
		}
		void quit_game()
		{
			block_list.clear();
			slider_list.clear();
			user_output.clear();
			// free_space.clear();
			// cur_block = *(Block*)nullptr;
			nxt_input = -1;
		}
	// 	int inbox(int cur_step){
	// 		++nxt_input;
	// //        printf("nxt_input=%d std.size=%d\n",nxt_input,std_input.size());
	// 		if (nxt_input>=std_input.size()) return input_size + 1;
	// 		cur_block = std_input[nxt_input];
	// 		return cur_step + 1;
	// 	}
	// 	int outbox(int cur_step){
	// 		if (cur_block==INF) return -1;
	// 		user_output.push_back(cur_block);
	// 		cur_block = INF;
	// 		return cur_step+1;
	// 	}
	// 	int copyfrom(int cur_step,int x){
	// 		if (x>available_space || block[x]==INF) return -1;
	// 		cur_block = block[x];
	// 		return cur_step+1;
	// 	}
	// 	int copyto(int cur_step,int x){
	// 		if (x>available_space || cur_block==INF) return -1;
	// 		block[x] = cur_block;
	// 		return cur_step+1;
	// 	}
	// 	int add(int cur_step,int x){
	// 		if (x>available_space || cur_block==INF || block[x]==INF) return -1;
	// 		cur_block += block[x];
	// 		return cur_step+1;
	// 	}
	// 	int sub(int cur_step,int x){
	// 		if (x>available_space || cur_block==INF || block[x]==INF) return -1;
	// 		cur_block -= block[x];
	// 		return cur_step+1;
	// 	}
	// 	int jump(int x){
	// 		if (x>n) return -1;
	// 		return x;
	// 	}
	// 	int jumpifzero(int cur_step,int x){
	// 		if (x>n || cur_block==INF) return -1;
	// 		return (!cur_block)?x:cur_step+1;
	// 	}
	// 	int getnxt(int cur_step){
	// 		int op=a[cur_step].op, x=a[cur_step].x;
	// 		if (!is_useful[op]) return -1;
	// 		if (op==1) return inbox(cur_step);
	// 		else if (op==2) return outbox(cur_step);
	// 		else if (op==3) return copyfrom(cur_step,x);
	// 		else if (op==4) return copyto(cur_step,x);
	// 		else if (op==5) return add(cur_step,x);
	// 		else if (op==6) return sub(cur_step,x);
	// 		else if (op==7) return jump(x);
	// 		else if (op==8) return jumpifzero(cur_step,x);
	// 		return -1;
	// 	}
	private:
		int is_useful;
		int available_space;
		int input_size, output_size;
		std::vector<int> std_input,std_output;
		std::vector<Block> block_list;
		std::vector<Slider> slider_list;
		std::vector<int> user_output;
		std::vector<Block*> free_space; 
		Block* cur_block = (Block*)nullptr;
    	int nxt_input=-1;
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
					level_list[level_value-1].ProcessMessage(msg);
					break;
			}
		}
		if (is_game_started == true)
		{
			level_list[level_value-1].init_game();
			puts("INIT");
			is_game_started = false;
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
				putimage_alpha(0, 0, &img_select_level_background);
				for (int i=0; i<level_number; ++i)
				{
					level_select_btn_list[i].draw(_T(std::to_string(i+1).c_str()));
				}
				menu_btn_quit.draw(_T("Quit"));
				break;
			case GameStage::Game:
				putimage_alpha(0, 0, &img_game_background);
				menu_btn_quit.draw(_T("Quit"));
				level_list[level_value-1].Draw();
				
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