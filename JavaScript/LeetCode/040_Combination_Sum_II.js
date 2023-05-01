/**
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]

Constraints:
    1 <= candidates.length <= 100
    1 <= candidates[i] <= 50
    1 <= target <= 30
*/

/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum2 = function (candidates, target) {
  // Time Limit Exceeded

  // 用之前的最快的答案，先找出所有符合target的数组
  var result = [];
  var len = candidates.length;

  var permute = function (arr, sum, idx) {
    if (sum === target) {
      // 排序
      arr = arr.sort(function (a, b) {
        return a - b;
      });
      // 判断去重
      if (!result.some((x) => x.toString() === arr.toString())) {
        result.push(arr);
      }
      result.push(arr);
      return;
    }

    for (var i = idx; i < len; i++) {
      var newSum = sum + candidates[i];
      if (newSum <= target) {
        // 这里因为一个数字只能用一次 所以是i+1,不再是 i
        permute(arr.concat([candidates[i]]), newSum, i + 1);
      }
    }
  };
  permute([], 0, 0);

  return result;
};

// Testcase
(function () {
  var testcase = [
    // {
    //   input: [10, 1, 2, 7, 6, 1, 5],
    //   target: 8,
    //   output: [
    //     [1, 1, 6],
    //     [1, 2, 5],
    //     [1, 7],
    //     [2, 6],
    //   ],
    //   temp: [
    //     [1, 2, 5],
    //     [1, 7],
    //     [1, 6, 1],
    //     [2, 6],
    //     [2, 1, 5],
    //     [7, 1],
    //   ],
    // },
    // {
    //   input: [2, 5, 2, 1, 2],
    //   target: 5,
    //   output: [[1, 2, 2], [5]],
    // },
    // { input: [2], target: 1, output: [] },
    // 这个用例会搞死机，要正确退出超时！！！
    {
      input: [
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      ],
      target: 30,
    },
  ];

  testcase.forEach((x) => console.log(combinationSum2(x.input, x.target)));
})();
