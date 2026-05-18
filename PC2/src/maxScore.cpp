#include <iostream>
#include <vector>
#include "deque.h"
#include "maxScore.h"

namespace algorithm {

int maxScore(const std::vector<int>& nums, int k) {

    if (nums.empty() || k <= 0) {
        return 0;
    }

    int n = nums.size();
    std::vector<int> dp(n);
    
    dp[0] = nums[0];
    
    ods::Deque<int> dq;
    dq.addBack(0);
    
    for (int i = 1; i < n; ++i) {
        while (!dq.empty() && dq.front() < i - k) {
            dq.removeFront();
        }
        
        dp[i] = dp[dq.front()] + nums[i];
        
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.removeBack();
        }
        
        dq.addBack(i);
    }
    return dp[n - 1];
    }

int maxScoreSlow(const std::vector<int>& nums, int k){ // Complejidad O([k-1]n)
    if (nums.empty() || k <= 0) {
        return 0;
    }

    int n = nums.size();
    std::vector<int> dp(n);
    
    dp[0] = nums[0];

    for (int i = 1; i < n; i++)
    {
        int izq = std::max(0, i-k);

        int best = dp[izq];

        for (int j = izq+1; j < i; j++)
        {
            best = std::max(best, dp[j]);
        }
        dp[i] = best + nums[i];
    }
    return dp[n-1];
    
    }
}
