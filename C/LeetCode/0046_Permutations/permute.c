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
    int count = 1;
    for (int i = 1; i <= numsSize; i++)
    {
        count = count * i;
    }
    *returnSize = count;
    *returnColumnSizes = (int *)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }

    int **result = (int **)malloc(sizeof(int *) * count);

    // 现在可以得出循环的过程[0,...,0]这里有numsSize列，每一个位都算作numSize进制，
    // 从最后一个位开始，不停地加1，当其等于numSize时上一位+1，直至所有位置都等于[numSize-1]，等同于numSize进制加法
    // 在累加的过程中，如果一个数组没一位各不相等，则属于有效数组，将其值记录到result中
    // 一开始可以是[0,1,2,3...,numSize-1];

    int *indexArr = (int *)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        indexArr[i] = i;
    }

    int cnt = 0;
    int end = numsSize - 1;
    // 判断所有位都变成numSize - 1 就结束
    int isFinish = 0;
    while (isFinish == 0)
    {
        int isValid = 1;
        for (int i = 0; i < numsSize; i++)
        {
            for (int j = i + 1; j < numsSize; j++)
            {
                if (indexArr[i] == indexArr[j])
                {
                    isValid = 0;
                    break;
                }
            }
            if (isValid == 0)
            {
                break;
            }
        }

        if (isValid == 1)
        {
            int *item = (int *)malloc(sizeof(int) * numsSize);
            for (int i = 0; i < numsSize; i++)
            {
                item[i] = nums[indexArr[i]];
            }

            result[cnt++] = item;
        }

        // 末尾一位+1，如果触发进位则上一位再+1，直至到顶
        int cur = end;
        indexArr[cur]++;
        while (cur > 0)
        {
            if (indexArr[cur] == numsSize)
            {
                indexArr[cur] = 0;
                indexArr[cur - 1]++;
            }

            cur--;
        }

        // 默认结束
        isFinish = 1;
        for (int i = 0; i < numsSize; i++)
        {
            if (indexArr[i] < end)
            {
                isFinish = 0;
                break;
            }
        }
    }

    return result;
}

int main()
{
    // int nums[3] = {1, 2, 3};
    // int returnSize;
    // int **returnColumnSizes = (int **)malloc(sizeof(int *) * 2000);

    int nums[] = {1};
    int returnSize;
    int **returnColumnSizes = (int **)malloc(sizeof(int *) * 2000);

    int **result = permute(nums, sizeof(nums) / sizeof(int), &returnSize, returnColumnSizes);

    return 0;
}

// 判断下标数组是否合法
int isValid(int indexArr[], int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (indexArr[i] == indexArr[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

// 下标数组+1
void plus(int indexArr[], int numsSize, int end)
{
    int cur = end;
    indexArr[cur]++;

    while (cur > 0)
    {
        if (indexArr[cur] == numsSize)
        {
            indexArr[cur] = 0;
            indexArr[cur - 1]++;
        }

        cur--;
    }
}

// 是否结束
int isFinish(int indexArr[], int numsSize, int end)
{
    for (int i = 0; i < numsSize; i++)
    {
        if (indexArr[i] < end)
        {
            return 0;
        }
    }

    return 1;
}

// 貌似是说传递 indexArr这个会导致有问题
// Line 207: Char 3: runtime error: load of misaligned address 0xbebebebebebebebe for type 'int', which requires 4 byte alignment [__Serializer__.c]
// 0xbebebebebebebebe: note: pointer points here
// <memory cannot be printed>
int **permute_memory_cannot_be_printed(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 1;
    for (int i = 1; i <= numsSize; i++)
    {
        *returnSize = *returnSize * i;
    }
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < (*returnSize); i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }

    int **result = (int **)malloc(sizeof(int *) * (*returnSize));

    // 现在可以得出循环的过程[0,...,0]这里有numsSize列，每一个位都算作numSize进制，
    // 从最后一个位开始，不停地加1，当其等于numSize时上一位+1，直至所有位置都等于[numSize-1]，等同于numSize进制加法
    // 在累加的过程中，如果一个数组没一位各不相等，则属于有效数组，将其值记录到result中
    // 一开始可以是[0,1,2,3...,numSize-1];

    int *indexArr = (int *)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        indexArr[i] = i;
    }

    int cnt = 0;
    int end = numsSize - 1;
    while (isFinish(indexArr, numsSize, end) == 0)
    {
        if (isValid(indexArr, numsSize) == 1)
        {
            int *item = (int *)malloc(sizeof(int) * numsSize);
            for (int i = 0; i < numsSize; i++)
            {
                item[i] = nums[indexArr[i]];
            }

            result[cnt++] = item;
        }

        plus(indexArr, numsSize, end);
    }

    return result;
}

int **permute_direct(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
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