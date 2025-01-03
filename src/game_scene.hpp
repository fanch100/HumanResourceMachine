#pragma once

#include "classes.hpp"
#include "scene.hpp"
// #include "button.hpp"
// #include "scene_manager.hpp"

extern IMAGE img_game_background;
extern IMAGE block;

extern GameQuitButton game_btn_quit;
extern GameStopButton game_stop_btn;
extern GamePlayButton game_play_btn;
extern GameFileInputButton game_file_input_btn;
extern GameInputButton game_input_btn;
extern GameDeleteButton game_delete_btn;

extern std::ifstream fin;
extern const int INF;
extern std::unordered_map<std::string, int> operation_name_to_number;
extern std::unordered_map<int, std::string> operation_number_to_name;

extern const int operation_width;
extern const int operation_height;

extern std::ofstream fout;

class GameScene : public Scene
{
    public:
        GameScene();
        ~GameScene();
        void Init();
        void Draw();
        void Update();
        void FileInputUpdate();
        void InputUpdate();
        void ProcessMessage(const ExMessage &msg);
        void Quit();
        int CreateOperation(const std::string& line_str);
        int FileInit(LPCTSTR path);
        void DeleteUpdate();
        std::vector<Operation> operation_list;
        int game_result = 0;
    private:
        TextBox* input_box = nullptr;
        TextBox* file_input_box = nullptr;
};