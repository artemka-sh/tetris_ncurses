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


    
class Main
{
private:
    static Main* sInstance;
    Vector2 screenSize;
    Vector2 defaultBrickPosition;
    std::vector<Brick*> brickPack;
    Brick* brick = nullptr;
    std::atomic<bool> isInputRunning = false;
    bool isRunning = true;

public:
    Ground ground;
    Main();
    ~Main();
    static Main* getIns();
    void moveBrick(Sides side);
    void rotateBrick(bool clockwise);
    void render();
    void userInput();
    void gameTicks();
    void run();
};


#endif 