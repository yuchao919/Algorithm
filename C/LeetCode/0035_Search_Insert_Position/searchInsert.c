/**
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:

Input: nums = [1,3,5,6], target = 2
Output: 1

Example 3:

Input: nums = [1,3,5,6], target = 7
Output: 4


Constraints:

    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums contains distinct values sorted in ascending order.
    -104 <= target <= 104
*/

#include <stdio.h>

int searchInsert(int *nums, int numsSize, int target)
{
    if (numsSize == 0)
    {
        return 0;
    }

    if (numsSize == 1)
    {
        return target > nums[0] ? 1 : 0;
    }

    int low = 0, high = numsSize - 1, mid;
    while (low <= high)
    {
        // 取中间位置
        mid = (low + high) / 2;
        if (nums[mid] == target)
            // 查找成功返回所在的位置
            return mid;
        else if (nums[mid] > target)
        {
            // 从前部分查找
            high = mid - 1;
        }
        else
        {
            // 从后部分查找
            low = mid + 1;
        }
    }

    // if (high < 0)
    // {
    //     return 0;
    // }
    // if (low > max)
    // {
    //     return numsSize;
    // }

    // 从这里可以看出，low始终返回可以插入 本属于这个不重复数组中的位置
    return low;
}

void main()
{
    int result1[3] = {1, 3, 5};
    int target1 = 4;

    printf("Insert: %d\n", searchInsert(result1, 3, target1));

    printf("\n\n----------\n\n");

    int result[][4] = {
        {1, 3, 5, 6},
        {1, 3, 5, 6},
        {1, 3, 5, 6}};
    int target[] = {
        5,
        2,
        7};

    for (size_t i = 0; i < 3; i++)
    {
        printf("Insert: %d\n", searchInsert(result[i], 4, target[i]));
    }

    printf("\n\n----------\n\n");

    int result2[][5] = {
        {1, 3, 5, 7, 9},
        {1, 3, 5, 7, 9},
        {1, 3, 5, 7, 9},
        {1, 3, 5, 7, 9},
        {1, 3, 5, 7, 9}};
    int target2[] = {
        0,
        1,
        4,
        9,
        10};

    for (size_t i = 0; i < sizeof(result2) / (sizeof(int) * 5); i++)
    {
        printf("Insert: %d\n", searchInsert(result2[i], 5, target2[i]));
    }
}