#include <stdio.h>
#include "battleship.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(int argc, char* argv[])
{
    char *argument = argv[1];
    Battle g = createBattle(argument);
    
    int round = 0;
    printf("\n");
    
    if(strcmp(argument,"A") == 0)
    {
        placeShip(g);
        
        while(isGameOver(g) == false)
        {
            round += 1;
            
            guess_A(g);
            showGameBoard(g);
            
            printf("Hit Enter to continue...\n");
            getchar();
            
            readFile_A(g);
            response_A(g);
            showGameBoard(g);
            printf("Round : %d\n",round);
            
            printf("Hit Enter to continue...\n");
            getchar();
            
        }
   
    }
    else if(strcmp(argument,"B") == 0)
    {
        printf("1");
        placeShip(g);
        printf("1");
        
        while(isGameOver(g) == false)
        {
            round += 1;
            
            readFile_B(g);
            guess_B(g);
            showGameBoard(g);
            
            printf("Hit Enter to continue...\n");
            getchar();
            
            response_B(g);
            showGameBoard(g);
            printf("Round : %d\n",round);
            
            printf("Hit Enter to continue...\n");
            getchar();
            
            
        }
        
    }
    
    freeBattleship(g);
 
    

    return 0;
}
