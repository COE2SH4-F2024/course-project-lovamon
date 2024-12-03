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

    game = new GameMechs(30, 15);
    myPlayer = new Player(game);
    game->generateFood(myPlayer->getPlayerPos());

}

void GetInput(void)
{
   game->getAsynchronousInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    game->clearInput(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    int i;
    int j;
    for (i = 0; i < game->getBoardSizeY(); i++) {
        for (j = 0; j < game->getBoardSizeX(); j++) {
            if (i == game->getFoodPos().pos->y && j == game->getFoodPos().pos->x)
            {
                MacUILib_printf("%c", game->getFoodPos().getSymbol());
            }
            else if (i == 0 || i == game->getBoardSizeY() - 1 || j == 0 || j == game->getBoardSizeX() - 1) 
            {
                // Print borders represented by '#'
                MacUILib_printf("#");
            } 
            else 
            {
                // Print empty space inside the game board
                bool valid;
                for(int k = 0; k<myPlayer->getPlayerPos()->getSize(); k++){
                    valid = false;
                    if (i == myPlayer->getPlayerPos()->getElement(k).getObjPos().pos->y && j == myPlayer->getPlayerPos()->getElement(k).getObjPos().pos->x) {
                        MacUILib_printf("%c", myPlayer->getPlayerPos()->getElement(k).getSymbol());
                        valid = true;
                        break;
                    } 
                }

                if(!valid){
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");  // Move to the next row
    } 
    MacUILib_printf("Your Score is %d\n", myPlayer->getPlayerPos()->getSize()-1);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if(game->getLoseFlagStatus()){
        MacUILib_printf(" You Lost The Game.\n");
    } 
    if (game->getExitFlagStatus()) {
        MacUILib_printf(" You Exitted the Game. \n");
    }

    MacUILib_uninit();

    delete myPlayer;
    delete game;
}
