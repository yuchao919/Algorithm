/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum = function (candidates, target) {
  // input: [2, 3, 6, 7], target: 7
  // 搞一个堆栈，堆栈变化规律
  // [2,2,2] 先不停的往里灌第一个数字，直至大于target, 退栈一个
  // 再在[2,2,2] 找 input:[3,6,7] target:1，查找到第一个数字就比target大，继续退栈
  // [2,2] 递归栈 [3,6,7] target:3, 返回子数组 [3]
  // 2,2,3
  // 7

  // []
  // i=0,index[0]=0,j=0 => [2]
  // i=1;index[1]=0,j=0 => [2,2]
  // i=2;index[2]=0,j=0 => [2,2,2]
  // [2,2,2] + 2 > target  不再继续入栈，并且出栈一个，继续灌candidate下一个数
  // i-- => 1,index[2]++,j=1 => [2,2] + candidate[j] == target, 记录结果，并且继续出栈
  // i-- => 0,index[1]++,j=1 => [2] + candidate[j] => [2,3]
  // [2,2] + 3 == target => [2,2,3] 进入结果集 但是栈 [2,2] 再退一个
  // i-- => i=0,index[1]++ => j=index[1]=1 => [2] + 3  < target => i++ => [2,3]
  // [2,3] + 3 > target => j=index[1]++=2, [2,6]> target

  /**
   * 先给数组排序，
   * len = candidates.length
   * 每往数组里加一个数
   *    - 目标数组长度最长为 maxNum target / Min(candidates);
   * 再给一个堆栈，记录candidate两个下标 二维数组，[i][j], i < maxNum, j < len
   * 当堆栈之和 + 当前数 < target， 则当前数入栈 i++,j=0 ，
   * 否则不入栈，并且出栈一个 i-1,j++继续尝试加入 candidate[j]
   */
  if (!Array.isArray(candidates) || !candidates.length) {
    return [];
  }

  candidates = candidates.sort((a, b) => a - b);
  var maxNum = Math.floor(target / candidates[0]);
  if (maxNum === 0) {
    return [];
  }
  var len = candidates.length;

  var result = [];
  var stack = [];
  var stackSum = 0;
  // 栈清空的次数，cnt == len的时候结束循环
  var index = [];
  var i = 0;

  for (var j = 0; j < maxNum; j++) {
    index[j] = 0;
  }

  // 初始状态就往前累加
  while (true) {
    if (index[0] === len) {
      // 所有元素都已尝试
      break;
    }

    var num = candidates[index[i]];
    var sum = stackSum + num;
    // 小于target就持续进栈
    if (sum < target) {
      stack.push(num);
      stackSum = sum;
      i++;
    } else {
      // 相等场景就记录答案，并且出栈
      if (sum === target) {
        result.push(stack.concat([num]));
      }

      if (stack.length > 0) {
        var popNum = stack.pop();
        stackSum -= popNum;
        i--;
      }

      index[i]++;
      for (var j = i + 1; j < maxNum; j++) {
        index[j] = index[i];
      }
    }
  }

  return result;
};

/** */
var combinationSum_fastest = function (candidates, target) {
  var result = [];
  var len = candidates.length;
  //
  var permute = (arr, sum, idx) => {
    console.log(arr);
    if (sum === target) {
      result.push(arr);
      return;
    }

    for (var i = idx; i < len; i++) {
      if (sum + candidates[i] <= target) {
        permute(arr.concat(candidates[i]), sum + candidates[i], i);
      }
    }
  };

  permute([], 0, 0);
  return result;

  /*
  递归过程，
   []
   [5]
   [5, 2]
   [3]
   [3, 3]
   [3, 2]
   [3, 2, 2]
   [2]
   [2, 2]
   [2, 2, 2]
   [7]

  

*/
};

//
(function () {
  var testcase = [
    { input: [5, 3, 2, 7], target: 7, output: [[2, 2, 3], [7]] },
    // {
    //   input: [2, 3, 5],
    //   target: 8,
    //   output: [
    //     [2, 2, 2, 2],
    //     [2, 3, 3],
    //     [3, 5],
    //   ],
    // },
    // { input: [2], target: 1, output: [] },
  ];

  testcase.forEach((x) => console.log(combinationSum_fastest(x.input, x.target)));
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

/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum_answer = function (candidates, target) {
  candidates = candidates.sort((a, b) => a - b);

  var result = [];
  var combination = [];
  combine_answer(candidates, target, result, combination, 0);
  return result;
};

var combine_answer = function (candidates, target, result, combination, begin) {
  if (!target) {
    result.push(combination.map((x) => x));
    return;
  }

  for (var i = begin; i != candidates.length && target >= candidates[i]; ++i) {
    combination.push(candidates[i]);
    combine_answer(candidates, target - candidates[i], result, combination, i);
    combination.pop();
  }
};
