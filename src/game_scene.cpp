#include "main.hpp"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;

int GameScene::CreateOperation(const std::string& line_str)
{
    std::string str; char ch; int x=INF;
    for(int j = 0; j < line_str.size(); ++j) {
        ch = line_str[j];
        if (ch == '\n' || ch == '\r' || ch == EOF) break;
        if (isdigit(ch)) 
        {
            if (x == INF) x=0;
            x=x*10+ch-'0';
        }
        else if (('A'<=ch && ch<='Z') || ('a'<=ch && ch<='z')) {
            ch = tolower(ch);
            str = str + ch;
        }
    }
    std::transform(str.begin(),str.end(),str.begin(),::tolower);
    if (operation_name_to_number.find(str) == operation_name_to_number.end()) return -4;//error，没有所求指令
    if (str!="inbox" && str!="outbox" && x==INF) return -4;//error，数字不匹配

    int i = operation_list.size();
    POINT cur_operation = {100 + i*(operation_height+2),1100};//top left
    RECT pos = {cur_operation.y, cur_operation.x, cur_operation.y + operation_width, cur_operation.x + operation_height};

    operation_list.push_back(Operation(pos, x, operation_name_to_number[str], i+1));
    return 0;
}
int GameScene::FileInit(LPCTSTR path)
{
    fin.open(path);//之后改成path
    if (!fin.is_open()) 
    {
        return -3;
    }
    if (fin.eof()) return -3;
    int n; fin >> n; fin.get();
    std::string line_str;
    for (int i=1; i<=n; ++i) {
        std::getline(fin,line_str);
        int type = CreateOperation(line_str);
        if (type != 0) return -4;
    }
    fin.close();
    fin.clear();
    fin.seekg(0, std::ios::beg);
    return 0;
}
void GameScene::Init()
{
    cur_level->InitGame();
    //文本框初始化
    Point ptn_input_box = {870, 350}; 
    input_box = new TextBox();
    input_box->Init(RECT{ ptn_input_box.x, ptn_input_box.y, ptn_input_box.x + 160, ptn_input_box.y + 50}, 100);
    Point ptn_file_input_box = {100, 650};
    file_input_box = new TextBox();
    file_input_box->Init(RECT{ ptn_file_input_box.x, ptn_file_input_box.y, ptn_file_input_box.x + 600, ptn_file_input_box.y + 50}, 100);

    //FileInit("texts/input2.txt");

}
void GameScene::Draw()
{
    putimage_alpha(0, 0, &img_game_background);
    cur_level->Draw();
    if (game_result == 0)
    {
        game_play_btn.Draw(_T("Play"));
        game_input_btn.Draw(_T("Input"));
        game_delete_btn.Draw(_T("Delete"));
        game_file_input_btn.Draw(_T("FileInput"));
    }
    else
    {
        settextcolor(RED);//设置字体颜色
        settextstyle(20, 0, _T("monospace"));//设置字体
        RECT pos = {100, 200, 600, 300};
        std::string str;
        if (game_result > 0)
        {
            str = "Error on Instruction " + std::to_string(game_result);
        }
        else if (game_result == -1)
        {
            str = "You Win With " + std::to_string(cur_level->tot_step) + " Steps!";
            cur_level->is_completed = true;
            cur_level->LevelComplete();
        }
        else if (game_result == -2)
        {
            str = "You Failed!";
        }
        else if (game_result == -3)
        {
            str = "No Such File!";
        }
        else if (game_result == -4)
        {
            str = "Invalid Input!";
        }
        else if (game_result == -5)
        {
            str = "Can't Delete Anymore!";
        }
        drawtext(_T(str.c_str()), &pos, DT_CENTER);
    }
    if (input_box != nullptr)
    {
        input_box->Draw();
    }
    if (file_input_box != nullptr)
    {
        file_input_box->Draw();
    }
    for (Operation &operation : operation_list) operation.Draw(RED);
    game_stop_btn.Draw(_T("Stop"));
    game_btn_quit.Draw(_T("Quit"));
}
void GameScene::Update()
{
    game_result = cur_level->Update();
}
void GameScene::ProcessMessage(const ExMessage &msg)
{
    cur_level->ProcessMessage(msg);
    if (game_result == 0)
    {
        if (input_box != nullptr)
        {
            input_box->ProcessMessage(msg);
        }
        if (file_input_box != nullptr)
        {
            file_input_box->ProcessMessage(msg);
        }
        game_play_btn.ProcessMessage(msg);
        game_input_btn.ProcessMessage(msg);
        game_file_input_btn.ProcessMessage(msg);
        game_delete_btn.ProcessMessage(msg);
    }
    game_stop_btn.ProcessMessage(msg);
    game_btn_quit.ProcessMessage(msg);//quit最好设置在下面
}
void GameScene::Quit()
{
    cur_level->QuitGame();
    if (input_box != nullptr) 
    {
        delete input_box;
        input_box = nullptr;
    }
    if (file_input_box != nullptr) 
    {
        delete file_input_box;
        file_input_box = nullptr;
    }
    operation_list.clear();
    game_result = 0;
}

void GameScene::FileInputUpdate()
{
    TCHAR* t_str  = file_input_box->GetText();
    operation_list.clear();
    game_result = FileInit(t_str);
    file_input_box->Clear();
    if (game_result != 0) return;
}
void GameScene::InputUpdate()
{
    TCHAR* t_str  = input_box->GetText();
    std::string str; int len = _tcslen(t_str);
    for (int i = 0; i < _tcslen(t_str); ++i) str = str + t_str[i]; 
    game_result = CreateOperation(str);
    input_box->Clear();
}
void GameScene::DeleteUpdate()
{
    if (operation_list.size() == 0) 
    {
        game_result = -5;
        return;
    }
    operation_list.pop_back();
}