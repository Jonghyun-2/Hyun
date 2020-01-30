#
# @lc app=leetcode id=1 lang=python3
#
# [1] Two Sum
#

# @lc code=start
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for Idx0 in range(len(nums)):
            for Idx1 in range(len(nums)):
                if Idx0 != Idx1:
                    ans = nums[Idx0] + nums[Idx1]
                    if ans == target:
                        return [Idx0,Idx1]

# @lc code=end


