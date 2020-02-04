#
# @lc app=leetcode id=7 lang=python3
#
# [7] Reverse Integer
#
# https://leetcode.com/problems/reverse-integer/description/
#
# algorithms
# Easy (25.62%)
# Likes:    2798
# Dislikes: 4380
# Total Accepted:    933.8K
# Total Submissions: 3.6M
# Testcase Example:  '123'
#
# Given a 32-bit signed integer, reverse digits of an integer.
# 
# Example 1:
# 
# 
# Input: 123
# Output: 321
# 
# 
# Example 2:
# 
# 
# Input: -123
# Output: -321
# 
# 
# Example 3:
# 
# 
# Input: 120
# Output: 21
# 
# 
# Note:
# Assume we are dealing with an environment which could only store integers
# within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose
# of this problem, assume that your function returns 0 when the reversed
# integer overflows.
# 
#

# @lc code=start
class Solution:
    def reverse(self, x: int) -> int:
        ans =""
        x_list = []
        if(x <= -2**31 or x>=2**31 -1 ):
            return 0
        else : 
            if(x < 0):
                x = abs(x)
                x_str = str(x)
                for i in range(len(x_str)):
                    x_list.append(x_str[i])
                x_list.reverse()
                for i in x_list:
                    ans += i
                if int(ans) * -1 <= -2**31:
                    return 0
                else:
                    return int(ans) * -1
            else : 
                x_str = str(x)
                for i in range(len(x_str)):
                    x_list.append(x_str[i])
                x_list.reverse()
                for i in x_list:
                    ans += i
                if int(ans) >= 2**31-1:
                    return 0
                else:
                    return int(ans)


# @lc code=end

