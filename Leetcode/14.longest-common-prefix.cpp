/*
 * @lc app=leetcode id=14 lang=cpp
 *
 * [14] Longest Common Prefix
 *
 * https://leetcode.com/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (34.61%)
 * Likes:    1969
 * Dislikes: 1645
 * Total Accepted:    630.7K
 * Total Submissions: 1.8M
 * Testcase Example:  '["flower","flow","flight"]'
 *
 * Write a function to find the longest common prefix string amongst an array
 * of strings.
 * 
 * If there is no common prefix, return an empty string "".
 * 
 * Example 1:
 * 
 * 
 * Input: ["flower","flow","flight"]
 * Output: "fl"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 * 
 * 
 * Note:
 * 
 * All given inputs are in lowercase letters a-z.
 * 
 */

// @lc code=start
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    
    //int strLen = strs[0].size();
public:
    string longestCommonPrefix(vector<string>& strs) {
    if(strs.size() >0){
        string ans = "";
        string letters = strs[0];
        bool end = false;
            for(int j =0 ;j< strs[0].size(); j++){
                char letter = letters[j];
                for (int i =0; i < strs.size();i++){
                    string temp = strs[i];

                    // j 번째의 글자가 다를때
                    if(letter != temp[j]){
                        end = true;
                        break;
                    }
                }
                if(end == true){
                    return ans;
                }
                ans += letter;
            }
            return ans;
        }
        else{return "";}
    }
};


//for(int i=1; i < strs.size(); i++){
        //    if(strs[i].size() < strLen){
        //        strLen = strs[i].size();
        //    }
// @lc code=end

