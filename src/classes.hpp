#pragma once

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <math.h>

class Button;
class StartButton;
class LevelSelectButton;
class MenuQuitButton;
class LevelSelectQuitButton;
class GameQuitButton;
class GamePlayButton;
class GameFileInputButton;

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
class Operation;

enum class GameStage {
    Menu = 0,
    LevelSelect,
    Game
};

struct Point;

