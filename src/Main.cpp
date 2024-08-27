#include "Main.hpp"

Main* Main::sInstance = nullptr;
Main::Main(): groundWin(10, 10, 4, 4), ground(Vector2(10, 10))
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
    ground.wdraw(groundWin);
    if(brick != nullptr)
        brick->wdraw(groundWin);
    refresh();
    groundWin.refresh();
			       
}

void Main::moveBrick(Sides side)    //здесь хорошо бы мьюиксом закрывать
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
    return; //тут не точно
    
}

void Main::userInput()
{
    
    while(brick != nullptr)
    {            
        char input = getch();
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
        moveBrick(Down);
        render();
    }
    return;
};

void Main::run()
{
    ///////////////////       START      ///////////////////

    render();
    getchar();    //   WELCOME SCREEN (must be)

    
    while(isRunning)   // игра
    {
        if(brickPack.empty())
        {
            unsigned seed = rand();
            brickPack.push_back(new LBrick(defaultBrickPosition));
            brickPack.push_back(new IBrick(defaultBrickPosition));
            brickPack.push_back(new TBrick(defaultBrickPosition));
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