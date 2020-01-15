#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

#define CANNOT_PUT -20000
#define MIN -10000
// Check if input coordinate is valid
bool legal_coor (int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 6)
        return true;
    else return false; 
}

// See if input tile are only 1 orbs from explode
bool is_critical (Board board, int row, int col) {
    return (board.get_capacity(row, col) - board.get_orbs_num(row, col) <= 1);
}

// main algorithm
void algorithm_A(Board board, Player player, int index[]){
    char player_color = player.get_color(); // get player orb's color
    char opponent_color;                    // get opponent's color
    int board_num[5][6];                    // current orb's number on board
    char board_color[5][6];                 // current orb's color on board
    int board_capacity[5][6];               // maximum orb's capacity of board
    int best_score = MIN;                   // best score of every tile
    int best_move_row = 0;                  // put orb on highest score cell
    int best_move_col = 0;

    // get player's color
    if (player_color = 'r')
        opponent_color = 'b';
    else opponent_color = 'r';

    // get information about board
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {
            board_capacity[row][col] = board.get_capacity(row, col);
            board_num[row][col] = board.get_orbs_num(row, col);
            board_color[row][col] = board.get_cell_color(row, col);
        }
    }
    // judge every tile and give it a score
    // cell which get best score is best to put on a orb
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {
            int score = 0;
            // if no opponent on tile
            if (board_color[row][col] != opponent_color) {
                // consider itself
                // consider number of orb on that cell
                score = board_num[row][col];
                // consider it's position on board
                if (board_capacity[row][col] == 2)
                    score = score + 3;
                else if (board_capacity[row][col] == 3)
                    score = score + 2;
                // consider adjacency
                // if the current cell is not critical
                if (!is_critical(board, row, col)) {
                    // if adjacency block have opponent cell is at critical
                    // give this cell lower score
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
                // if cell is critical
                else {
                    // if adjacency block have opponent cell is at critical
                    // give this cell much higher score
                    // or if adjacency block have player cell is at critical
                    // give this cell higher score
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
            // if there is opponent orb in cell
            // give this cell lowest score
            else score = CANNOT_PUT;
            // if current cell score is higher than previous highest cell score
            // update new location
            if (score > best_score) {
                best_score = score;
                best_move_row = row;
                best_move_col = col;
            }
        }
    }
    // output chess coordinate
    index[0] = best_move_row;
    index[1] = best_move_col;
}