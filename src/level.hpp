#pragma once

#include "classes.hpp"
// #include "button.hpp"
// #include "Block.hpp"
// #include "Slider.hpp"

extern std::ifstream fin;
extern std::ofstream fout;
extern int level_value;

class Level
{
	public:
		Level(LPCTSTR path);
		~Level();
		void Draw();
		void ProcessMessage(const ExMessage &msg);
		void InitGame();
		void QuitGame();
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