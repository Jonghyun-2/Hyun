#
# @lc app=leetcode id=9 lang=python3
#
# [9] Palindrome Number
#
# https://leetcode.com/problems/palindrome-number/description/
#
# algorithms
# Easy (46.41%)
# Likes:    1880
# Dislikes: 1464
# Total Accepted:    786.1K
# Total Submissions: 1.7M
# Testcase Example:  '121'
#
# Determine whether an integer is a palindrome. An integer is a palindrome when
# it reads the same backward as forward.
# 
# Example 1:
# 
# 
# Input: 121
# Output: true
# 
# 
# Example 2:
# 
# 
# Input: -121
# Output: false
# Explanation: From left to right, it reads -121. From right to left, it
# becomes 121-. Therefore it is not a palindrome.
# 
# 
# Example 3:
# 
# 
# Input: 10
# Output: false
# Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
# 
# 
# Follow up:
# 
# Coud you solve it without converting the integer to a string?
# 
#

# @lc code=start
class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        else :
            strX = str(x)
            halfLen = 1+int(len(strX) / 2)
            for i in range(halfLen):
                if strX[i] != strX[-i-1]:
                    return False
            return True

        
# @lc code=end

