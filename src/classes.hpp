#pragma once

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

class Button;
class StartButton;
class LevelSelectButton;
class MenuQuitButton;
class LevelSelectQuitButton;
class GameQuitButton;

class Scene;
class SceneManager;
class MenuScene;
class LevelSelectScene;
class GameScene;

class Block;
class Slider;
class Level;
class TextBox;
class Player;
class Space;

enum class GameStage {
    Menu = 0,
    LevelSelect,
    Game
};

