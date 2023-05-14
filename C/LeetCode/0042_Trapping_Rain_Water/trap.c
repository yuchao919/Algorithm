/**
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:

https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9

Constraints:

    n == height.length
    1 <= n <= 2 * 104
    0 <= height[i] <= 105

*/

#include <stdio.h>

int trap(int *height, int heightSize)
{
    /*
        解题思路：
        初始化head=0，tail=length-1；
        p=head，q=0，q自增，累加height[q]-height[p], 如果height[q]>=height[p]，p=q，直至q==tail；
        到最后p如果不等于tail，则再从tail往head遍历，即head=length-1，tail=p；q=p，q自减，累加height[q]-height[p], 直至q==tail，
        最后p==tail的时候结束颠倒循环
    */

    if (heightSize < 3)
    {
        return 0;
    }

    int head = 0, tail = heightSize - 1;
    int p = head, q = head;
    short plus = 1;
    int result = 0;

    int sum = 0;

    while (p != tail)
    {
        int flag = 0;
        if (plus == 1)
        {
            q++;
            // 穿头了，翻转
            if (q > tail)
            {
                flag = 1;
            }
        }
        else
        {
            q--;
            // 穿头了，翻转
            if (q < tail)
            {
                flag = 1;
            }
        }
        // 翻转
        if (flag == 1)
        {
            plus ^= 1;
            head = tail;
            tail = p;
            q = head;
            p = head;
            sum = 0;
            continue;
        }

        if (height[q] < height[p])
        {
            sum += height[p] - height[q];
            continue;
        }

        result += sum;
        sum = 0;
        p = q;
    }

    return result;
}

int main()
{

    int height1[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int output = 6;

    printf("height1, output=%d\n", trap(height1, (int)(sizeof(height1) / sizeof(int))));

    int height2[] = {4, 2, 0, 3, 2, 5};
    int output2 = 9;

    printf("height2, output=%d\n", trap(height2, (int)(sizeof(height2) / sizeof(int))));

    return 0;
}