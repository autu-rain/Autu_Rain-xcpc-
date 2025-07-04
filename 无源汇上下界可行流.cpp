constexpr int inf = 1E9;
template<class T>
struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    
    int n;
    std::vector<_Edge> e, l;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    
    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        e.clear();
        l.clear();
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
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < (int)g[u].size(); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c, T d) {
        g[u].push_back(e.size());
        e.emplace_back(v, d - c);
        l.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
        l.emplace_back(-1, -1);
    }
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
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
        T down;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            x.down = l[i].cap;
            a.push_back(x);
        }
        return a;
    }
};

void solve() {
  cin >> n >> m;
  MaxFlow<int> mf(n + 2);
  int s = 0, t = n + 1;
  v<int> dflow(n + 1);
  while (m -- ) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    mf.addEdge(a, b, c, d);
    dflow[b] += c, dflow[a] -= c;
  }
  int tot = 0;
  for (int i = 1; i <= n; i ++ )
    if (dflow[i] > 0) mf.addEdge(s, i, 0, dflow[i]), tot += dflow[i];
    else if (dflow[i] < 0) mf.addEdge(i, t, dflow[i], 0);
  if (tot != mf.flow(s, t)) return cout << "NO\n", void();
  cout << "YES\n";
  auto v  = mf.edges();
  for (auto x : v) 
    if (x.from != 0 && x.to != n + 1)
      cout << x.flow + x.down << '\n';
}