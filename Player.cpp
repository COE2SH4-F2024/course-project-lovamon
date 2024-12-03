#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPos = objPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();      
    switch (input)
    {
    case 'w':
        if (myDir == LEFT || myDir == RIGHT || myDir == STOP) // STOPPED is also a state here
        {
            myDir = UP; 
        }
        break;

    case 's':
        if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
        {
            myDir = DOWN;
        }
        break;

    case 'a':
        if (myDir == UP || myDir == DOWN || myDir == STOP)
        {
            myDir = LEFT;
        }
        break;

    case 'd':
        if (myDir == UP || myDir == DOWN || myDir == STOP)
        {
            myDir = RIGHT;
        }
        break;
    
    case ' ':
        mainGameMechsRef->setExitTrue();
        break;

    case STOP:
        break;

    default: 
        break;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int currentX = playerPos.pos->x;
    int currentY = playerPos.pos->y;
    int boardY = mainGameMechsRef->getBoardSizeY();
    int boardX = mainGameMechsRef->getBoardSizeX();
    
    switch (myDir)
    {
    case LEFT:
        currentX--;
        if (currentX < 1)
        {
            currentX = boardX - 2; // the first hashtag is also an index value therefore it has to be columns - 2
        }
        break;
    case RIGHT:
        currentX++;
        if (currentX > boardX - 2)
        {
            currentX = 1; // to wrap around from right to left
        }
        break;
    case UP:
        currentY--;
        if (currentY < 1)
        {
            currentY = boardY - 2; //  wraps around from the top to bottom
        }
        break;
    case DOWN:
        currentY++;
        if (currentY > boardY - 2)
        {
            currentY = 1; 
        }
        break;

    case STOP:
        break;

    default: 
        break;
    }

    playerPos.setObjPos(currentX, currentY, '*');
}

// More methods to be added