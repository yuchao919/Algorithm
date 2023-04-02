/*
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

    countAndSay(1) = "1"
    countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then converted into a different digit string.

To determine how you "say" a digit string, split it into the minimal number of substrings such that each substring contains exactly one unique digit. Then for each substring, say the number of digits, then say the digit. Finally, concatenate every said digit.

Example 1:

Input: n = 1
Output: "1"
Explanation: This is the base case.

Example 2:

Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1's = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"

*/
/*
1
1 1
2 1
1 2 1 1
1 1 1 2 2 1
3 1 2 2 1 1
1 3 1 1 2 2 2 1
1 1 1 3 2 1 3 2 1 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 第一版，malloc很费时间哦
char *countAndSay_Ver1(int n)
{
    char *str = (char *)malloc(2 * sizeof(char));
    str[0] = '1';
    str[1] = '\0';
    int i = 2;
    while (i <= n)
    {
        int index = 0;
        char c = str[0];
        int count = 0;
        int sLength = strlen(str);
        char *result = (char *)malloc(1 * sizeof(char));
        result[0] = '\0';
        for (int j = 0; j <= sLength; j++)
        {
            // 相同就计数，否则到下一个数字
            if (str[j] == c)
            {
                count++;
            }
            else
            {
                // 扩充字符串
                int resultLen = strlen(result);
                char *newResult = (char *)malloc((i == 1 ? 3 : resultLen + 3) * sizeof(char));
                strcpy(newResult, result);
                newResult[resultLen] = count + '0';
                newResult[resultLen + 1] = str[j - 1];
                newResult[resultLen + 2] = '\0';
                free(result);
                result = newResult;
                // 重置计数字符
                c = str[j];
                count = 1;
            }
        }
        free(str);
        str = result;
        i++;
    }

    return str;
}

char *countAndSay(int n)
{
    char *str = (char *)malloc(2 * sizeof(char));
    str[0] = '1';
    str[1] = '\0';
    printf("n1:%s\n", str);
    int i = 2;
    while (i <= n)
    {
        int index = 0;
        char c = str[0];
        int count = 0;
        int sLength = strlen(str);
        char *result = (char *)malloc((sLength * 2 + 1) * sizeof(char));
        result[0] = '\0';
        int k = 0;
        for (int j = 0; j <= sLength; j++)
        {
            // 相同就计数，否则到下一个数字
            if (str[j] == c)
            {
                count++;
            }
            else
            {
                // 扩充字符串
                result[k++] = count + '0';
                result[k++] = str[j - 1];
                // 重置计数字符
                c = str[j];
                count = 1;
            }
        }
        result[k] = '\0';
        free(str);
        str = result;
        printf("n%d:%s\n", i, str);
        printf("n%d:%lu\n", i, strlen(str));
        i++;
    }

    return str;
}

int main()
{
    printf("\n\n%s\n", countAndSay(30));
    // char *strPtr = "1211";

    // printf("'%s'.length = %lu\n", str, strlen(str));
    // printf("'%s'.length = %lu\n", strPtr, strlen(strPtr));
    return 0;
}