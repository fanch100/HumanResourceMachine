#include "main.hpp"

Level::Level(LPCTSTR path)
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
Level::~Level() = default;
void Level::Draw()
{
    for (Block block : block_list) block.Draw(RED);
    for (Slider &slider : slider_list) slider.Draw();
    input_box->Draw();
}
void Level::ProcessMessage(const ExMessage &msg)
{
    for (Slider &slider : slider_list) slider.ProcessMessage(msg);
    input_box->ProcessMessage(msg);
}
void Level::InitGame()
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
        this->free_space.push_back((Block*)nullptr);
    }
    //文本框初始化
    int cur_text_box_top = 600, cur_text_box_left = 900;
    input_box = new TextBox();
    input_box->Init(RECT{ cur_text_box_left, cur_text_box_top, cur_text_box_left + 100, cur_text_box_top + 100}, 100);
}
void Level::QuitGame()
{
    this->block_list.clear();
    this->slider_list.clear();
    this->user_output.clear();
    // free_space.clear();
    // cur_block = *(Block*)nullptr;
    this->nxt_input = -1;
    // if (input_box != nullptr) 
    // {
    //     delete input_box;
    //     input_box = nullptr; // 设置为 nullptr 避免重复删除
    // }
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