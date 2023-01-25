#include <bits/stdc++.h>
using namespace std;

// punctul a)

// Complexitate: O(n * m), unde n = lungimea cuvantului 1, m = lungimea cuvantului 2

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        vector <vector <int>> dp(n + 1, vector <int> (m + 1));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                // If the characters at the current indices match, the length of the LCS at the current indices is equal to the LCS at the previous indices + 1
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                // Otherwise, the length of the LCS at the current indices is the maximum of the LCS at the previous indices
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n][m];
    }
};





// punctul b)

// Complexitate: O(n * m), unde n = lungimea cuvantului 1, m = lungimea cuvantului 2

class Solution2 {
public:
    string shortestCommonSupersequence(string& A, string& B) {
        int i = 0; // index for string A
        int j = 0; // index for string B
        string res; // result string to be returned

        string lcsResult = lcs(A, B); // longest common subsequence of strings A and B
        for (char const& c : lcsResult) {
            // Move the index for string A up until the current character is found
            while (A[i] != c) {
                res += A[i++];
            }
            // Move the index for string B up until the current character is found
            while (B[j] != c) {
                res += B[j++];
            }

            // Add the current character to the result string
            res += c;
            ++i;
            ++j;
        }

        // Add the remaining characters in string A and B to the result string
        return res + A.substr(i) + B.substr(j);
    }


    // Find the longest common subsequence of strings A and B
    string lcs (string& A, string& B) {
        int n = A.size(); // length of string A
        int m = B.size(); // length of string B
        vector <vector <string>> dp(n + 1, vector <string> (m + 1, "")); // matrix to store longest common subsequences

        // For each character in string A and string B
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // If the current characters are the same, update the longest common
                // subsequence for the current indices to include the current character
                if (A[i] == B[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + A[i];
                }

                // Otherwise, update the longest common subsequence for the current
                // indices to the longer of the two possible values
                else {
                    dp[i + 1][j + 1] = dp[i + 1][j].size() > dp[i][j + 1].size()  ?  dp[i + 1][j] : dp[i][j + 1];
                }
            }
        }

        return dp[n][m];
    }
};