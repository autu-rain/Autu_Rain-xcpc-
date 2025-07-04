#include<bits/stdc++.h>
#define int long long
using namespace std;

const int p = 998244353, N = 12, M = 110;
int nxt[1 << N][26], f[2][1 << N], ans[M];
string s;

void solve()
{
    int n, m; 
    cin >> n >> m;
    cin >> s;
    s = ' ' + s;
    int st = 1 << n;
    for(int i = 0, tmp[N], res[N]; i < st; i ++ ) {
        res[0] = tmp[0] = 0;
        for(int j = 1, k = i; j <= n; j ++, k >>= 1) 
            tmp[j] = tmp[j - 1] + (k & 1);
        for(int k = 0, num; k < 26; k ++ ) {
            num = 0;
            for(int j = 1; j <= n; j ++ ) 
                res[j] = (s[j] == k + 'a') ? tmp[j - 1] + 1 : max(tmp[j], res[j - 1]), 
                num += (1 << (j - 1)) * (res[j] - res[j - 1]);
            nxt[i][k] = num;
        }
    }
    memset(f,0,sizeof f);
    f[0][0] = 1;
    for(int i = 0; i < m; i ++ ) {
        for(int j = 0; j < st; j ++ ) 
            f[(i & 1) ^ 1][j] = 0;
        for(int j = 0; j < st; j ++ ) 
            for(int k = 0; k < 26; k ++ ) 
                (f[(i & 1) ^ 1][nxt[j][k]] += f[i & 1][j]) %= p;
    }
    for(int i = 0; i <= n; i ++ ) ans[i]=0;
    for(int i = 0; i < st; i ++ ) 
        (ans[__builtin_popcount(i)] += f[m & 1][i]) %= p;
    for(int i = 0; i <= n; i ++ ) 
        cout << ans[i] << " \n"[i == n];
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    while (t -- ) solve();
    return 0;
}
