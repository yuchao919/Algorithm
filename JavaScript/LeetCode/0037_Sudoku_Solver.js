/**
 * @param {character[][]} board
 * @return {void} Do not return anything, modify board in-place instead.
 */
var solveSudoku = function (board) {
  /**
   * 第一阶段：
   *    记录所有空元素'.'的位置，然后递归判断空元素是否有唯一可填项，只有填入过一次就不停循坏。
   *    这个阶段能解决最简单的数独，但是存在有些单元格不止一个可填项就卡住了
   * 第二阶段：我卡住了。。直接抄答案，学习如何递归回溯
   *
   */
  var emptyNodes = [];
  // 记录所有空元素
  for (var i = 0; i < board.length; i++) {
    for (var j = 0; j < board[i].length; j++) {
      var element = board[i][j];
      if (element == ".") {
        emptyNodes.push({ row: i, col: j, candidates: [], reject: false });
      }
    }
  }

  var result = solveSimpleSudoku(copySudoku(board), emptyNodes);

  // 第一阶段返回
  if (emptyLength == 0) {
    return true;
  }

  var boardCopy = [];
  for (let i = 0; i < board.length; i++) {
    boardCopy.push([]);
    for (let j = 0; j < board[i].length; j++) {
      boardCopy[i].push(board[i][j]);
    }
  }
  // 找一个emptyNode的剩余可填最小的
  var minLength = Math.min.apply(
    null,
    emptyNodes.map((x) => x.candidates.length)
  );

  return emptyNodes.length == 0;
};

var copySudoku = function (board) {
  var boardCopy = [];
  for (let i = 0; i < board.length; i++) {
    boardCopy.push([]);
    for (let j = 0; j < board[i].length; j++) {
      boardCopy[i].push(board[i][j]);
    }
  }
  return boardCopy;
};

var solveSimpleSudoku = function (board, emptyNodes) {
  var emptyLength = emptyNodes.length;
  while (emptyLength > 0) {
    for (var i = 0; i < emptyLength; i++) {
      var emptyEl = emptyNodes[i];
      emptyEl.reject = putTheOnlyElement(board, emptyEl);
    }

    emptyNodes = emptyNodes.filter((x) => !x.reject);
    // 如果上次循环和这次循环相同，则不需要继续遍历，进入下一阶段
    if (emptyNodes.length == emptyLength) {
      break;
    }
    emptyLength = emptyNodes.length;
  }

  return emptyNodes;
};

var putTheOnlyElement = function (board, emptyEl) {
  var exists = [0, 0, 0, 0, 0, 0, 0, 0, 0];
  var row = emptyEl.row;
  var col = emptyEl.col;
  for (var i = 0; i < 9; i++) {
    // 同一行
    if (board[row][i] != ".") {
      exists[board[row][i] - 1] = 1;
    }
    // 同一列
    if (board[i][col] != ".") {
      exists[board[i][col] - 1] = 1;
    }
  }

  // 3x3遍历
  var r = Math.floor(row / 3) * 3;
  var c = Math.floor(col / 3) * 3;
  for (var i = 0; i < 3; i++) {
    for (var j = 0; j < 3; j++) {
      if (board[r + i][c + j] != ".") {
        exists[board[r + i][c + j] - 1] = 1;
      }
    }
  }
  emptyEl.candidate = [];
  for (var i = 0; i < 9; i++) {
    if (exists[i] == 0) {
      emptyEl.candidate.push(i + 1);
    }
  }

  // 唯一的就直接赋值
  if (emptyEl.candidate.length == 1) {
    board[row][col] = emptyEl.candidate[0].toString();
    return true;
  }
  return false;
};

var printSudoku = function (board) {
  for (var i = 0; i < 9; i++) {
    var str = "";
    for (var j = 0; j < 9; j++) {
      str += board[i][j] + "  ";
    }
    console.log(str);
  }
};

var board = [
  ["5", "3", ".", ".", "7", ".", ".", ".", "."],
  ["6", ".", ".", "1", "9", "5", ".", ".", "."],
  [".", "9", "8", ".", ".", ".", ".", "6", "."],
  ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
  ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
  ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
  [".", "6", ".", ".", ".", ".", "2", "8", "."],
  [".", ".", ".", "4", "1", "9", ".", ".", "5"],
  [".", ".", ".", ".", "8", ".", ".", "7", "9"],
];

board = [
  [".", ".", "9", "7", "4", "8", ".", ".", "."],
  ["7", ".", ".", ".", ".", ".", ".", ".", "."],
  [".", "2", ".", "1", ".", "9", ".", ".", "."],
  [".", ".", "7", ".", ".", ".", "2", "4", "."],
  [".", "6", "4", ".", "1", ".", "5", "9", "."],
  [".", "9", "8", ".", ".", ".", "3", ".", "."],
  [".", ".", ".", "8", ".", "3", ".", "2", "."],
  [".", ".", ".", ".", ".", ".", ".", ".", "6"],
  [".", ".", ".", "2", "7", "5", "9", ".", "."],
];

// Straight Forward Solution Using Backtracking
var solve = function (board) {
  for (var i = 0; i < 9; i++) {
    for (var j = 0; j < 9; j++) {
      if (board[i][j] === ".") {
        for (var c of "123456789") {
          //trial. Try 1 through 9
          if (isValid(board, i, j, c)) {
            board[i][j] = c; //Put c for this cell

            if (solve(board)) {
              return true; //If it's the solution return true
            } else {
              board[i][j] = "."; //Otherwise go back
            }
          }
        }

        return false;
      }
    }
  }
  return true;
};

var isValid = function (board, row, col, c) {
  var blkRow = 3 * Math.floor(row / 3);
  var blkCol = 3 * Math.floor(col / 3);
  for (var i = 0; i < 9; i++) {
    if (board[i][col] === c) return false; //check row
    if (board[row][i] === c) return false; //check column
    var ri = Math.floor(i / 3);
    var ci = i % 3;
    if (board[blkRow + ri][blkCol + ci] === c) return false; //check 3*3 block
  }

  return true;
};

(function () {
  console.log(solve(board));
  printSudoku(board);
})();
