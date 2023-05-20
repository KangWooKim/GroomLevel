#include<bits/stdc++.h>
using namespace std;

const int mod = 1000000009;
const int maxN = 101;
const int maxD = 1000;
int dp[maxN][maxD][2];

string n;
int d;

void initialize() {
    for (int i = 0; i < maxN; i++) {
        for (int j = 0; j < maxD; j++) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }
}

int calculate(int pos, int sum, bool tight) {
    if (sum > d) return 0;
    if (pos == n.size()) {
        return sum == d;
    }
    if (dp[pos][sum][tight] != -1) {
        return dp[pos][sum][tight];
    }

    int res = 0;
    int ub = tight ? (n[pos] - '0') : 9;

    for (int i = 0; i <= ub; i++) {
        if (sum + i > d) {
            break;
        }
        res = (res + calculate(pos + 1, sum + i, tight & (i == ub))) % mod;
    }

    dp[pos][sum][tight] = res;
    return res;
}

int main() {
    cin >> n >> d;
    
    initialize();
    int answer = calculate(0, 0, true);

    cout << answer << "\n";
    return 0;
}
