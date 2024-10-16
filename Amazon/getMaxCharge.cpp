/* Get Max Charge



A team of engineers at Amazon, using advanced simulation tools, are analyzing a series of interconnected systems, where each system has a charge value represented by charge[i] (which can be positive, negative, or zero).

The engineers have a specialized tool that allows them to perform the following operation: Select a system and remove it, causing the neighboring systems to automatically merge and combine their charge values. If the removed system has neighboring systems with charges x and y directly to its left and right, they will combine to form a new system with charge x + y. No combination will take place if the system is the leftmost or rightmost in the array.

Since this process is computationally expensive, the engineers will simulate the operation using Amazon's advanced tools.

For example, if the system charges are [-3, 1, 4, -1, 5, -9], using the tool on the 4th system (index 3) will result in the new sequence [-3, 1, 9, -9], as the charges from the 3rd and 5th systems also combine to 4 + 5 = 9. If they then use the tool on the 1st system in this new sequence, it will become [1, 9, -9].

Function Description

Complete the function getMaxCharge in the editor below. The function must return the maximum charge that can be obtained.

getMaxCharge has the following parameter:

List charge: a list of integers representing the charge values
Returns

long integer: the maximum charge that can be obtained

*/


#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;
long long getMaxCharge(std::vector<int>& charge) {
        int n = charge.size();
        std::vector<long long> dp(n);
        
        // Base cases
        dp[0] = charge[0];
        if (n > 1) dp[1] = std::max((long long)charge[1], (long long)charge[0] + charge[1]);
        
        // Fill dp table
        for (int i = 2; i < n; i++) {
            dp[i] = std::max({(long long)charge[i], 
                              dp[i-1], 
                              dp[i-2] + charge[i], 
                              (i > 2 ? dp[i-3] + charge[i-1] + charge[i] : 0LL)});
        }
        
        // Return maximum charge
        return *std::max_element(dp.begin(), dp.end());
    }

long long getMaxCharge2(std::vector<int>& charge) {
        int n = charge.size();
        if (n == 0) return 0;
        if (n == 1) return charge[0];
        
        std::vector<long long> dp(n);
        
        // Initialize dp array
        for (int i = 0; i < n; i++) {
            dp[i] = charge[i];
        }
        
        for (int len = n; len > 1; len--) {
            std::vector<long long> new_dp(len - 1);
            for (int i = 0; i < len - 1; i++) {
                new_dp[i] = std::max(dp[i], dp[i+1]);
            }
            dp = new_dp;
        }
        
        return dp[0];
    }  


    long long getMaxCharge3(std::vector<int>& charge) {
        int n = charge.size();
        if (n <= 2) return *std::max_element(charge.begin(), charge.end());

        std::vector<long long> values(charge.begin(), charge.end());
        std::set<std::pair<long long, int>> indexedValues;
        
        for (int i = 0; i < n; ++i) {
            indexedValues.insert({values[i], i});
        }

        std::vector<bool> removed(n, false);
        int remainingCount = n;

        while (remainingCount > 1) {
            auto [minValue, minIndex] = *indexedValues.begin();
            indexedValues.erase(indexedValues.begin());
            removed[minIndex] = true;
            remainingCount--;

            int left = minIndex - 1;
            while (left >= 0 && removed[left]) left--;
            
            int right = minIndex + 1;
            while (right < n && removed[right]) right++;

            if (left >= 0 && right < n) {
                long long sum = values[left] + values[right];
                indexedValues.erase({values[left], left});
                indexedValues.erase({values[right], right});
                indexedValues.insert({sum, left});
                values[left] = sum;
                removed[right] = true;
                remainingCount--;
            }
        }

        return *std::max_element(values.begin(), values.end());
    }

int main() {
    vector<int> test = {-2, 4, 3, -2, 1};
    vector<int> test1 = {-2, 4, 9, 1, -1};
    vector<int> test2 = {-1, 3, 2};

    cout << "res = " << getMaxCharge3(test)<<endl;
    cout << "res1 = " << getMaxCharge3(test1)<<endl;
    cout << "res2 = " << getMaxCharge3(test2)<<endl;
    
    return 0;
}
