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
    std:: cout << "str=" << str << std::endl;
    std::transform(str.begin(),str.end(),str.begin(),::tolower);
    if (operation_name_to_number.find(str) == operation_name_to_number.end()) return -4;//error，没有所求指令
    if (str!="inbox" && str!="outbox" && x==INF) return -4;//error，数字不匹配

    int i = operation_list.size();
    POINT cur_operation = {100 + i*(operation_height+2),1100};//top left
    RECT pos = {cur_operation.y, cur_operation.x, cur_operation.y + operation_width, cur_operation.x + operation_height};

    std ::cout << "type = " << operation_name_to_number[str] << "x = " << x << std::endl;
    operation_list.push_back(Operation(pos, x, operation_name_to_number[str]));
    return 0;
}
int GameScene::FileInit(LPCTSTR path)
{
    std:: cout << "Ready to input operations" << std::endl;
    fin.open(path);//之后改成path
    if (!fin.is_open()) 
    {
        std::cerr << "Error: Cannot open file " << std::endl;
        return -3;
    }
    if (fin.eof()) return -3;
    std:: cout << "Ready to input operations" << std::endl;
    int n; fin >> n; fin.get();
    std::string line_str;
    std:: cout << n << std::endl;
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
    Point ptn_input_box = {850, 400}; 
    input_box = new TextBox();
    input_box->Init(RECT{ ptn_input_box.x, ptn_input_box.y, ptn_input_box.x + 100, ptn_input_box.y + 50}, 100);
    Point ptn_file_input_box = {100,650};
    file_input_box = new TextBox();
    file_input_box->Init(RECT{ ptn_file_input_box.x, ptn_file_input_box.y, ptn_file_input_box.x + 600, ptn_file_input_box.y + 50}, 100);

    FileInit("texts/input2.txt");

    std::cout << "Game Scene Init" << std::endl;
}
void GameScene::Draw()
{
    putimage_alpha(0, 0, &img_game_background);
    cur_level->Draw();
    std :: cout << "game_result = " << game_result << std::endl;
    if (game_result == 0)
    {
        std :: cout << "Operation List Size = " << operation_list.size() << std :: endl;
        game_play_btn.Draw(_T("Play"));
        game_input_btn.Draw(_T("Input"));
        game_file_input_btn.Draw(_T("Input File"));
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
            str = "You Win!";
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
    std::cout << "Game Scene Draw" << std::endl;
}
void GameScene::Update()
{
    std::cout << "Game Scene Update" << std::endl;
    game_result = cur_level->Update();
    if (game_result > 0) 
    {
        std::cout << "Game Over" << std::endl;
    }
    else if (game_result == -1) 
    {
        std::cout << "Game Win" << std::endl;
    }
    else if (game_result == -2) std::cout << "Game Failed" << std::endl; 
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
    }
    game_stop_btn.ProcessMessage(msg);
    game_btn_quit.ProcessMessage(msg);//quit最好设置在下面
    std::cout << "Game Scene ProcessMessage" << std::endl;
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
    std::cout << "Game Scene Quit" << std::endl;
    operation_list.clear();
    game_result = 0;
}

void GameScene::FileInputUpdate()
{
    TCHAR* t_str  = file_input_box->GetText();
    
    game_result = FileInit(t_str);
    file_input_box->Clear();
    if (game_result != 0) return;
    std :: cout <<"REInit" << std::endl;
    operation_list.clear();
}
void GameScene::InputUpdate()
{
    TCHAR* t_str  = input_box->GetText();
    std::string str; int len = _tcslen(t_str);
    for (int i = 0; i < _tcslen(t_str); ++i) str = str + t_str[i]; 
    std :: cout <<"REInput" << std::endl;
    std :: cout << str << std::endl;
    std :: cout << t_str << std::endl;
    game_result = CreateOperation(str);
    input_box->Clear();
}