#include<bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vector<int>>
#define vb vector<bool>
#define vvb vector<vector<bool>>

void display(vi &dp)
{
    for (int ele : dp)
        cout << ele << " ";
    cout << endl;
}

void display2D(vvi &dp)
{
    for (vi ar : dp)
    {
        for (int ele : ar)
            cout << ele << " ";
        cout << endl;
    }
    cout << endl;
}

int fibo_01(int n, vi& dp){ //memoization

    if(n <= 1){
        dp[n] = n;
        return n;
    }

    if(dp[n] != 0){
        return dp[n];
    }

    return dp[n] = fibo_01(n - 1, dp) + fibo_01(n - 2, dp);
}

int fibo_02(int n, vi& dp){ //tabulation

    for(int i = 0; i < n + 1; i++){
        if(i <= 1){
            dp[i] = i;
            continue;
        }

        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int mazePath_HVD_01(int sr, int sc, int er, int ec, vvi& dp){
    if(sr == er && sc == ec){
        dp[sr][sc] = 1;
        return 1;
    }

    int count = 0;

    if(dp[sr][sc] != 0){
        return dp[sr][sc];
    }
    if(er == ec && dp[sc][sr] != 0){
        return dp[sc][sr];
    }

    if(sr + 1 <= er){
        count += mazePath_HVD_01(sr + 1, sc, er, ec, dp);
    }

    if(sc + 1 <= ec){
        count += mazePath_HVD_01(sr, sc + 1, er, ec, dp);
    }

    if(sr + 1 <= er && sc + 1 <= ec){
        count += mazePath_HVD_01(sr + 1, sc + 1, er, ec, dp);
    }

    dp[sr][sc] = count;
    if(er == ec)
        dp[sc][sr] = count;

    return count;
}

int mazePath_HVD_02(int sr, int sc, int er, int ec, vvi& dp){
    for(int i = er; i >= 0; i--){
        for(int j = ec; j >= 0; j--){

            if(i == er && j == ec){
                dp[i][j] = 1;
                continue;
            }

            int count = 0;

            if(i + 1 <= er){
                dp[i][j] += dp[i + 1][j];
            }

            if(j + 1 <= ec){
                dp[i][j] += dp[i][j + 1];
            }

            if(i + 1 <= er && j + 1 <= ec){
                dp[i][j] += dp[i + 1][j + 1];
            }   
        }
    }
    return dp[0][0];
}   

int mazePathJump_01(int sr, int sc, int er, int ec, vvi& dp){

    if(sr == er && sc == ec){
        dp[sr][sc] = 1;
        return 1;
    }

    if(dp[sr][sc] != 0){
        return dp[sr][sc];
    }

    int count = 0;

    for(int jump = 1; sr + jump <= er; jump++){
        count += mazePathJump_01(sr + jump, sc, er, ec, dp);
    }

    for(int jump = 1; sc + jump <= ec; jump++){
        count += mazePathJump_01(sr, sc + jump, er, ec, dp);
    }

    for(int jump = 1; sr + jump <= er && sc + jump <= ec; jump++){
        count += mazePathJump_01(sr + jump, sc + jump, er, ec, dp);
    }

    dp[sr][sc] = count;

    return count;
}

int mazePathJump_02(int sr, int sc, int er, int ec, vvi& dp){

    for(int i = er; i >= 0; i--){
        for(int j = ec; j >= 0; j--){

            if(i == er && j == ec){
                dp[i][j] = 1;
                continue;
            }

            
            for(int jump = 1; i + jump <= er; jump++){
                dp[i][j] += dp[i + jump][j];
            }

            for(int jump = 1; j + jump <= ec; jump++){
                dp[i][j] += dp[i][j + jump];

            }

            for(int jump = 1; i + jump <= er && j + jump <= ec; jump++){
                dp[i][j] += dp[i + jump][j + jump];
            }
        }
    }
    return dp[0][0];
}

int boardPath_01(int sp, int tar, vi& dp){
    
    if(sp == tar){
        dp[sp] = 1;
        return 1;
    }

    if(dp[sp] != 0){
        return dp[sp];
    }

    int count = 0;

    for(int i = 1; i <= 6; i++){
        if(sp + i <= tar){
            count += boardPath_01(sp + i, tar, dp);
        }
    }

    dp[sp] = count;
    return count;
}

int boardPath_02(int sp, int tar, vi& dp){

    for(int i = tar; i >= sp; i--){
        if(i == tar){
            dp[i] = 1;
            continue;
        }

        for(int j = 1; j <=6; j++){
            if(i + j <= tar)
                dp[i] += dp[i + j];
        }
    }
    return dp[sp];
}

int boardPathOutcomes_01(int sp, int tar, vi& outcomes, vi& dp){
    if(sp == tar){
        dp[sp] = 1;
        return 1;
    }

    if(dp[sp] != 0){
        return dp[sp];
    }

    int count = 0;
    for(int i = 0; i < outcomes.size(); i++){
        if(sp + outcomes[i] <= tar){
            count += boardPathOutcomes_01(sp + outcomes[i], tar, outcomes, dp);
        }
    }

    dp[sp] = count;
    return count;
}

int boardPathOutcomes_02(int sp, int tar, vi& outcomes, vi& dp){

    for(int i = tar; i >= sp; i--){
        if(i == tar){
            dp[i] = 1;
            continue;
        }

        for(int ele : outcomes){
            if(i + ele <= tar){
                dp[i] += dp[i + ele];
            }
        }
    }
    return dp[sp];
}

//leetcode 70
int climbStairs(int n) {    //just like fibonacci
    if(n <= 1){
        return n;
    }

    int a = 1, b = 1, c;
    for(int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int minCost = INT_MAX;

int helper(vi& cost){
    
    vi dp(cost.size(), 0);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for(int i = 2; i < cost.size(); i++){
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }

    return dp[cost.size()];
}

//leetcode 746
int minCostClimbingStairs(vector<int>& cost) {

    vector<int> dp(cost.size() + 1);
    cost.push_back(0);
    helper(cost);
}

//leetcode 64
int minPathSum(vector<vector<int>>& grid) {

    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
    dp[0][0] = grid[0][0];

    for(int j = 1; j < grid.size(); j++){
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    for(int i = 1; i < grid[0].size(); i++){
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    for(int i = 1; i < grid.size(); i++){
        for(int j = 1; j < grid[0].size(); j++){
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
        }
    }
    return dp[grid.size() - 1][grid[0].size() - 1];
}

//set2...................................................................

int singleOrPairUp_01(int n, vi& dp){

    if(n == 1 || n == 2){
        dp[n] = n;
        return n;
    }
    
    if(dp[n] != 0){
        return dp[n];
    }

    int singleWays = singleOrPairUp_01(n - 1, dp);
    int pairUpWays = (n - 1) * singleOrPairUp_01(n - 2, dp);

    int totalWays = singleWays + pairUpWays;
    return dp[n] = totalWays;
}

int singleOrPairUp_02(int n, vi& dp){

    for(int i = 1; i <= n; i++){
        if(i == 1 || i == 2){
            dp[i] = i;
            continue;
        }

        dp[i] = dp[i - 1] + (i - 1) * dp[i - 2];
    }
    return dp[n];
}

int singleOrPairUp_03(int n){

    if(n == 1 || n == 2){
        return n;
    }

    int a = 1, b = 2, ans = 0;

    for(int i = 3; i <= n; i++){
        ans = b + (i - 1) * a;
        a = b;
        b = ans;
    }
    return ans;
}

int minJump_01(int idx, vector<int>& arr, vector<int>& dp){

    if(idx == arr.size() - 1){
        return 0;
    }

    if(dp[idx] != 0){
        return dp[idx];
    }

    int minAns = INT_MAX;

    for(int jump = 1; jump <= arr[idx] && idx + jump < arr.size(); jump++){
        int minJump = minJump_01(idx + jump, arr, dp);
        if(minJump + 1 < minAns){
            minAns = minJump + 1;
        }
    }
    
    return dp[idx] = minAns;
}

int minJump_02(int idx, vi& arr, vi& dp){

    int n = arr.size();
    dp[n - 1] = 0;

    for(int i = n - 2; i >= 0; i--){

        int minAns = INT_MAX;
        for(int jump = 1; jump <= arr[idx] && idx + jump < arr.size(); jump++){
            int minJump = dp[idx + jump];
            if(minAns != INT_MAX && minJump + 1 < minAns){
                minAns = minJump + 1;
            }
        }
        dp[i] = minAns;
    }
    return dp[0];
}

int goldMine_01(vvi& arr, vvi& dp){
    
    for(int i = 0; i < arr.size(); i++){
        dp[i][0] = arr[i][0];
    }

    for(int j = 1; j < arr[0].size(); j++){
        for(int i = 0; i < arr.size(); i++){ 
            dp[i][j] = max((i - 1 < 0)? 0 : dp[i - 1][j - 1], max(dp[i][j - 1], (i + 1 >= arr.size())? 0 : dp[i + 1][j - 1])) + arr[i][j];
        }
    }

    int j = dp[0].size() - 1;
    int ans = -1;
    
    for(int i = 0; i < dp.size(); i++){
        ans = max(ans, dp[i][j]);
    }

    return ans;
}

void goldMine(){
    vvi arr =  {{10, 33, 13, 15},
                  {22, 21, 04, 1},
                  {5, 0, 2, 3},
                  {0, 6, 14, 2}};

    vvi dp(arr.size(), vi(arr[0].size(), 0));

    cout<<goldMine_01(arr, dp)<<endl;

    display2D(dp);
}

int maxSquare = -1;

int maxSquareOf1s(int r, int c, vvi& arr, vvi& dp){

    if(r == arr.size() || c == arr[0].size()){
        return 0;
    }

    if(dp[r][c] != -1){
        return dp[r][c];
    }

    int right = maxSquareOf1s(r, c + 1, arr, dp);
    int diag = maxSquareOf1s(r + 1, c + 1, arr, dp);
    int down = maxSquareOf1s(r + 1, c, arr, dp);

    int minPossibleSquare = 0;
    if(arr[r][c] == 1)
        minPossibleSquare = min(right, min(diag, down)) + 1;

    if(minPossibleSquare > maxSquare){
        maxSquare = minPossibleSquare;
    }

    dp[r][c] = minPossibleSquare;
    return minPossibleSquare;
}

int maxSquareOf1s_DP(vvi& arr, vvi& dp){

    for(int i = arr.size() - 1; i >= 0; i--){
        for(int j = arr[0].size() - 1; j >= 0; j--){

            if(arr[i][j] == 1)
                dp[i][j] = min(dp[i][j + 1], min(dp[i + 1][j + 1], dp[i + 1][j])) + 1;
            else
                dp[i][j] = 0;
            
            if(dp[i][j] > maxSquare){
                maxSquare = dp[i][j];
            }
        }
    }
    return maxSquare;

}

void maxSizeSquare1s(){

    vvi arr = {{0, 1, 1, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 0}, {1, 1, 1, 1, 1,1}, {0, 0, 0, 0, 0}};
    vvi dp(arr.size() + 1, vi(arr[0].size() + 1, 0));

    // maxSquareOf1s(0, 0, arr, dp);
    // cout<<maxSquare<<endl;

    cout<<maxSquareOf1s_DP(arr, dp)<<endl;

    display2D(dp);
}

int tileFloor(int n, int m, vi& dp){

    if(n == m){
        dp[n] = 2;
        return 2;
    }

    if(n == 0 || n < m){
        dp[n] = 1;
        return 1;
    }

    if(dp[n] != 0){
        return dp[n]; 
    }

    int hor = 0, ver = 0;
    if(n - 1 >= 0)
        hor = tileFloor(n - 1, m, dp);
    
    if(n - m >= 0)
        ver = tileFloor(n - m, m, dp);

    int totalWays = hor + ver;

    dp[n] = totalWays;
    return totalWays;
}

int tileFloor_DP(int n, int m, vi& dp){

    for(int i = 0; i <= n; i++){
        if(i < m){
            dp[i] = 1;
            continue;
        }
        else if(i == m){    //already handled below as when i = m : dp[m - 1] + d[0] -> 1 + 1 -> 2
            dp[i] = 2;
            continue;
        }

        dp[i] = dp[i - 1] + dp[i - m];
    }
    return dp[n];
}

//target Type.....................................................

int coinChangePermutation(vi& arr, int tar, vi& dp){

    if(tar == 0){
        return dp[tar] = 1;
    }

    if(dp[tar] != 0){
        return dp[tar];
    }

    int count = 0;
    for(int i = 0; i < arr.size(); i++){
        if(tar - arr[i] >= 0){
            count += coinChangePermutation(arr, tar - arr[i], dp);
        }
    }

    dp[tar] = count;
    return count;
}

int coinChangePermutation_DP(vi& arr, int tar, vi& dp){

    dp[0] = 1;

    for(int i = 1; i <= tar; i++){
        for(int j = 0; j < arr.size(); j++){

            if(i - arr[j] >= 0){
                dp[i] += dp[i - arr[j]];
            }
        }
    }
    return dp[tar];
}

int coinChangeCombination_DP(int tar, vi& arr, vi& dp){

    dp[0] = 1;

    for(int j = 0; j < arr.size(); j++){
        for(int i = 1; i <= tar; i++){
            
            if(i - arr[j] >= 0){
                dp[i] += dp[i - arr[j]];
            }
        }
    }
    return dp[tar];

}

//leetcode 322

int minCoinsHeight(vi& arr, int tar, vi& dp){
    
    if(tar == 0){
        return 0;
    }

    if(dp[tar] != 0){
        return dp[tar];
    }

    int minHeight = INT_MAX;

    for(int i = 0; i < arr.size(); i++){
        if(tar - arr[i] >= 0){
            int height = minCoinsHeight(arr, tar - arr[i], dp);
            if(height + 1 < minHeight){
                minHeight = height + 1;
            }
        }
    }

    dp[tar] = minHeight;
    return minHeight;
}

int minCoinsHeight_DP(int tar, vi& arr, vi& dp){

    dp[0] = 0;

    for(int i = 1; i <= tar; i++){
        for(int j = 0; j < arr.size(); j++){

            if(i - arr[j] >= 0)
                dp[i] = min(dp[i], dp[i - arr[j]] + 1);
        }
    }
    return dp[tar] == INT_MAX ? -1 : dp[tar];
}

int targetCoins_01(int tar, int idx, vi& arr, vvi& dp){ //actually it is combination with no repetition
    
    if(tar == 0 || idx < 0){
        if(tar == 0){
            return 1;
        }
        return 0;
    }

    if(dp[idx][tar] != 0){
        return dp[idx][tar];
    }

    int count = 0;
    
    if(tar - arr[idx] >= 0){
        count += targetCoins_01(tar - arr[idx], idx - 1, arr, dp);
    }
    count += targetCoins_01(tar, idx - 1, arr, dp);
    
    dp[idx][tar] = count;
    return count;
}

int targetCoins_02(int tar, vi& arr, vvi& dp){

    dp[0][0] = 1;

    for(int i = 1; i < arr.size(); i++){
        for(int j = 0; j <= tar; j++){
            
            if(j - arr[i] >= 0){    //agar main aata hu to
                dp[i][j] += dp[i - 1][j - arr[i]];
            }

            dp[i][j] += dp[i - 1][j];   //agar main nhi aata hu to
        }
    }
    return dp[arr.size() - 1][tar];
}

int knapsack_01(vi& cost, vi& weight, int w, int idx, vvi& dp){

    if(idx == weight.size()){
        dp[idx][w] = 0;
        return 0;
    }

    if(dp[idx][w] != 0){
        return dp[idx][w];
    }

    int inc = 0, non_inc = 0;

    if(w - weight[idx] >= 0){
        inc = cost[idx] + knapsack_01(cost, weight, w - weight[idx], idx + 1 ,dp);
    }
    non_inc = knapsack_01(cost, weight, w, idx + 1, dp);

    return dp[idx][w] = max(inc, non_inc);
}

int knapsack_02(vi& cost, vi& weight, int w, vvi& dp){

    for(int i = cost.size() - 1; i >= 0; i--){
        for(int j = w; j >= 0; j--){

            int inc = 0, non_inc = 0;
            if(j - weight[i] >= 0){
                inc = cost[i] + dp[i + 1][j - weight[i]];
            }
            non_inc = dp[i + 1][j];
            
            dp[i][j] = max(inc, non_inc);
        }
    }
    return dp[0][w];
}

int unbounded_knapsack(vi& cost, vi& weight, int w){

    vector<pair<int, int>> ratio;
    for(int i = 0; i < weight.size(); i++){
        ratio.push_back({cost[i] / weight[i], i});
    }

    sort(ratio.begin(), ratio.end());

    int maxCost = 0, i = ratio.size() - 1;
    while (i >= 0){
        int idx = ratio[i].second;
        if(weight[idx] <= w){
            maxCost += cost[idx];
            w -= weight[idx];
        }
        else{
            i--;
        }
    }
    return maxCost;
}

int unbounded_knapsack_01(vi& cost, vi& weight, int w, vi& dp){

    dp[0] = 0;

    for(int i = 0; i <= w; i++){
        for(int j = 0; j < weight.size(); j++){
            
            if(i - weight[j] >= 0){
                dp[i] = max(dp[i], dp[i - weight[j]] + cost[j]);
            }
        }
    }
    return dp[w];
}

//string set...........................................................

vvb isPallindromeSubstring(string str){

    vvb dp(str.size(), vb(str.size(), true));

    for(int gap = 0; gap < str.size(); gap++){

        for(int i = 0, j = gap; j < str.size(); i++, j++){

            if(gap == 0){
                dp[i][j] = true;
            }
            else if(str[i] == str[j]){
                if(dp[i + 1][j - 1] == true){
                    dp[i][j] = true;
                }
            }
            else{
                dp[i][j] = false;
            }
        }
    }
    return dp;
}

int longestPallindromicSubstring(string str, vvi& dp){

    vvb isPali = isPallindromeSubstring(str);

    for(int gap = 0; gap < str.size(); gap++){

        for(int i = 0, j = gap; j < str.size(); i++, j++){

            if(gap == 0){
                dp[i][j] = 1;
            }
            else if(str[i] == str[j] && gap == 1){
                dp[i][j] = 2;
            }
            else if(str[i] == str[j] && isPali[i + 1][j - 1]){
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else{
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][str.size() - 1];
}

int longestPallindromicSubsequence(string str, vvi& dp){
    
    for(int gap = 0; gap < str.size(); gap++){

        for(int i = 0, j = gap; j < str.size(); i++, j++){

            if(gap == 0){
                dp[i][j] = 1;
            }
            else if(str[i] == str[j]){
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else{
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][str.size() - 1];
}

int countPallindromicSubsequence(string str, vvi& dp){

    for(int gap = 0; gap < str.size(); gap++){
        
        for(int i = 0, j = gap; j < str.size(); i++, j++){

            if(gap == 0){
                dp[i][j] = 1;
            }
            else if(str[i] == str[j]){  
                dp[i][j] = dp[i + 1][j - 1]  + 1;   //beech ke pallindromic subseq + 1 for the end chararter() 
                dp[i][j] += dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]; // when one character is included from first and last at a time.
            }
            else{
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1]; - dp[i + 1][j - 1];
            }
        }
    }
}

//LIS set

int LIS_max = 0;
int LIS_Rec(vi& arr, int ei){

    if(ei == 0){
        return 1;
    }

    int max_ = 1;
    for(int i = ei - 1; i >=0; i--){
        
        int recAns = LIS_Rec(arr, i);
        if(arr[ei] > arr[i]){
            LIS_max = max(LIS_max, recAns + 1);
            max_ = max(max_, recAns + 1);
        }
    }
    return max_;
}

vector<int> LIS_dp(vi& arr){

    vector<int> dp(arr.size(), 1);

    dp[0] = 1;
    int max_ = 1;
    for(int i = 1; i < arr.size(); i++){

        for(int j = 0; j < i; j++){ // har ek j cell uss tak ka maximum increasing subsequence store krke apne pass rakhta hai.

            if(arr[i] > arr[j]){    //agar main khud usse bada hun to length increase ho jaayegi 1 se
                dp[i] = max(dp[i], dp[j] + 1);
            }
            
            max_= max(max_, dp[i]);
        }
    }

    cout << max_ << endl;

    return dp;
}

vector<int> LDS_dp(vi& arr){

    vector<int> dp(arr.size(), 1);

    int max_ = 1;
    for(int i = arr.size() - 2; i >= 0; i--){

        for(int j = i + 1; j < arr.size(); j++){

            if(arr[i] > arr[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }

            max_ = max(max_, dp[i]);
        }
    }
    cout << max_ << endl;
    return dp;
}

vector<int> LBS_dp(vi& arr){

    vi LIS = LIS_dp(arr);
    vi LDS = LDS_dp(arr);
    vi LBS(arr.size(), 1);

    int max_ = 1;
    for(int i = 0; i < arr.size(); i++){
        LBS[i] = LIS[i] + LDS[i] - 1;
        max_ = max(max_, LBS[i]);
    }

    cout << max_ << endl;
}

void set1(){

    int n = 10;
    // int m = 3;
    vi dp(n + 1, 0);
    // vvi dp(n, vi(m, 0));

    // cout<<fibo_01(n, dp)<<endl;
    // cout<<fibo_02(n, dp)<<endl;

    // cout<<mazePath_HVD_01(0, 0, n - 1, m - 1, dp)<<endl;
    // cout<<mazePath_HVD_02(0, 0, n - 1, m - 1, dp)<<endl;

    // cout<<mazePathJump_01(0, 0, n - 1, m - 1, dp)<<endl;
    // display2D(dp);
    // cout<<mazePathJump_02(0, 0, n - 1, m - 1, dp)<<endl;

    // cout<<boardPath_01(0, n, dp)<<endl;
    // cout<<boardPath_02(0, n, dp)<<endl;

    vi outcomes = {2, 3, 5, 7};
    // cout<<boardPathOutcomes_01(0, n, outcomes, dp)<<endl;
    cout<<boardPathOutcomes_02(0, n, outcomes, dp)<<endl;

    display(dp);
}

void set2(){

    // int n = 4;
    // vi dp(n + 1, 0);

    // cout<<singleOrPairUp_01(n, dp)<<endl;
    // cout<<singleOrPairUp_02(n, dp)<<endl;
    // cout<<singleOrPairUp_03(n)<<endl;

    // goldMine();
    // maxSizeSquare1s();

    int n = 70, m = 8;
    vi dp(n + 1, 0);
    // cout<<tileFloor(n, m, dp)<<endl;
    cout<<tileFloor_DP(n, m, dp)<<endl;

    display(dp);
}

void targetType(){

    vi arr = {0, 2, 3, 5, 7};
    int tar = 10;

    // vi dp(tar + 1, 0);
    // vvi dp(arr.size(), vi(tar + 1, 0));

    // cout << coinChangePermutation(arr, tar, dp) << endl;
    // cout << coinChangePermutation_DP(arr, tar, dp) << endl;
    // cout << coinChangeCombination_DP(tar, arr, dp) << endl;

    // cout<<targetCoins_01(tar, arr.size() - 1, arr, dp)<<endl;
    // cout<<targetCoins_02(tar, arr, dp)<<endl;

    vector<int> cost = {10, 15, 20, 55};
	vector<int> weight = {2, 3, 5, 11};
	int w = 14;
    // vvi dp(cost.size() + 1, vi(w + 1, 0));
    vi dp(w + 1 , 0);

    // cout<<knapsack_01(cost, weight, w, 0, dp)<<endl;
    // cout<<knapsack_02(cost, weight, w, dp)<<endl;

    // cout<<unbounded_knapsack(cost, weight, w)<<endl;
    cout << unbounded_knapsack_01(cost, weight, w, dp) << endl;

    // display2D(dp);
}

void stringSet(){

    // string str = "abccbdefeg";

    // isPallindromeSubstring(str);

    string str = "geeksforgeeks";
    int n = str.length();
    vvi dp(n, vi(n, 0));

    // cout << longestPallindromicSubstring(str, dp) << endl;
    cout << longestPallindromicSubsequence(str, dp) << endl;

    display2D(dp);
}

vector<int> maximumSumSubsequence(vector<int>& arr){

    vi dp(arr.size(), 0);
    dp[0] = arr[0];

    int max_ = 1;

    for(int i = 1; i < arr.size(); i++){
        
        dp[i] = arr[i];
        for(int j = i + 1; j < arr.size(); j++){

            if(arr[j] > arr[i]){
                dp[i] = max(dp[i], dp[j] + arr[i]);
            }
        }
        max_ = max(max_, dp[i]);
    }
    return dp;
}

//minimum deletions to make a sequence sorted in increasing order 
int minimumDeletion(vi& arr){

    vector<int> LIS = LIS_dp(arr);  //for equal values add >= sign in LIS condition
    int max_ = 1;

    for(int ele : LIS){
        max_ = max(max_, ele);
    }

    int min_deletion = arr.size() - max_;
    return min_deletion;
}

//cut Type
// int MCM_memo()

void LIS_Set(){
    
    vector<int> arr = {50, 3, 10, 7, 40, 1};
    vi dp(arr.size(), 0);

    // LIS_Rec(arr, arr.size() - 1);
    // cout << LIS_max << endl;
    
    // LIS_dp(arr);
    // LDS_dp(arr);
    // LBS_dp(arr);

    // display(dp);
}

void cutType(){

}

int main(){

    // set1();
    // set2();
    // targetType();
    // stringSet();
    // LIS_Set();
    cutType();

    return 0;
}