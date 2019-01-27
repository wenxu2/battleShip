/*
 
Wenwen Xu
Project 2
This is the header file for battleship.c
 
*/

#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <stdbool.h>



typedef struct BATTLESHIP* Battle;
Battle createBattle(char *argument);
void showGameBoard(Battle currentGame);//show the gameBoard
void placeShip(Battle currentGame);//random generater the position and place the ships on the board

//Player A
char createFile_A(Battle currentGame);//create A.salvos A.response
void guess_A(Battle currentGame);//guess a position and write to A.salvos, also place * on GB 2
char response_A(Battle currrentGame);// read B.response's and update ship on GB2
void readFile_A(Battle currentGame);//read B.salvo and write to A.response, place "x" or "o" on GB

//Player B
char createFile_B(Battle currentGame);//create B.salvofile and B.response
void guess_B(Battle currentGame);//guess a position and write to B.salvos, also place * on GB 2
char response_B(Battle currrentGame);// read A.response's and update ship on GB2
void readFile_B(Battle currentGame);//read A.salvo and write to B.response, place "x" or "o" on GB

bool getGame(Battle currentGame);



bool checkMyGameBorad(Battle currentGame);//chech to printf "DEFEATED"
bool checkBoard(Battle currentGame,char temp);//check the gameboard
bool isGameOver(Battle currentGame);//check if the game is over
void freeBattleship(Battle currentGame);//free the malloc memory

#endif 




