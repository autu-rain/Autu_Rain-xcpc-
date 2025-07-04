bool is_ok(int x, int y) {
  return x == y;
}

int digit_dp(int l, int r) {
  string low = to_string(l), high = to_string(r);
  int n = high.size(), diff = n - low.size();
  unordered_map<i64, int> st; // 状态记录
  auto dfs = [&](auto && self, int i, int m, int s, bool lim_l, bool lim_h) -> int {
    if (i == n) return is_ok(m, s);
    i64 msk = (i64)m << 32ll | i << 16ll | s; // 位运算, 字符串叠加(用空格分隔)(会很慢, 尽量用位运算), 离散化
    if (!lim_l && !lim_h && st.count(msk)) return st[msk];
    int lo = lim_l && i >= diff ? low[i - diff] - '0' : 0;
    int hi = lim_h ? high[i] - '0' : 9;
    int res = 0, d = lo;
    if (lim_l && i < diff) {
      res = self(self, i + 1, 1, 0, 1, 0);
      d = 1;
    }
    for (; d <= hi; d ++ )
      res += self(self, i + 1, m * d, s + d, lim_l && d == lo, lim_h && d == hi);
    if (!lim_l && !lim_h) return st[msk] = res;
    return res;
  };
  return dfs(dfs, 0, 1, 0, 1, 1);
}