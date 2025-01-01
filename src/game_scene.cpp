#include "main.hpp"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;
void GameScene::Init()
{
    cur_level->InitGame();

    int cur_text_box_top = 400, cur_text_box_left = 900;
    input_box = new TextBox();
    input_box->Init(RECT{ cur_text_box_left, cur_text_box_top, cur_text_box_left + 100, cur_text_box_top + 100}, 100);
    
    std:: cout << "Ready to input operations" << std::endl;

    fin.open("texts/input2.txt");//之后改成path
    if (!fin.is_open()) std::cerr << "File not found!" << std::endl;
    if (fin.eof()) std::cerr << "File reach the End!" << std::endl;
    std:: cout << "Ready to input operations" << std::endl;
    int n; fin >> n; fin.get();
    std:: cout << n << std::endl;
    for (int i=1; i<=n; ++i) {
        std::string str; char ch; int x=INF;
        while(fin.get(ch)) {
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
            puts("YES");
        }
        std:: cout << "str=" << str << " i=" << i << std::endl;
        std::transform(str.begin(),str.end(),str.begin(),::tolower);
        if (operation_name_to_number.find(str) == operation_name_to_number.end()) ;//error，没有所求指令
        if (str!="inbox" && str!="outbox" && x!=INF) ;//error，数字不匹配
        POINT cur_operation = {100 + (i-1)*(operation_height+2),1100};//top left
        RECT pos = {cur_operation.y, cur_operation.x, cur_operation.y + operation_width, cur_operation.x + operation_height};
        std ::cout << "type = " << operation_name_to_number[str] << "x = " << x << std::endl;
        operation_list.push_back(Operation(pos, x, operation_name_to_number[str]));
    }
    fin.close();

    std::cout << "Game Scene Init" << std::endl;
}
void GameScene::Draw()
{
    putimage_alpha(0, 0, &img_game_background);
    cur_level->Draw();
    std :: cout << "game_result = " << game_result << std::endl;
    if (game_result == 0)
    {
        if (input_box != nullptr)
        {
            input_box->Draw();
        }
        std :: cout << "Operation List Size = " << operation_list.size() << std :: endl;
        for (Operation &operation : operation_list) operation.Draw(RED);
        game_play_btn.Draw(_T("Play"));
        game_stop_btn.Draw(_T("Stop"));
        game_file_input_btn.Draw(_T("Input File"));
    }
    else
    {
        settextcolor(RED);//设置字体颜色
        settextstyle(20, 0, _T("monospace"));//设置字体
        RECT pos = {100, 100, 600, 400};
        std::string str;
        if (game_result > 0)
        {
            str = "Error on Instruction " + std::to_string(game_result);
        }
        else if (game_result == -1)
        {
            str = "You Win!";
        }
        else if (game_result == -2)
        {
            str = "You Failed!";
        }
        drawtext(_T(str.c_str()), &pos, DT_CENTER);
    }
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
    // switch(msg.message)
    // {
    //     int x, y;
    //     case WM_LBUTTONDOWN:
    //         x = msg.x, y = msg.y;
    //         circle(x, y, 100);
    //         SetWindowText(hwnd,"Hello World!");
    //         break;
    //     case WM_LBUTTONUP:
    //         x = msg.x, y = msg.y;
    //         circle(x+100, y+100, 100);
    //         // PostMessage(hwnd, WM_CLOSE, 0, 0);
    //         SetWindowText(hwnd,"Hello World!");
    //         break;
    // }
    
    cur_level->ProcessMessage(msg);
    if (game_result == 0)
    {
        if (input_box != nullptr)
        {
            input_box->ProcessMessage(msg);
        }
        game_play_btn.ProcessMessage(msg);
        game_file_input_btn.ProcessMessage(msg);
    }
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
    std::cout << "Game Scene Quit" << std::endl;
    operation_list.clear();
    game_result = 0;
}