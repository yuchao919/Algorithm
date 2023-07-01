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

#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 1;
    for (int i = 1; i <= numsSize; i++)
    {
        *returnSize = *returnSize * i;
    }

    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));

    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }

    int **result = malloc(sizeof(int *) * (*returnSize));
    int i = 0;
    for (int n1 = 0; numsSize >= 1 && n1 < numsSize; n1++)
    {
        if (numsSize == 1)
        {
            int *item = malloc(sizeof(int) * numsSize);
            item[0] = nums[n1];
            result[i++] = item;
        }
        for (int n2 = 0; numsSize >= 2 && n2 < numsSize; n2++)
        {
            if (n2 == n1)
            {
                continue;
            }
            if (numsSize == 2)
            {
                int *item = malloc(sizeof(int) * numsSize);
                item[0] = nums[n1];
                item[1] = nums[n2];
                result[i++] = item;
            }
            for (int n3 = 0; numsSize >= 3 && n3 < numsSize; n3++)
            {
                if (n3 == n2 || n3 == n1)
                {
                    continue;
                }
                if (numsSize == 3)
                {
                    int *item = malloc(sizeof(int) * numsSize);
                    item[0] = nums[n1];
                    item[1] = nums[n2];
                    item[2] = nums[n3];
                    result[i++] = item;
                }
                for (int n4 = 0; numsSize >= 4 && n4 < numsSize; n4++)
                {
                    if (n4 == n3 || n4 == n2 || n4 == n1)
                    {
                        continue;
                    }
                    if (numsSize == 4)
                    {
                        int *item = malloc(sizeof(int) * numsSize);
                        item[0] = nums[n1];
                        item[1] = nums[n2];
                        item[2] = nums[n3];
                        item[3] = nums[n4];
                        result[i++] = item;
                    }
                    for (int n5 = 0; numsSize >= 5 && n5 < numsSize; n5++)
                    {
                        if (n5 == n4 || n5 == n3 || n5 == n2 || n5 == n1)
                        {
                            continue;
                        }
                        if (numsSize == 5)
                        {
                            int *item = malloc(sizeof(int) * numsSize);
                            item[0] = nums[n1];
                            item[1] = nums[n2];
                            item[2] = nums[n3];
                            item[3] = nums[n4];
                            item[4] = nums[n5];
                            result[i++] = item;
                        }
                        for (int n6 = 0; numsSize >= 6 && n6 < numsSize; n6++)
                        {
                            if (n6 == n5 || n6 == n4 || n6 == n3 || n6 == n2 || n6 == n1)
                            {
                                continue;
                            }
                            if (numsSize == 6)
                            {
                                int *item = malloc(sizeof(int) * numsSize);
                                item[0] = nums[n1];
                                item[1] = nums[n2];
                                item[2] = nums[n3];
                                item[3] = nums[n4];
                                item[4] = nums[n5];
                                item[5] = nums[n6];
                                result[i++] = item;
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

int main()
{
    int nums[3] = {1, 2, 3};
    int returnSize;
    int **returnColumnSizes = (int **)malloc(sizeof(int *) * 2000);

    int **result = permute(nums, 3, &returnSize, returnColumnSizes);

    return 0;
}

// var len = nums.length;

// var indexes = [];

// for (var n1 = 0; n1 < len; n1++) {
//     if (len === 1) {
//         indexes.push([n1]);
//     }
//     for (var n2 = 0; n2 < len; n2++) {
//         if (n2 === n1) {
//             continue;
//         }
//         if (len === 2) {
//             indexes.push([n1, n2]);
//         }
//         for (var n3 = 0; n3 < len; n3++) {
//             if (n3 === n2 || n3 === n1) {
//                 continue;
//             }
//             if (len === 3) {
//                 indexes.push([n1, n2, n3]);
//             }
//             for (var n4 = 0; n4 < len; n4++) {
//                 if (n4 === n3 || n4 === n2 || n4 === n1) {
//                     continue;
//                 }
//                 if (len === 4) {
//                     indexes.push([n1, n2, n3, n4]);
//                 }
//                 for (var n5 = 0; n5 < len; n5++) {
//                     if (n5 === n4 || n5 === n3 || n5 === n2 || n5 === n1) {
//                         continue;
//                     }
//                     if (len === 5) {
//                         indexes.push([n1, n2, n3, n4, n5]);
//                     }
//                     for (var n6 = 0; n6 < len; n6++) {
//                         if (n6 === n5 || n6 === n4 || n6 === n3 || n6 === n2 || n6 === n1) {
//                             continue;
//                         }
//                         if (len === 6) {
//                             indexes.push([n1, n2, n3, n4, n5, n6]);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// var result = [];
// for (var item of indexes) {
//     var data = [];
//     for (var i of item) {
//         data.push(nums[i]);
//     }
//     result.push(data);
// }

// return result;