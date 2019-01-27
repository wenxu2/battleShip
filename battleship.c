/*
functions for battleship
*/
#include <stdio.h>
#include "battleship.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct BATTLESHIP
{
    char **gameboard;
    char **gameboard2;
    char *player;
    char *response;
    char winner;
    int x;
    int y;
    bool gameEnd;
    int hit;
    
    
};

Battle game(char **gameboard, char **gameboard2,char *player,char *response, char winner, int x, int y,bool gameEnd,int hit)
{
    Battle g = malloc(sizeof(*g));
    
    g->gameboard = gameboard;
    g->gameboard2 = gameboard2;
    g->player = player;
    g->response = response;
    g->winner = winner;
    g->x = x;
    g->y = y;
    g->gameEnd = gameEnd;
    g->hit = hit;
    
    return g;
    
}

Battle createBattle(char *argument)//create the gameboard
{
    Battle g = game(NULL,NULL, 0,argument,0,0,0,false,0);
    
    g->response = malloc(sizeof(char)*10);
    g->gameboard = malloc(sizeof(char*) * 10);
    g->gameboard2 = malloc(sizeof(char*) * 10);
    
    int i;
    
    for(i =0 ; i <10; ++i)
    {
        g->gameboard[i] = malloc(sizeof(char*) * 10);
        strcat(g->gameboard[i],"----------");
        
        g->gameboard2[i] = malloc(sizeof(char*) * 10);
        strcat(g->gameboard2[i],"----------");
        
    }
    
   
    return g;
    
}

void showGameBoard(Battle currentGame)
{
    int i,j;
    
    printf(" ships\t\t\t\t\t salvos\n");
    printf("  0 1 2 3 4 5 6 7 8 9");
    printf("\t\t\t  0 1 2 3 4 5 6 7 8 9\n");
    
    for(i =0; i<10; ++i)
    {
        printf("%d",i);
        for(j =0 ; j<10; ++j)
        {
            printf(" ");
            printf("%c",currentGame->gameboard[i][j]);
           
            
        }
        
        printf("\t\t\t");
        
        printf("%d",i);
        for(j =0 ; j<10; ++j)
        {
            printf(" ");
            printf("%c",currentGame->gameboard2[i][j]);
            
        }
        
        printf("\n");
    }
    
}



void placeShip(Battle currentGame)
{
    int x, y, i;
    
    srand(time(NULL));
    
    
    //
    //CARRIER - CCCCC
    //
    x = rand()%10;
    y = rand()%2;
    
    currentGame->gameboard[x][y] = 'C';
    
    if((x >= 6) && (x <= 10))
    {
        for(i = 1; i<5; ++i)
        {
            currentGame->gameboard[x-i][y] = 'C';
        }
    }
    else if( (x >=0) && (x <=6))
    {
        for(i = 1; i<5; ++i)
        {
            currentGame->gameboard[x+i][y] = 'C';
        }
        
    }
    
    
    //
    //SUBMARINE - SSS
    //
    x = rand()%5 + 5;
    y = rand()%4 + 2;
    currentGame->gameboard[x][y] = 'S';
    
    if((x >=5) && (x<= 7))
    {
        for(i =1; i<3 ; i++)
        {
            currentGame->gameboard[x+i][y] = 'S';
        }
    }
    else if ((x>=8)&&(x<=10))
    {
        for(i =1; i<3 ; i++)
        {
            currentGame->gameboard[x-i][y] = 'S';
        }
    }
    
    
    //
    //BATTLESHIP - BBBB
    //
    x = rand()%2;
    y = rand()%8 + 2;
    
    currentGame->gameboard[x][y] = 'B';
    
    if((y>=5) && (y<=10))
    {
        
        for(i = 1; i<4; ++i)
        {
            currentGame->gameboard[x][y-i] = 'B';
        }
        
    }
    
    else if((y>=2) && (y <= 6))
    {
        
        for(i = 1; i<4; ++i)
        {
            currentGame->gameboard[x][y+i] = 'B';
        }
        
    }
    
    
    //
    //PRTOL - PP
    //
    
    currentGame->gameboard[8][8] = 'P';
    int position = rand()%4;
    if(position == 0)
    {
        currentGame->gameboard[7][8] = 'P';
    }
    else if(position == 1)
    {
        currentGame->gameboard[9][8] = 'P';
    }
    else if(position == 2)
    {
        currentGame->gameboard[8][7] = 'P';
    }
    else if(position == 3)
    {
        currentGame->gameboard[8][9] = 'P';
    }
    

    //
    //DESTROYER - RRR
    //
    x = rand()%2 + 3;
    y = rand()%8 + 2;
    
    currentGame->gameboard[x][y] = 'R';
    
    if((y>=2)&&(y<=7))
    {
        for(i = 1; i<3; ++i)
        {
            currentGame->gameboard[x][y+i] = 'R';
        }
    }
    else if((y>=3) && (y<=10))
    {
        for(i =1; i<3; ++i)
        {
            currentGame->gameboard[x][y-i] = 'R';
        }
    }
    
    
    
}

char createFile_A(Battle currentGame)
{
    FILE* salvoFile;
    salvoFile = fopen("A.salvos", "w");
    
    FILE* resFile;
    resFile = fopen("A.response","w");
    
    fclose(salvoFile);
    fclose(resFile);
    return 0;
}

void guess_A(Battle currentGame)
{
    FILE* salvoFile = fopen("A.salvos","a+");
    srand(time(NULL));
    

    int x = rand()%10;
    int y = rand()%10;
    
    while(currentGame->gameboard2[x][y]!= '-')
    {
       x = rand()%10;
       y = rand()%10;
    }
    
    currentGame->x = x;
    currentGame->y = y;
    
    currentGame->gameboard2[currentGame->x][currentGame->y] = '*';
    fprintf(salvoFile,"%d ",currentGame->x);
    fprintf(salvoFile,"%d\n",currentGame->y);
    
    fclose(salvoFile);
    
}

char response_A(Battle currentGame)
{
    FILE* resFile = fopen("B.response","r");

    char a = '\0';
    int i=0;
 
    //Read response
    fseek(resFile,-1,SEEK_END);
    fread(&a,1,1,resFile);
    
    
    
    int h = 0;
    
    while(h==0)
    {
        
            if((a =='D')|| (a =='d'))
            {
                strcpy(currentGame->response,"DEFEATED");
                currentGame->winner = 'A';
                currentGame->gameEnd = true;
                h = 1;
            }
            
            else if((a=='K')||(a=='k'))
            {
                strcpy(currentGame->response,"SUNK");
                currentGame->gameboard2[currentGame->x][currentGame->y] = 'x';
                h=1;
            }
            
            else if((a=='S')||(a=='s'))
            {
                strcpy(currentGame->response,"MISS");
                currentGame->gameboard2[currentGame->x][currentGame->y] = 'o';
                h=1;
            }
            
            else if((a=='T')||(a=='t'))
            {
                strcpy(currentGame->response,"HIT");
                currentGame->gameboard2[currentGame->x][currentGame->y] = 'x';
                h=1;
            }
        
            else
            {
                fseek(resFile,-i,SEEK_END);
                fread(&a,1,1,resFile);
                h=0;
            }
        i++;
    }
    
    showGameBoard(currentGame);
    
    fclose(resFile);
    return 0;
    
}


void readFile_A(Battle currentGame)
{
    
    
    FILE* salvoFile = fopen("B.salvos","r");
    FILE* resFile = fopen("A.response","a+");

    int buffer[2000];
    int a=0;
    int i=0;
    char temp = '\0';

    
   while(fscanf(salvoFile,"%d",&a) >= 0)
    {
      buffer[i] = a;
      i++;
        
    }
    
    
        if((currentGame->gameboard[buffer[i-2]][buffer[i-1]] == '-')
               ||(currentGame->gameboard[buffer[i-2]][buffer[i-1]] == 'x'))
        {
            fprintf(resFile,"MISS\n");
        
        }
        else
        {
            currentGame->hit += 1;
            temp = currentGame->gameboard[buffer[i-2]][buffer[i-1]];
            printf("%c",temp);
                
            currentGame->gameboard[buffer[i-2]][buffer[i-1]] = 'x';
    
            if(currentGame->hit == 17)
            {
                fprintf(resFile,"DEFEATED\n");
                currentGame->winner = 'B';
                currentGame->gameEnd = true;
                    
            }
            else if(checkBoard(currentGame,temp) == false)
            {
                fprintf(resFile,"SUNK\n");
            }
            else
            {
                fprintf(resFile,"HIT\n");
                    
            }
        }
    
    fclose(salvoFile);
    fclose(resFile);

}



//
///PLAYER B
//

char createFile_B(Battle currentGame)
{
    FILE* salvoFile;
    salvoFile = fopen("B.salvos", "w");
    
    FILE* resFile;
    resFile = fopen("B.response","w");
    
    fclose(salvoFile);
    fclose(resFile);
    return 0;
}

void guess_B(Battle currentGame)
{
       FILE* salvoFile = fopen("B.salvos","a+");
        srand(time(NULL));
        
        int x = rand()%10;
        int y = rand()%10;
        
        while(currentGame->gameboard2[x][y]!= '-')
        {
            x = rand()%10;
            y = rand()%10;
        }
    
        currentGame->x = x;
        currentGame->y = y;
    
        currentGame->gameboard2[currentGame->x][currentGame->y] = '*';
        fprintf(salvoFile,"%d ",currentGame->x);
        fprintf(salvoFile,"%d\n",currentGame->y);
        
        fclose(salvoFile);
    
    
}

char response_B(Battle currentGame)
{
    FILE* resFile = fopen("A.response","r");
    
    char a = '\0';
    int i=0;
    
    //Read response
    fseek(resFile,-1,SEEK_END);
    fread(&a,1,1,resFile);
    
    
    
    int h = 0;
    
    while(h==0)
    {
        ++i;
        
        //placeShip(currentGame);
        
        if((a =='D')|| (a =='d'))
        {
            strcpy(currentGame->response,"DEFEATED");
            currentGame->winner = 'B';
            currentGame->gameEnd = true;
            h = 1;
        }
        
        else if((a=='K')||(a=='k'))
        {
            strcpy(currentGame->response,"SUNK");
            currentGame->gameboard2[currentGame->x][currentGame->y] = 'x';
            h=1;
        }
        
        else if((a=='S')||(a=='s'))
        {
            strcpy(currentGame->response,"MISS");
            currentGame->gameboard2[currentGame->x][currentGame->y] = 'o';
            h=1;
        }
        
        else if((a=='T')||(a=='t'))
        {
            strcpy(currentGame->response,"HIT");
            currentGame->gameboard2[currentGame->x][currentGame->y] = 'x';
            h=1;
        }
        
        else
        {
            fseek(resFile,-i,SEEK_END);
            fread(&a,1,1,resFile);
            h=0;
        }
    }
    
    showGameBoard(currentGame);
    
    fclose(resFile);
    return 0;
    
}



void readFile_B(Battle currentGame)
{
    
    
    FILE* salvoFile = fopen("A.salvos","r");
    FILE* resFile = fopen("B.response","a+");
    
    int buffer[2000];
    int a=0;
    int i=0;
    char temp = '\0';
    
    
    while(fscanf(salvoFile,"%d",&a) >= 0)
    {
        buffer[i] = a;
        i++;
        
    }
    
    
    if((currentGame->gameboard[buffer[i-2]][buffer[i-1]] == '-')
       ||(currentGame->gameboard[buffer[i-2]][buffer[i-1]] == 'x'))
    {
        fprintf(resFile,"MISS\n");
        
    }
    else
    {
        currentGame->hit += 1;
        temp = currentGame->gameboard[buffer[i-2]][buffer[i-1]];
        printf("%c",temp);
        
        currentGame->gameboard[buffer[i-2]][buffer[i-1]] = 'x';
    
    if(currentGame->hit == 17)
    {
        fprintf(resFile,"DEFEATED\n");
        currentGame->winner = 'A';
        currentGame->gameEnd = true;
        
    }
    else if(checkBoard(currentGame,temp) == false)
    {
        fprintf(resFile,"SUNK\n");
    }
    else
    {
        fprintf(resFile,"HIT\n");
        
    }
    }
    
    
    fclose(salvoFile);
    fclose(resFile);
    
}



bool isGameOver(Battle currentGame)
{
    if(currentGame->gameEnd == true)
    {
        printf("The winner is %c\n",currentGame->winner);
        
        return true;
        
    }
    else
        return false;
}


bool checkBoard(Battle currentGame, char temp)
{
    int i;
    int j;
    
    for(i =0; i<10; i++)
    {
        
        for(j =0; j<10; j++)
        {
            
            if(currentGame->gameboard[i][j] == temp)
            {
                return true;
            }
        }
    }
    
    return false;
    
}

void freeBattleship(Battle currentGame)
{
    free(currentGame->response);

    int i;
    for(i = 0; i<10; i++)
    {
       
            free(currentGame->gameboard[i]);
            free(currentGame->gameboard2[i]);
        
        
    }
    free(currentGame->gameboard);
    free(currentGame->gameboard2);
    
    free(currentGame);
    
    
}
