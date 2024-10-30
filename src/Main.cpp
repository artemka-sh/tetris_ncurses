#include "Main.hpp"


Main::Main(): groundWin(18, 10, 0, 0), ground(Vector2(10, 18)), stateWin(11, 10, 0, 0), helpWin(7, 10, 0, 0)
{
    defaultBrickPosition = (Vector2(4, 0));    
}

Main::~Main()
{
    endwin();
}

void Main::printState()
{
    stateWin.draw();
    stateWin.print("Lines:", 2, 2);
    stateWin.print( std::to_string(ground.getLines()), 4, 2);
    stateWin.print("Level:", 6, 2);
    stateWin.print(std::to_string(level), 8, 2);
    stateWin.refresh();
}

void Main::printHelp()
{
    helpWin.draw();
    helpWin.print("a - left", 1, 1);
    helpWin.print("s - down", 2, 1);
    helpWin.print("d -right", 3, 1);
    helpWin.print("q,e-rot.", 4, 1);
    helpWin.print("o - exit", 5, 1);

    helpWin.refresh();
    
}

void Main::render()
{
    ground.wdraw(groundWin);
    if(brick != nullptr)
        brick->wdraw(groundWin);
    refresh();
    groundWin.refresh();
    printState();
    printHelp();
}

void Main::moveBrick(Sides side)    
{
    if(brick)
        if(brick->moveTo(side, ground)) 
            return; // succes 
    
    delete brick;
    brick = nullptr;
}

void Main::rotateBrick(bool clockwise)
{
    if(brick)
        brick->rotate(clockwise, ground);
    return;
}

void Main::userInput()
{
    
    while(brick != nullptr)
    {            
        char input = getch();
        breakguard.lock();
        if(brick == nullptr)
            break;

        if(input == 'o')
        {
            isRunning = false;
        }
        if(input == 'q')
            rotateBrick(/*clockwise*/ false);
        if(input == 'e')
            rotateBrick(/*clockwise*/ true);
        if(input == 'a')
            moveBrick(Left);
        if(input == 'd')
            moveBrick(Right);
        if(input == 's')
            moveBrick(Down);
        if(input == 'f'){
            ground.freeze(brick);
            delete brick;
            brick = nullptr;
        }
        if(input == '1')
            level = 1;
        if(input == '2')
            level = 2;
        if(input == '3')
            level = 3;
        if(input == '4')
            level = 4;
        if(input == '5')
            level = 5;
        if(input == '6')
            level = 6;
        if(input == '7')
            level = 7;
        if(input == '8')
            level = 8;
        if(input == '9')
            level = 10;
        if(input == '0')
            level = 20;
        
        breakguard.unlock();
        if(!isRunning)
        {
            return;
        }
        render();
        
    }
    isInputRunning = false;
    return;
};

bool Main::gameTicks()
{
    while(brick != nullptr and isRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/level));
        breakguard.lock();
        moveBrick(Down);
        render();
        breakguard.unlock();
    }

    if(ground.checkGameOver())
    {
        return true;
    }
    {
        return false;
    }
};

void Main::gameOver()
{
    groundWin.print("Game Over", 8, 1);
    render();
}

void Main::run()
{
    groundWin.setPositionCentered();
    groundWin.setPosition(groundWin.getXYPositions().y, groundWin.getXYPositions().x - 6);
    stateWin.setPosition(groundWin.getXYPositions().y, groundWin.getXYPositions().x + 11);
    helpWin.setPosition(stateWin.getXYPositions().y + 11, stateWin.getXYPositions().x);
    

    render();
    getchar();    //   WELCOME SCREEN (must be)

    
    while(isRunning && !gameOverStop)   
    {
        if(brickPack.empty())
        {
            brickPack.push_back(new LBrick(defaultBrickPosition));
            brickPack.push_back(new IBrick(defaultBrickPosition));
            brickPack.push_back(new TBrick(defaultBrickPosition));
            brickPack.push_back(new JBrick(defaultBrickPosition));
            brickPack.push_back(new CBrick(defaultBrickPosition));
            brickPack.push_back(new ZBrick(defaultBrickPosition));
            brickPack.push_back(new SBrick(defaultBrickPosition));
            unsigned seed = rand();
            std::shuffle(brickPack.begin(), brickPack.end(), std::default_random_engine(seed));
        }

        brick = *brickPack.begin(); // current 

        auto myfuture = std::async(&Main::gameTicks, this);
        //(void)myfuture;

        if(!isInputRunning){
            isInputRunning = true;
            std::thread inputThread(&Main::userInput, this);
            inputThread.detach();
        }

        //myfuture.wait();
        gameOverStop = myfuture.get();
        brickPack.erase(brickPack.begin());
    }
    
    if(!gameOverStop)
    {
        gameOver();
    }

}