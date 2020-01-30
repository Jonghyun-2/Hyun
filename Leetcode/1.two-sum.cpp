/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution {
public:
    int ans;
    vector<int> output;
    vector<int> twoSum(vector<int>& nums, int target) {
        for(int i =0; i < nums.size(); i++){
            for(int j =0; j < nums.size(); j++){
                if(i != j){
                    ans = nums[i] + nums[j];
                    if(ans == target){
                        output = {i,j};
                        return output ;
                    }
                }
            }
        }    
    return output ;
    }
};
// @lc code=end

