#include "Main.hpp"

Main::Main(): groundWin(18, 10, 0, 0), ground(Vector2(10, 18)), stateWin(18, 10, 0, 0)
{
    defaultBrickPosition = (Vector2(4, 0));    
    
    run();
}

Main::~Main()
{
    endwin();
    exit(0); 
}

void Main::printState()
{
    stateWin.draw();
    stateWin.print("Lines:", 2, 2);
    stateWin.print( std::to_string(ground.getLines()), 4, 2);
    stateWin.refresh();
}

void Main::render()
{
    ground.wdraw(groundWin);
    if(brick != nullptr)
        brick->wdraw(groundWin);
    refresh();
    groundWin.refresh();
    printState();
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
        render();
        breakguard.unlock();
    }
    isInputRunning = false;
    return;
};

void Main::gameTicks()
{
    while(brick != nullptr and isRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        breakguard.lock();
        moveBrick(Down);
        render();
        breakguard.unlock();
    }
    return;
};

void Main::run()
{
    groundWin.setPositionCentered();
    groundWin.setPosition(groundWin.getXYPositions().y, groundWin.getXYPositions().x - 5);
    stateWin.setPositionCentered();
    stateWin.setPosition(stateWin.getXYPositions().y, stateWin.getXYPositions().x + 5);
    

    render();
    getchar();    //   WELCOME SCREEN (must be)

    
    while(isRunning)   
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
        (void)myfuture;

        if(!isInputRunning){
            isInputRunning = true;
            std::thread inputThread(&Main::userInput, this);
            inputThread.detach();
        }

        myfuture.wait();
        brickPack.erase(brickPack.begin());
    }
    
}