#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

#define CANNOT_PUT -20000
#define MIN -10000
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
bool legal_coor (int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 6)
        return true;
    else return false; 
}
bool is_critical (Board board, int row, int col) {
    return (board.get_capacity(row, col) - board.get_orbs_num(row, col) <= 1);
}

void algorithm_A(Board board, Player player, int index[]){
    char player_color = player.get_color();
    char opponent_color;
    int board_num[5][6];
    char board_color[5][6];
    int board_capacity[5][6];
    int best_score = MIN;
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
            board_capacity[row][col] = board.get_capacity(row, col);
            board_num[row][col] = board.get_orbs_num(row, col);
            board_color[row][col] = board.get_cell_color(row, col);
        }
    }
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {
            int score = 0;
            if (board_color[row][col] != opponent_color) {
                // consider itself
                score = board_num[row][col];
                if (board_capacity[row][col] == 2)
                    score = score + 3;
                else if (board_capacity[row][col] == 3)
                    score = score + 2;
                // consider adjacency
                    // if adjacency have enemy orb
                if (!is_critical(board, row, col)) {
                    if (legal_coor(row - 1, col) && board_color[row - 1][col]
                        && is_critical(board, row - 1, col)) { // up
                        score = score - (20 - board_num[row - 1][col] * 5);
                    }
                    if (legal_coor(row + 1, col) && board_color[row + 1][col]
                        && is_critical(board, row + 1, col)) { // down
                        score = score - (20 - board_num[row + 1][col] * 5);
                    }
                    if (legal_coor(row, col - 1) && board_color[row][col - 1]
                        && is_critical(board, row, col - 1)) {  // left
                        score = score - (20 - board_num[row][col - 1] * 5);
                    }
                    if (legal_coor(row, col + 1) && board_color[row][col + 1]
                        && is_critical(board, row, col + 1)) {  // right
                        score = score - (20 - board_num[row][col + 1] * 5);
                    }
                }
                else {
                    // up
                    if (legal_coor(row - 1, col) && board_color[row - 1][col] == opponent_color
                        && is_critical(board, row - 1, col)) {
                        score = score + (30 - board_num[row - 1][col] * 5);
                    } 
                    else if (legal_coor(row - 1, col) && is_critical(board, row - 1, col)) {
                        score = score + (board_num[row - 1][col] * 2);
                    }
                    // down
                    if (legal_coor(row + 1, col) && board_color[row + 1][col] == opponent_color
                        && is_critical(board, row + 1, col)) {
                        score = score + (30 - board_num[row + 1][col] * 5);
                    } 
                    else if (legal_coor(row + 1, col) && is_critical(board, row + 1, col)) {
                        score = score + (board_num[row + 1][col] * 2);
                    }
                    // left
                    if (legal_coor(row, col - 1) && board_color[row][col - 1] == opponent_color
                        && is_critical(board, row, col - 1)) {
                        score = score + (30 - board_num[row][col - 1] * 5);
                    } 
                    else if (legal_coor(row, col - 1) && is_critical(board, row, col - 1)) {
                        score = score + (board_num[row][col - 1] * 2);
                    }
                    // right
                    if (legal_coor(row, col + 1) && board_color[row][col + 1] == opponent_color
                        && is_critical(board, row, col + 1)) {
                        score = score + (30 - board_num[row][col + 1] * 5);
                    } 
                    else if (legal_coor(row, col + 1) && is_critical(board, row, col + 1)) {
                        score = score + (board_num[row][col + 1] * 2);
                    }
                }
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
}