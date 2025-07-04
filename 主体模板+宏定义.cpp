#include <bits/stdc++.h>
using namespace std;

#define int long long
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define v vector
#define printv(a, x) for (int i = x; i < a.size(); i ++ ) \
                      cout << a[i] << " \n"[i == (int)a.size() - 1]
#define printvv(a, x) for (int i = x; i < a.size(); i ++ ) \
                      for (int j = x; j < a[i].size(); j ++ ) \
                        cout << a[i][j] << " \n"[j == (int)a[i].size() - 1]
#define all(x) (x).begin(), (x).end()
#define readv(a, n, x) for (int i = x; i < n + x; i ++ ) \
                          cin >> a[i]
#define readvv(a, n, m, x) for (int i = x; i < n + x; i ++ ) \
                            for (int j = x; j < m + x; j ++ ) \
                              cin >> a[i][j]
#define gt greater
#define pq priority_queue
#define umap unordered_map
#define uset unordered_set         
#define lbound(a, l, r, x) lower_bound(a.begin() + l, a.begin() + r + 1, x) - a.begin()
#define ubound(a, l, r, x) upper_bound(a.begin() + l, a.begin() + r + 1, x) - a.begin()
template <typename T>
void base_dbg(const std::string& key, const T& value) {
    std::cerr << key << " = " << value;
}
template <typename... Args>
void dbg_args(const std::string& keys, Args... args) {
  size_t pos{ 0 }; ((base_dbg(keys.substr(pos, keys.find(',', pos) - pos),args),
      pos = keys.find(',', pos) + 1),...);
}
#define dbg(...) { \
    std::cerr << ""; \
    dbg_args(#__VA_ARGS__, __VA_ARGS__); \
    std::cerr << '\n'; \
}
template <typename T>
void base_print(const T& value) {
    std::cout << value << ' ';
}
template <typename... Args>
void print_args(Args... args) {
  size_t pos{ 0 }; ((base_print(args)),...);
}
#define print(...) { \
    std::cout << ""; \
    print_args(__VA_ARGS__); \
    std::cout << '\n'; \
}

typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;
typedef pair<int, int> pII;
typedef tuple<int, int, int> pIII;

std::mt19937 rnd(std::chrono::steady_clock().now().time_since_epoch().count());

struct PII {
  int x, y;
  bool operator< (const PII &tmp) const {
    return x < tmp.x;
  }
};

const int N = 2e5 + 10, M = 1e6 + 10, mod = 1e9 + 7, 
inf = 0x3f3f3f3f3f3f3f3f, base = 131;
int t, n, m, q, k;
int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

void solve() {
} 

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
  cin >> t;
  // t = 1;
  while (t -- ) solve();
  return 0;
}