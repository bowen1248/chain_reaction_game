#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

#define CANNOT_PUT -20000
#define LOSE -10000
#define WIN 10000
/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


void algorithm_A(Board board, Player player, int index[]){
    char player_color = player.get_color();
    char opponent_color;
    int playerboard_num[5][6];
    char playerboard_color[5][6];
    int playerboard_capacity[5][6];
    int best_score = LOSE;
    int best_move_row = 0;
    int best_move_col = 0;
    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Superficial Algorithm //////////
    if (player_color = 'r')
        opponent_color = 'b';
    else opponent_color = 'r';

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {
            playerboard_capacity[row][col] = board.get_capacity(row, col);
            playerboard_num[row][col] = board.get_orbs_num(row, col);
            playerboard_color[row][col] = board.get_cell_color(row, col);
        }
    }
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {
            int score;
            if (playerboard_color[row][col] != opponent_color) {
                score = -playerboard_num[row][col];
                score = score - playerboard_capacity[row][col];
            }
            else score = CANNOT_PUT;
            if (score > best_score) {
                best_score = score;
                best_move_row = row;
                best_move_col = col;
            }
        }
    }
            
    index[0] = best_move_row;
    index[1] = best_move_col;
    /*
    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    srand(time(NULL));
    int row, col;
    int color = player.get_color();
    
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }
    
    index[0] = row;
    index[1] = col;
    */
}