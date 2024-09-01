#include "Main.hpp"

Main* Main::sInstance = nullptr;
Main::Main(): groundWin(10, 10, 0, 0), ground(Vector2(10, 10))
{
    /////////////////     INIT     ////////////////////
    if(sInstance == nullptr) 
    {
        sInstance = this;
        
    }
    else throw "double main";

    defaultBrickPosition = (Vector2(4, 0));

    
    run();
}

Main::~Main()
{
    endwin();
    exit(0); 
}


Main* Main::getIns()
{
    return sInstance;
}

void Main::render()
{
    renderguard.lock();
    ground.wdraw(groundWin);
    if(brick != nullptr)
        brick->wdraw(groundWin);
    refresh();
    groundWin.refresh();
    renderguard.unlock();
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
        breakguard.unlock();
        //////////////////// RENDER ////////////////////
        render();
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
        breakguard.unlock();
        render();
    }
    return;
};

void Main::run()
{
    groundWin.setPositionCentered();
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