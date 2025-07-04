struct DSU {
  std::vector<int> f, siz, d;

  DSU() {}
  DSU(int n) {
    init(n);
  }

  void init(int n) {
    f.resize(n);
    std::iota(f.begin(), f.end(), 0);
    d.assign(n, 0);
    siz.assign(n, 1);
  }

  int find(int x) {
    if (f[x] != x) {
      int t = find(f[x]);
      d[x] ^= d[f[x]];
      f[x] = t;
    }
    return f[x];
  }

  bool same(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return !(d[x] ^ d[y]);
  }

  //t == 1不同类, t == 0 同一类
  bool merge(int x, int y, int t) {
    int px = find(x);
    int py = find(y);
    if (px == py) return (d[x] ^ d[y]) == t;
    siz[px] += siz[py];
    f[py] = px;
    d[py] = d[x] ^ d[y] ^ t;
    return true;
  }

  int size(int x) {
    return siz[find(x)];
  }
};