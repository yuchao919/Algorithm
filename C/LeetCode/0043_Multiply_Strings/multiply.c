/*
    Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

    Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

    Example 1:

    Input: num1 = "2", num2 = "3"
    Output: "6"

    Example 2:

    Input: num1 = "123", num2 = "456"
    Output: "56088"

    Constraints:

        1 <= num1.length, num2.length <= 200
        num1 and num2 consist of digits only.
        Both num1 and num2 do not contain any leading zero, except the number 0 itself.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *multiply(char *num1, char *num2)
{
    /* 思路：
        就是做一个乘法算数题。
        每一位数相乘，如果有进位则记录进位，把结果放入一个数组里面，最后翻转这个数组
        两个数相乘，得到的数的位数最多可以是这两个位数的和

            89
        x  123
        --------
            27          27
           240         24
           180         18
          1600        16
           900         9
          8000        8
        _________
         10947
    */

    size_t len1 = strlen(num1);
    size_t len2 = strlen(num2);

    // 字符串最后一位是'\0'
    size_t totalLen = len1 + len2 + 1;
    char *result = (char *)malloc(sizeof(char) * (totalLen));
    memset(result, '\0', totalLen);

    if ((len1 == 1 && num1[0] == '0') || (len2 == 1 && num2[0] == '0'))
    {
        result[0] = '0';
        return result;
    }

    // 超过10的进位
    char carry;
    // num1 作为被乘数，num2作为乘数
    for (size_t n2 = 0; n2 < len2; n2++)
    {
        size_t l2 = len2 - 1 - n2;
        carry = 0;
        for (size_t n1 = 0; n1 < len1; n1++)
        {
            size_t n = n1 + n2;
            size_t l1 = len1 - 1 - n1;
            char cur = (num1[l1] - '0') * (num2[l2] - '0') + result[n] + carry;
            result[n] = cur % 10;
            carry = cur / 10;
        }
        // 多余的进位往前累加
        size_t d = len1 + n2;
        while (carry > 0 && d < totalLen)
        {
            result[d] += carry;
            carry = result[d] / 10;
            result[d] = result[d] % 10;
            d++;
        }
    }

    // 判断字符串长度
    for (size_t i = totalLen - 1; i >= 0; i--)
    {
        if (result[i] != '\0')
        {
            totalLen = i + 1;
            break;
        }
    }

    // 将结果中的数字转成字符
    for (size_t i = 0; i < totalLen; i++)
    {
        result[i] += '0';
    }

    //  reverse result的中的字符
    size_t t2 = totalLen / 2;
    for (size_t i = 0; i < t2; i++)
    {
        char tmp = result[totalLen - 1 - i];
        result[totalLen - 1 - i] = result[i];
        result[i] = tmp;
    }

    return result;
}

int main()
{
    // char *num1 = "123";
    // char *num2 = "456";

    // char *num1 = "89";
    // char *num2 = "123";

    // char *num1 = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    // char *num2 = "987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210";

    // char *num1 = "2";
    // char *num2 = "3";

    char *num1 = "0";
    char *num2 = "0";

    char *result = multiply(num1, num2);

    printf("%s\n", result);

    free(result);

    // 提交的时候反复报错，内存越界什么的，经过排查， 确实是 for (size_t i = totalLen - 1; i >= 0; i--) 判断写成了i>0， 导致只有一位数的时候没有正确设置字符串长度

    return 0;
}