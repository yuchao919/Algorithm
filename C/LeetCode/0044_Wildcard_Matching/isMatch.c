/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

    '?' Matches any single character.
    '*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

Constraints:

    0 <= s.length, p.length <= 2000
    s contains only lowercase English letters.
    p contains only lowercase English letters, '?' or '*'.

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char *s, char *p)
{
    int slen = strlen(s);
    int plen = strlen(p);

    if (slen == 0 && plen == 0)
    {
        return true;
    }

    if (slen == 0 || plen == 0)
    {
        return false;
    }

    if (plen == 1 && p[0] == '*')
    {
        return true;
    }

    // 这里主要是* 难以处理，当p[i]是*时，s继续前进，当前进的字符等于s[i+n]==p[i+1]时，则命中，如果s[i+n+j]!=p[i+1+j]时，p回退到p[i]状态

    // 场景罗列
    // 1. p前面没有*，s[i]==p[pi]，i,pi都+1

    // 记录*出现在p的位置
    int pi = 0, ps = -1;
    // 两者同步前进
    for (int i = 0; i < slen; i++)
    {
        if (p[pi] == '\0')
        {
            return false;
        }
        // 匹配成功则前进
        if (s[i] == p[pi] || p[pi] == '?')
        {
            pi++;
            continue;
        }

        // 匹配失败，如果是*
        if (p[pi] == '*')
        {
            // 加速处理，如果p[plen-1]=='*' ，前面只要匹配住了，后面不需要处理
            if (pi == plen - 1)
            {
                return true;
            }

            ps = pi;
            // 继续前进
            pi++;
            continue;
        }

        // p没有出现过*，这时候绝对失败
        if (ps == -1)
        {
            return false;
        }
        // 否则pi退回到ps+1状态
        else
        {
            pi = ps + 1;
        }
    }

    return pi == plen;
}

typedef struct Item
{
    char *s;
    char *p;
} Item;

int main()
{
    Item itemList[] = {
        // {"aa", "bb"},
        // {"cb", "?a"},
        // {"aca", "?a"},
        {"adceb", "*a*b"}};
    int length = sizeof(itemList) / (sizeof(Item));
    for (size_t i = 0; i < length; i++)
    {
        Item item1 = itemList[i];
        printf("s:%s, p:%s,  isMatch: %s\n", item1.s, item1.p, isMatch(item1.s, item1.p) == 1 ? "true" : "false");
        ;
    }

    printf("\n");
}