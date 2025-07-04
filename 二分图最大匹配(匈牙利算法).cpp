struct BipGraph {
  int n;
  vector<vector<int>> e;
  vector<int> match;
  vector<bool> st;
  BipGraph(int n) {
    init(n);
  }
  void init(int n) {
    e.resize(n + 1);
    match.assign(n + 1, 0);
  }
  void add(int u, int v) {
    e[u].push_back(v);
  }
  bool find(int u) {
    for (auto v : e[u]) {
      if (!st[v]) {
        st[v] = true;
        if (!match[v] || find(match[v])) {
          match[v] = u;
          return true;
        }
      }
    }
    return false;
  }
};