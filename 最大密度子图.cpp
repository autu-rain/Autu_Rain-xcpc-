constexpr int inf = 1E9;
template<class T>
struct MaxFlow {
  struct _Edge {
    int to;
    T cap;
    _Edge(int to, T cap) : to(to), cap(cap) {}
  };

  int n;
  std::vector<_Edge> e;
  std::vector<std::vector<int>> g;
  std::vector<int> cur, h;

  MaxFlow() {}
  MaxFlow(int n) {
    init(n);
  }

  void init(int n) {
    this->n = n;
    e.clear();
    g.assign(n, {});
    cur.resize(n);
    h.resize(n);
  }

  bool bfs(int s, int t) {
    h.assign(n, -1);
    std::queue<int> que;
    h[s] = 0;
    que.push(s);
    while (!que.empty()) {
      const int u = que.front();
      que.pop();
      for (int i : g[u]) {
        auto [v, c] = e[i];
        if (c > 0 && h[v] == -1) {
          h[v] = h[u] + 1;
          if (v == t) {
            return true;
          }
          que.push(v);
        }
      }
    }
    return false;
  }

  T dfs(int u, int t, T f) {
    if (u == t) return f;
    T r = 0;
    for (int &i = cur[u]; i < (int)g[u].size(); ++i) {
      const int j = g[u][i];
      auto [v, c] = e[j];
      if (c > 0 && h[v] == h[u] + 1) {
        auto a = dfs(v, t, std::min(f - r, c));
        if (a <= 0) h[v] = -1;
        e[j].cap -= a;
        e[j ^ 1].cap += a;
        r += a;
        if (r >= f) return f;
      }
    }
    return r;
  }
  void addEdge(int u, int v, T c1, T c2 = T{}) {
    g[u].push_back(e.size());
    e.emplace_back(v, c1);
    g[v].push_back(e.size());
    e.emplace_back(u, c2);
  }

  T flow(int s, int t) {
    T ans = 0;
    while (bfs(s, t)) {
      cur.assign(n, 0);
      ans += dfs(s, t, inf);
    }
    return ans;
  }

  std::vector<bool> minCut() {
    std::vector<bool> c(n);
    for (int i = 0; i < n; i++) {
      c[i] = (h[i] != -1);
    }
    return c;
  }

  struct Edge {
    int from;
    int to;
    T cap;
    T flow;
  };
  std::vector<Edge> edges() {
    std::vector<Edge> a;
    for (int i = 0; i < e.size(); i += 2) {
      Edge x;
      x.from = e[i + 1].to;
      x.to = e[i].to;
      x.cap = e[i].cap + e[i + 1].cap;
      x.flow = e[i + 1].cap;
      a.push_back(x);
    }
    return a;
  }
};

// 最大密度子图(一般都是无向图)
// 最大化 |E| + |V| - g|V|
// 原图的边 + (i -> T, U + 2 * g - E_i - 2 * V_i) + (S -> i, U)
// Max(|E| + |V| - g|V|) = (U * n - c[S, T]) / 2; 
void solve() {
  cin >> n >> m;
  MaxFlow<int> f(n + 2);
  int S = 0, T = n + 1;
  v<int> p(n + 1);
  for (int i = 1; i <= n; i ++ ) {
    cin >> p[i];
    p[i] *= -1;
  }
  v<int> deg(n + 1);
  for (int i = 1; i <= m; i ++ ) {
    int u, v, c;
    cin >> u >> v >> c;
    deg[u] += c, deg[v] += c;
    f.addEdge(u, v, c, c);
  }
  int U = 0;
  for (int i = 1; i <= n; i ++ )
    U = max(U, deg[i] + 2 * p[i]);
  for (int i = 1; i <= n; i ++ ) {
    f.addEdge(S, i, U);
    f.addEdge(i, T, U - 2 * p[i] - deg[i]);
  }
  cout << (U * n - f.flow(S, T)) / 2 << '\n';
}