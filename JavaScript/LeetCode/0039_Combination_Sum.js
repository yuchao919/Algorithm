/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum = function (candidates, target) {
  // 先给数组排序
  candidates = candidates.sort((a, b) => a - b);
  // input: [2, 3, 6, 7], target: 7
  // 搞一个堆栈，堆栈变化规律
  // [2,2,2,2] 先不停的往里灌第一个数字，直至大于target, 退栈一个
  // 再在[2,2,2] 找 input:[3,6,7] target:1，查找到第一个数字就比target大，继续退栈
  // [2,2] 递归栈 [3,6,7] target:3, 返回子数组 [3]
  //
  var result = [];
  var combination = [];
  combine(candidates, target, result, combination, 0);
  return result;
};

var combine = function (candidates, target, result, combination, begin) {
  if (!target) {
    result.push(combination.map((x) => x));
    return;
  }

  for (var i = begin; i != candidates.length && target >= candidates[i]; ++i) {
    combination.push(candidates[i]);
    combine(candidates, target - candidates[i], result, combination, i);
    combination.pop();
  }
};

(function () {
  var testcase = [
    { input: [2, 3, 6, 7], target: 7, output: [[2, 2, 3], [7]] },
    {
      input: [2, 3, 5],
      target: 8,
      output: [
        [2, 2, 2, 2],
        [2, 3, 3],
        [3, 5],
      ],
    },
    { input: [2], target: 1, output: [] },
  ];

  testcase.forEach((x) => console.log(combinationSum(x.input, x.target)));
})();

// function a() {
//   var result = [];
//   var stack = [];
//   var stackSum = 0;
//   //
//   var head = 0;
//   var tail = 0;
//   var sum = 0;

//   for (; candidates[head] < target; head++) {
//     var num = candidates[head];
//     while (true) {
//       if (stackSum < target) {
//         stack.push(num);
//         stackSum += num;
//         continue;
//       } else if (stackSum === target) {
//         result.push(stack.map((x) => x));
//         stack.pop();
//       } else if (stackSum > target) {
//         stack.pop();
//       }
//     }
//   }
//   return result;
// }
