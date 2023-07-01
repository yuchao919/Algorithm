/**
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:

Input: nums = [1]
Output: [[1]]


Constraints:

    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of nums are unique.
*/

/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var permute = function (nums) {
    /**
     * 就是求一个数组的全排列
     * 可以先将全排列的index求出来，再转化为实际数组
     * 举例来说，n的全排列数组，我们可以写一个n重循环。n2!=n1,n3!=n2&&n3!=n1,以此类推，暴力求出index全排列
     */

    var len = nums.length;

    var indexes = [];

    for (var n1 = 0; n1 < len; n1++) {
        if (len === 1) {
            indexes.push([n1]);
        }
        for (var n2 = 0; n2 < len; n2++) {
            if (n2 === n1) {
                continue;
            }
            if (len === 2) {
                indexes.push([n1, n2]);
            }
            for (var n3 = 0; n3 < len; n3++) {
                if (n3 === n2 || n3 === n1) {
                    continue;
                }
                if (len === 3) {
                    indexes.push([n1, n2, n3]);
                }
                for (var n4 = 0; n4 < len; n4++) {
                    if (n4 === n3 || n4 === n2 || n4 === n1) {
                        continue;
                    }
                    if (len === 4) {
                        indexes.push([n1, n2, n3, n4]);
                    }
                    for (var n5 = 0; n5 < len; n5++) {
                        if (n5 === n4 || n5 === n3 || n5 === n2 || n5 === n1) {
                            continue;
                        }
                        if (len === 5) {
                            indexes.push([n1, n2, n3, n4, n5]);
                        }
                        for (var n6 = 0; n6 < len; n6++) {
                            if (n6 === n5 || n6 === n4 || n6 === n3 || n6 === n2 || n6 === n1) {
                                continue;
                            }
                            if (len === 6) {
                                indexes.push([n1, n2, n3, n4, n5, n6]);
                            }
                        }
                    }
                }
            }
        }
    }

    var result = [];
    for (var item of indexes) {
        var data = [];
        for (var i of item) {
            data.push(nums[i]);
        }
        result.push(data);
    }

    return result;
};