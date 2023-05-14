/**
Given an unsorted integer array nums, return the smallest missing positive integer.

You must implement an algorithm that runs in O(n) time and uses constant extra space.

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.

Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.

Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.

Constraints:
    1 <= nums.length <= 105
    -231 <= nums[i] <= 231 - 1
*/

#include <stdio.h>

int firstMissingPositive(int *nums, int numsSize)
{
    /**
        改变原数组，第一遍遍历，如果当前下标的数字小于等于numsSize，则对换该数字下标的数字
        原数组中对应下标的数字应该是下标+1，
        再一次遍历数组，把nums[i]不等于i+1的数字即为所得
    */
    for (int i = 0; i < numsSize;)
    {
        // 不在1~numsSize的数字跳过处理
        int n = nums[i];
        if (n < 1 || n > numsSize || nums[n - 1] == n)
        {
            i++;
            continue;
        }

        nums[i] = nums[n - 1];
        nums[n - 1] = n;
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != i + 1)
        {
            return i + 1;
        }
    }

    return numsSize + 1;
}

int main()
{
    int a[][4] = {{3, 4, -1, 1}, {1, 1, 1, 1}};

    for (size_t i = 0; i < 2; i++)
    {
        printf("Expected: %d. Output: %d\n", 2, firstMissingPositive(a[i], 4));
    }

    return 0;
}