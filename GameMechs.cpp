#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = '\0'; // Null initially
    boardSizeX = 30; // default size
    boardSizeY = 15; // default size
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

void GameMechs::getAsynchronousInput() {
    if(MacUILib_hasChar()) {
        setInput(MacUILib_getChar());
    }
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    ++score;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::generateFood(objPosArrayList* blockOff){
    int randomX;
    int randomY;
    bool foodSpawned = false;
    srand(time(0));

    while (!foodSpawned){
        randomX = (rand() % (boardSizeX-2)) + 1;
        randomY = (rand() % (boardSizeY-2)) + 1;

        for(int i = 0; i < blockOff->getSize(); i++){
            if(randomX != blockOff->getElement(i).pos->x && randomY != blockOff->getElement(i).pos->y){
                food.setObjPos(randomX, randomY, 'F');
                foodSpawned = true;
                break;
            }
        }
    }
}

objPos GameMechs::getFoodPos() const{
    return food;
}