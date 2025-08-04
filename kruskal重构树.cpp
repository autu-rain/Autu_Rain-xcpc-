constexpr int N = 18, inf = -1E9;
template<class Cmp = less<int>>
struct KruskalRTree {
    struct Node {
        int u, v, w;
        bool operator<(const Node &t) {
            Cmp cmp;
            return cmp(w, t.w);
        }
    };

    vector<Node> e;
    vector<int> val;
    vector<vector<int>> dp;
    int n;
    HLD g;
    DSU d;

    void init(int n_) {
        n = n_;
        d.init(n);
        g.init(2 * n - 1);
        val.assign(2 * n - 1, -1);
        dp.assign(N, vector<int>(2 * n - 1, inf));
    }

    KruskalRTree(int n_) {
        init(n_);
    }

    void addEdge(int u, int v, int w) {
        e.push_back({u, v, w});
    }

    i64 kruskal() {
        sort(e.begin(), e.end());
        int cnt = n;
        i64 res = 0;
        for (auto [u, v, w] : e) {
            int pu = d.find(u), pv = d.find(v);
            if (pu != pv) {
                g.addEdge(pu, cnt);
                g.addEdge(pv, cnt);
                val[cnt] = w;
                res += w;
                cnt++;
            }
        }
        return res;
    }

    i64 calc(i64 x, i64 y) {
        return max(x, y);
    }

    void bfs() {
        g.work(2 * n - 2);
        vector<int> st(2 * n - 1);
        queue<int> q;
        q.push(2 * n - 2);
        st[2 * n - 2] = 1;
        while (q.size()) {
            int u = q.front();
            q.pop();

            for (auto v : g.adj[u]) {
                if (!st[v]) {
                    st[v] = 1;
                    int p = g.jump(v, 1);
                    dp[0][v] = val[p];
                    for (int i = 1; i < N; i++) {
                        p = g.jump(v, 1 << i - 1);
                        if (p != -1) {
                            dp[i][v] = calc(dp[i - 1][v], dp[i - 1][p]);
                        }
                    }
                }
            }
        }
    }

    int jump(int u, i64 k) {
        for (int i = N - 1; i >= 0; i--) {
            int p = g.jump(u, 1 << i);
            if (p != -1 && dp[i][u] <= k) {
                u = p;
            }
        }
        return u;
    }

    int lca(int u, int v) {
        return g.lca(u, v);
    }
};