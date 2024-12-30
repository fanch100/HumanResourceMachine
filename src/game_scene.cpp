#include "main.hpp"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;
void GameScene::Init()
{
    std::cout << "Game Scene Init" << std::endl;
}
void GameScene::Draw()
{
    std::cout << "Game Scene Draw" << std::endl;
}
void GameScene::Update()
{
    std::cout << "Game Scene Update" << std::endl;
}
void GameScene::ProcessMessage(const ExMessage &msg)
{
    std::cout << "Game Scene ProcessMessage" << std::endl;
}
void GameScene::Quit()
{
    std::cout << "Game Scene Quit" << std::endl;
}