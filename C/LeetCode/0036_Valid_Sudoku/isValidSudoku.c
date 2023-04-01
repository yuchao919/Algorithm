/**
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

Note:

    A Sudoku board (partially filled) could be valid but is not necessarily solvable.
    Only the filled cells need to be validated according to the mentioned rules.

Example 1:

Input: board =
[['5','3','.','.','7','.','.','.','.']
,['6','.','.','1','9','5','.','.','.']
,['.','9','8','.','.','.','.','6','.']
,['8','.','.','.','6','.','.','.','3']
,['4','.','.','8','.','3','.','.','1']
,['7','.','.','.','2','.','.','.','6']
,['.','6','.','.','.','.','2','8','.']
,['.','.','.','4','1','9','.','.','5']
,['.','.','.','.','8','.','.','7','9']]
Output: true

Example 2:

Input: board =
[['8','3','.','.','7','.','.','.','.']
,['6','.','.','1','9','5','.','.','.']
,['.','9','8','.','.','.','.','6','.']
,['8','.','.','.','6','.','.','.','3']
,['4','.','.','8','.','3','.','.','1']
,['7','.','.','.','2','.','.','.','6']
,['.','6','.','.','.','.','2','8','.']
,['.','.','.','4','1','9','.','.','5']
,['.','.','.','.','8','.','.','7','9']]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Constraints:

    board.length == 9
    board[i].length == 9
    board[i][j] is a digit 1-9 or '.'.

    创建一个长度为9的数组，横向遍历，把数字转成下标给数组对应的数字置为1，如果有重复则返回false
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidSudoku(char **board, int boardSize, int *boardColSize)
{
    *boardColSize = 9;

    char a[9];
    char b[9];

    int num = 0;

    // 横向检查、纵向也检查
    for (size_t i = 0; i < 9; i++)
    {
        memset(a, '.', sizeof(a));
        memset(b, '.', sizeof(b));
        for (size_t j = 0; j < 9; j++)
        {
            num = board[i][j] - '1';
            if (num > -1 && num < 9)
            {
                if (a[num] != '.')
                {
                    return false;
                }
                a[num] = '1';
            }

            num = board[j][i] - '1';
            if (num > -1 && num < 9)
            {
                if (b[num] != '.')
                {
                    return false;
                }
                b[num] = '1';
            }
        }
    }
    int row, col, _row;

    // 遍历3x3单元格，// 3行3列一组，横向纵向分别有3组
    for (size_t i = 0; i < 3; i++)
    {
        row = i * 3;
        for (size_t j = 0; j < 3; j++)
        {
            col = j * 3;
            memset(a, '.', sizeof(a));
            for (size_t p = 0; p < 3; p++)
            {
                _row = row + p;
                for (size_t q = 0; q < 3; q++)
                {
                    num = board[_row][col + q] - '1';
                    if (num > -1 && num < 9)
                    {
                        if (a[num] != '.')
                        {
                            return false;
                        }
                        a[num] = '1';
                    }
                }
            }
        }
    }

    return true;
}

bool checkrow(int row, int col, char **board, int n)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] - '0' == n && i != col)
            return false;
    }
    return true;
}
bool checkcol(int row, int col, char **board, int n)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] - '0' == n && i != row)
            return false;
    }
    return true;
}
bool checkgrid(int row, int col, char **board, int n)
{
    int r = (row / 3) * 3;
    int c = (col / 3) * 3;
    for (int i = r; i < r + 3; i++)
    {
        for (int j = c; j < c + 3; j++)
        {
            if (board[i][j] - '0' == n)
            {
                if (i != row && j != col)
                    return false;
            }
        }
    }
    return true;
}

// 最快的解法
bool isValidSudoku_fastest(char **board, int boardSize, int *boardColSize)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // 原因就是这里会跳过不需要校验的点
            if (board[i][j] != '.')
            {
                int p = board[i][j] - '0';
                bool check = checkrow(i, j, board, p) && checkcol(i, j, board, p) && checkgrid(i, j, board, p);
                if (check == false)
                    return false;
            }
        }
    }
    return true;
}

void main()
{
    char board[9][9] = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    int boardSize = 0;
    char **boardPtr = malloc(9 * sizeof(char *));
    for (int i = 0; i < 9; i++)
    {
        boardPtr[i] = malloc(9 * sizeof(char));
        for (int j = 0; j < 9; j++)
        {
            boardPtr[i][j] = board[i][j];
        }
    }

    bool result = isValidSudoku(boardPtr, 9, &boardSize);
    printf("answer: %s\n", result ? "true" : "false");

    for (int i = 0; i < 9; i++)
    {
        free(boardPtr[i]);
    }
    free(boardPtr);
}
