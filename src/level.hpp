#pragma once

#include "classes.hpp"
// #include "button.hpp"
// #include "Block.hpp"
// #include "Slider.hpp"

extern std::ifstream fin;
extern std::ofstream fout;
extern int level_value;
extern int operation_size;

extern GameScene game_scene;

extern const Point inbox_pos;
extern const Point outbox_pos;

extern std::unordered_map<std::string, int> operation_name_to_number;
extern std::unordered_map<int, std::string> operation_number_to_name;

class Level
{
	public:
		Level(LPCTSTR path, LPCTSTR path_state);
		// Level& operator= (const Level& level);
		// Level(const Level& level);
		~Level();
		void Draw();
		void ProcessMessage(const ExMessage &msg);
		int Update();
		void InitGame();
		void QuitGame();
        void Play(int cur_step);
		bool Check();
		bool is_completed;
		void LevelComplete();
	private:
		enum class OperationType
		{
			Inbox = 1,
			Outbox = 2,
			CopyFrom = 3,
			CopyTo = 4,
			Add = 5,
			Sub = 6,
			Jump = 7,
			JumpIfZero = 8,
			Invalid = 9,
		};
		int is_useful;
		int available_space;
		int input_size, output_size;
		std::vector<int> std_input,std_output;
		std::vector<Block> block_list;
		std::vector<Slider> slider_list;
		std::vector<int> user_output;
		std::vector<Space> space_list;
        std::vector<Block*> new_block;
        std::vector<Block*> output_block;
        Player* player = (Player*)nullptr;
    	int nxt_input = -1;
		int cur_step = 1;
		int last_step = 0;
		bool is_failed = false;
		LPCTSTR path;
		LPCTSTR path_state;
		std::string level_info;
        int GetNextStep(int cur_step);
};