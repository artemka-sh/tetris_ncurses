#ifndef __Main
#define __Main


#include <thread>
#include <future>
#include <atomic>
#include <chrono>

#include <vector>
#include <algorithm>
#include <random> 

#include <ncurses.h>
#include "Ground.hpp"
#include "Bricks.hpp"
#include "Window.hpp"


    
class Main
{
private:
    Window groundWin;
    Ground ground;
    Window stateWin;
    Window helpWin;
    
    Vector2 defaultBrickPosition;
    std::vector<Brick*> brickPack;
    Brick* brick = nullptr;
    
    std::atomic<bool> isInputRunning = false;
    bool isRunning = true;
    bool gameOverStop = false;
    std::mutex breakguard;
    int level = 1;

public:
    
    Main();
    ~Main();
    void moveBrick(Sides side);
    void rotateBrick(bool clockwise);
    void printState();
    void printHelp();
    void render();
    void userInput();
    bool gameTicks(); // return game over state;
    void gameOver();
    void run();
};


#endif 