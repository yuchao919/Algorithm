/**
You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].

Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at nums[i], you can jump to any nums[i + j] where:

    0 <= j <= nums[i] and
    i + j < n

Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n - 1].

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: nums = [2,3,0,1,4]
Output: 2

Constraints:

    1 <= nums.length <= 104
    0 <= nums[i] <= 1000
    It's guaranteed that you can reach nums[n - 1].
*/

/**
1. 假定可以一次就跳到结尾，那么就有一个数满足nums[i]>=n-1-i的，i越小越好
2.

*/
#include <stdio.h>

int findSmallest(int *nums, int end)
{
    int min = end;
    int p = end;
    while (p > 0)
    {
        p--;
        if (nums[p] >= (end - p))
        {
            min = p;
        }
    }
    return min;
}

int jump(int *nums, int numsSize)
{
    if (numsSize == 0 || numsSize == 1)
    {
        return 0;
    }

    int i = 1;
    int end = numsSize - 1;
    while (i < numsSize)
    {
        int p = findSmallest(nums, end);
        if (p == 0)
        {
            return i;
        }
        end = p;
        i++;
    }

    return numsSize;
}

int main()
{
    int nums[] = {2, 3, 1, 1, 4};

    // int p = findSmallest(nums, 4);

    int times = jump(nums, 5);

    printf("%d\n", times);

    return 0;
}
