/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

    Each of the digits 1-9 must occur exactly once in each row.
    Each of the digits 1-9 must occur exactly once in each column.
    Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

The '.' character indicates empty cells.

Example 1:

Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

bool isValid(char **board, int row, int col, char c)
{
    int blkRow = 3 * (row / 3);
    int blkCol = 3 * (col / 3);
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == c)
            return false; // check row
        if (board[row][i] == c)
            return false; // check column
        int ri = (i / 3);
        int ci = i % 3;
        if (board[blkRow + ri][blkCol + ci] == c)
            return false; // check 3*3 block
    }

    return true;
};

bool solve(char **board, int boardSize, int *boardColSize)
{
    char nums[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.')
            {
                for (int c = 0; c < 9; c++)
                {
                    // trial. Try 1 through 9
                    if (isValid(board, i, j, nums[c]))
                    {
                        board[i][j] = nums[c]; // Put c for this cell

                        if (solve(board, boardSize, boardColSize))
                        {
                            return true; // If it's the solution return true
                        }
                        else
                        {
                            board[i][j] = '.'; // Otherwise go back
                        }
                    }
                }

                return false;
            }
        }
    }
    return true;
}

void solveSudoku(char **board, int boardSize, int *boardColSize)
{
    // 抄的答案，最简单的解法，利用递归回溯，相当于从第一个待定点开始推下一个待定点
    solve(board, boardSize, boardColSize);
}

char **convertToPtr(char board[][9], int rowSize, int colSize)
{
    char **boardPtr = malloc(rowSize * sizeof(char *));
    for (int i = 0; i < rowSize; i++)
    {
        boardPtr[i] = malloc(colSize * sizeof(char));
        for (int j = 0; j < colSize; j++)
        {
            boardPtr[i][j] = board[i][j];
        }
    }

    return boardPtr;
}

void printSudoku(char **board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // char board[9][9] = {
    //     {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
    //     {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
    //     {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
    //     {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    //     {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    //     {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    //     {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    //     {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    //     {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    char board[9][9] = {
        {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
        {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
        {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
        {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
        {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
        {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
        {'.', '.', '.', '2', '7', '5', '9', '.', '.'},
    };

    char **boardPtr = convertToPtr(board, 9, 9);
    int boardColSize = 9;
    solve(boardPtr, 9, &boardColSize);

    printSudoku(boardPtr);

    printf("\n");

    return 0;
}