#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player* myPlayer;
GameMechs* game;

int main(void)
{

    Initialize();

    while(game->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    game = new GameMechs(30,15);
    myPlayer = new Player(game);

    exitFlag = false;
}

void GetInput(void)
{
   game->getAsynchronousInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    int i;
    int j;
    for (i = 0; i < game->getBoardSizeY(); i++) {
        for (j = 0; j < game->getBoardSizeX(); j++) {
            if (i == myPlayer->getPlayerPos().getObjPos().pos->y && j == myPlayer->getPlayerPos().getObjPos().pos->x) {
                MacUILib_printf("%c", myPlayer->getPlayerPos().symbol);
            }
            else if (i == 0 || i == game->getBoardSizeY() - 1 || j == 0 || j == game->getBoardSizeX() - 1) {
                // Print borders represented by '#'
                MacUILib_printf("#");
            } else {
                // Print empty space inside the game board
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");  // Move to the next row
    } 
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
