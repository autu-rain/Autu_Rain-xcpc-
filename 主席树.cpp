constexpr int inf = 1E9;
template <class Info>
struct PersistentSegmentTree {
    int n, idx;
    vector<Info> info;
    vector<int> root;
    void init (int n_) {
        idx = 0;
        n = n_;
        info.assign(n_ << 5, Info{});
        root.assign(n_ + 1, 0);
    }
    PersistentSegmentTree (int n_) {
        init (n_);
    }
    void insert (int p, int &q, int l, int r, int x, const Info &v) {
        q = ++ idx;
        info[q] = info[p];
        if (r - l == 1) {
            info[q].apply (x, v);
            return;
        }
        int m = l + r >> 1;
        if (x < m) insert(info[p].l, info[q].l, l, m, x, v);
        else insert(info[p].r, info[q].r, m, r, x, v);
        pull(q);
    }
    void insert (int i, int x, const Info &v = Info{}) {
        insert(root[i], root[i + 1], -inf, inf + 1, x, v);
    }
    void pull (int q) {
        info[q] = Info{info[q].l, info[q].r, info[info[q].l].val} + Info{.val = info[info[q].r].val};
    }
    Info rangeQuery (int p, int q, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info{};
        }
        if (l >= x && r <= y) {
            return info[q] - info[p];
        }
        int m = l + r >> 1;
        return rangequery(info[p].l, info[q].l, l, m, x, y) + rangequery(info[p].r, info[q].r, m, r, x, y);
    }
    Info rangeQuery (int l, int r, int x, int y) {
        return rangeQuery(root[l + 1], root[r + 1], -inf, inf + 1, x, y);
    }
    template <class F>
    int findFirst (int p, int q, int l, int r, int x, F pred) {
        if (r - l == 1) {
            return l;
        }
        int m = l + r >> 1;
        if (pred (info[info[p].l], info[info[q].l], x) ) {
            return findFirst(info[p].l, info[q].l, l, m, x, pred);
        } else {
            return findFirst(info[p].r, info[q].r, m, r, x, pred);
        }
    }
    template <class F>
    int findFirst (int l, int r, int x, F pred) {
        return findFirst(root[l + 1], root[r + 1], -inf, inf + 1, x, pred);
    }
    template <class F>
    int findLast (int p, int q, int l, int r, int x, F pred) {
        if (r - l == 1) {
            return l;
        }
        int m = l + r >> 1;
        if (pred (info[info[p].r], info[info[q].r], x) ) {
            return findFirst(info[p].r, info[q].r, m, r, x, pred);
        } else {
            return findFirst(info[p].l, info[q].l, l, m, x, pred);
        }
    }
    template <class F>
    int findLast (int l, int r, int x, F pred) {
        return findLast(root[l + 1], root[r + 1], -inf, inf + 1, x, pred);
    }
};
struct Info {
    int l, r, val = -1;
    void apply (int x, const Info &v) {

    }
};
Info operator+ (const Info &a, const Info &b) {

}
Info operator- (const Info &a, const Info &b) {

}