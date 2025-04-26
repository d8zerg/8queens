#ifndef QUEENSSOLVER_H
#define QUEENSSOLVER_H

#include "solutions.h"


class QueensSolver 
{
public:
    QueensSolver() = default;
    
    Solutions find_all_solutions() 
    {
        Solutions solutions;
        Board board{};
        solve_recursive(board, 0, solutions);
        return solutions;
    }
    
    Solutions find_unique_solutions() 
    {
        return find_all_solutions().filter_symmetric();
    }
    
private:
    bool is_safe(const Board& board, int row, int col) const 
    {
        for (int i = 0; i < col; ++i) 
        {
            if (board[i] == row || board[i] - i == row - col || board[i] + i == row + col) 
            {
                return false;
            }
        }
        return true;
    }

    void solve_recursive(Board& board, int col, Solutions& solutions) 
    {
        if (col == BOARD_SIZE) 
        {
            solutions.add(board);
            return;
        }

        for (int row = 0; row < BOARD_SIZE; ++row) 
        {
            if (is_safe(board, row, col)) 
            {
                board[col] = row;
                solve_recursive(board, col + 1, solutions);
            }
        }
    }
};


#endif //QUEENSSOLVER_H