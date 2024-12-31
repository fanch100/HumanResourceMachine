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

    // player = new Player(RECT{20, 20, 20 + player_width, 20 + player_height});
}
// Level& Level::operator= (const Level& level)
// {
//     this->input_size = level.input_size;
//     this->output_size = level.output_size;
//     this->is_useful = level.is_useful;
//     this->std_input = level.std_input;
//     this->std_output = level.std_output;
//     this->available_space = level.available_space;
//     if (level.player != nullptr)
//     {
//         this->player = new Player(*level.player);
//     }
//     else this->player = nullptr;
//     this->cur_block = level.cur_block;
//     this->block_list = level.block_list;
//     this->slider_list = level.slider_list;
//     this->user_output = level.user_output;
//     this->space_list = level.space_list;
//     this->nxt_input = level.nxt_input;
//     this->is_playing = level.is_playing
//     return *this;
// }

// Level::Level(const Level& level)
// {
//     *this = level;
// }
Level::~Level()
{
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }
}
void Level::Draw()
{
    for (Block block : block_list) block.Draw(RED);
    for (Slider &slider : slider_list) slider.Draw();
    for (Space &space : space_list) space.Draw(RED);
    player->Draw();
}
void Level::ProcessMessage(const ExMessage &msg)
{
    for (Slider &slider : slider_list) slider.ProcessMessage(msg);
    //for (Space &space : space_list) space.ProcessMessage(msg);//没有写
}
void Level::Update()
{
    bool is_finish = player->Move(500, 500);
    std:: cout << "is_finish is " << is_finish << std::endl;
}
void Level::InitGame()
{
    //箱子初始化
    std:: cout << "game_id is "  << level_value << std::endl;
    int cur_block_top = 350, cur_block_left = 20;
    for (int i : std_input)
    {
        RECT pos = {cur_block_left, cur_block_top, cur_block_left + block_width, cur_block_top + block_height};
        block_list.push_back(Block(pos, 0, i));
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
    
    int space_top = 400, space_left = 400;
    int space_row = (int)std::sqrt(available_space);
    int space_column = (available_space == 0)? 0 : (available_space-1) / space_row +1;
    std :: cout << "space_row: " << space_row  << std::endl;
    std :: cout << "space_column: " << space_column << std::endl;
    std :: cout << "available_space: " << available_space << std::endl;
    space_top -= space_row * space_height / 2;
    space_left -= space_column * space_width / 2;
    for (int i = 0, k = 0; i < space_row && k < available_space; ++i)
    {
        for (int j = 0; j < space_column && k < available_space; ++j, ++k)
        {
            RECT pos = {space_left+ j*space_width, space_top + i*space_height, space_left + (j+1)*space_width, space_top + (i+1)*space_height};
            std :: cout << "pos.right = " << pos.right << std::endl;
            std :: cout << "pos.bottom = " << pos.bottom << std::endl;
            space_list.push_back(Space(pos, 0, k));
        }
    }
    //文本框初始化
    
    //Player初始化
    player = new Player(RECT{20, 20, 20 + player_width, 20 + player_height});
}
void Level::QuitGame()
{
    this->block_list.clear();
    this->slider_list.clear();
    this->user_output.clear();
    // free_space.clear();
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }
    if (cur_block != nullptr)
    {
        cur_block = (Block*)nullptr;
    }
    
    this->nxt_input = -1;
    
    std :: cout << "Level::QuitGame()" << std :: endl;
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
int GetNextStep(int cur_step){
    // int op=a[cur_step].op, x=a[cur_step].x;
    // if (!is_useful[op]) return -1;
    // if (op==1) return inbox(cur_step);
    // else if (op==2) return outbox(cur_step);
    // else if (op==3) return copyfrom(cur_step,x);
    // else if (op==4) return copyto(cur_step,x);
    // else if (op==5) return add(cur_step,x);
    // else if (op==6) return sub(cur_step,x);
    // else if (op==7) return jump(x);
    // else if (op==8) return jumpifzero(cur_step,x);
    return -1;
}
bool chk(){
    // if (user_output.size()!=std_output.size()) return 0;
    // else {
    //     for (int i=0;i<user_output.size();++i){
    //         if (user_output[i]!=std_output[i]) return 0;
    //     }
    // }
    return 1;
}
void Play(){
    int cur_step = 1;
    int operation_size = game_scene.operation_list.size(); 
    while(cur_step <= operation_size){
//            printf("cur_step=%d\n",cur_step);
        int nxt_step=GetNextStep(cur_step);
//            printf("nxt_step=%d\n",nxt_step);
        if (nxt_step==-1){
            printf("Error on instruction %d\n",cur_step);
            return;
        }
        cur_step=nxt_step;
    }
//        for (int i=0;i<std_output.size();++i) printf("i=%d out=%d\n",i,std_output[i]);
//        for (int i=0;i<user_output.size();++i) printf("i=%d out=%d\n",i,user_output[i]);
    if (chk()) puts("Success");
    else puts("Fail");
}
void Update()
{
    
}