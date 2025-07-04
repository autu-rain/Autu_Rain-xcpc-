struct SegmentTreeGraph;

struct SegmentTree {
    int n;
    SegmentTreeGraph &stg;
    SegmentTree(int n_, SegmentTreeGraph &stg_) : n(n_), stg(stg_) {}
    virtual void build(int p, int l, int r) = 0;
    virtual void modify(int p, int l, int r, int x, int y, int k, int w) = 0;
};

struct SegmentTreeGraph {
    int n, idx;
    std::vector<std::vector<std::pair<int, int>>> adj;
    struct SegmentTreeIn : public SegmentTree {
        std::vector<int> num, pos;
        SegmentTreeIn(int n_, SegmentTreeGraph &stg_) : SegmentTree(n_, stg_) {
            num.assign(n_, 0);
            pos.assign(n_ << 2, 0);
        }
        void build(int p, int l, int r) override {
            pos[p] = stg.idx ++;
            if (r - l == 1) {
                num[l] = pos[p];
                return;
            }
            int m = l + r >> 1;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            stg.add(pos[2 * p], pos[p], 0);
            stg.add(pos[2 * p + 1], pos[p], 0);
        }
        void build() {
            build(1, 0, n);
        }
        void modify(int p, int l, int r, int x, int y, int k, int w) {
            if (l >= y || r <= x) {
                return;
            }
            if (l >= x && r <= y) {
                stg.add(pos[p], k, w);
                return;
            }
            int m = l + r >> 1;
            if (x < m) {
                modify(2 * p, l, m, x, y, k, w);
            }
            if (y >= m) {
                modify(2 * p + 1, m, r, x, y, k, w);
            }
        }
        void modify(int x, int y, int k, int w) {
            modify(1, 0, n, x, y, k, w);
        }
    } in_sg;
    struct SegmentTreeOut : public SegmentTree {
        std::vector<int> num, pos;
        SegmentTreeOut(int n_, SegmentTreeGraph &stg_) : SegmentTree(n_, stg_) {
            num.assign(n_, 0);
            pos.assign(n_ << 2, 0);
        }
        void build(int p, int l, int r) override {
            pos[p] = stg.idx ++;
            if (r - l == 1) {
                num[l] = pos[p];
                return;
            }
            int m = l + r >> 1;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            stg.add(pos[p], pos[2 * p], 0);
            stg.add(pos[p], pos[2 * p + 1], 0);
        }
        void build() {
            build(1, 0, n);
        }
        void modify(int p, int l, int r, int x, int y, int k, int w) {
            if (l >= y || r <= x) {
                return;
            }
            if (l >= x && r <= y) {
                stg.add(k, pos[p], w);
                return;
            }
            int m = l + r >> 1;
            if (x < m) {
                modify(2 * p, l, m, x, y, k, w);
            }
            if (y >= m) {
                modify(2 * p + 1, m, r, x, y, k, w);
            }
        }
        void modify(int x, int y, int k, int w) {
            modify(1, 0, n, x, y, k, w);
        }
    } out_sg;
    SegmentTreeGraph(int n_) : n(n_), idx(0), in_sg(n_, *this), out_sg(n_, *this) {
        adj.assign((1 << std::__lg(n)) * 2, {});
        in_sg.build();
        out_sg.build();
        for (int i = 0; i < n; i ++ ) {
            add(out_sg.num[i], in_sg.num[i], 0);
            add(in_sg.num[i], out_sg.num[i], 0);
        }
    }
    void add(int u, int v, int w) {
        if (u >= adj.size()) {
            adj.resize(2 * u + 1);
        }
        adj[u].emplace_back(v, w);
    }
    void insert(int l1, int r1, int l2, int r2, int w = 1) {
        int S = idx ++;
        in_sg.modify(l1, r1, S, 0);
        out_sg.modify(l2, r2, S, w);
    }
    std::vector<std::vector<std::pair<int, int>>> graph() {
        return adj;
    }
};