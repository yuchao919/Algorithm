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
  var result = [];
  var len = candidates.length;

  // 必须先排序，后续过程中保证重复的数组只会记录一次
  candidates = candidates.sort((a, b) => a - b);

  var traverse = function (arr, remain, start) {
    if (remain === 0) {
      result.push(arr);
      return;
    }

    for (var i = start; i < len; i++) {
      // 挪到最上面速度会加快很多，已经超过target就不需要判断了
      if (remain < candidates[i]) {
        break;
      }
      // 在每次递归过程中，因为i>start 限制，所以重复的元素只会进入集合一次，保证排除重复元素后，后续进来的结果集唯一
      if (i > start && candidates[i] === candidates[i - 1]) {
        continue;
      }

      traverse(arr.concat(candidates[i]), remain - candidates[i], i + 1);
    }
  };

  traverse([], target, 0);

  return result;
};

// Testcase
(function () {
  var testcase = [
    {
      input: [10, 1, 2, 7, 6, 1, 5],
      target: 8,
      output: [
        [1, 1, 6],
        [1, 2, 5],
        [1, 7],
        [2, 6],
      ],
      temp: [
        [1, 2, 5],
        [1, 7],
        [1, 6, 1],
        [2, 6],
        [2, 1, 5],
        [7, 1],
      ],
    },
    {
      input: [2, 5, 2, 1, 2],
      target: 5,
      output: [[1, 2, 2], [5]],
    },
    { input: [2], target: 1, output: [] },
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

// 全是1 ，target 30的用例会超时
var combinationSum2_TimeLimitExceed = function (candidates, target) {
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
