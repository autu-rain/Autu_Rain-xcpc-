template <class Info, size_t V = 30>
struct Persistent01Trie {
    int n, idx;
    vector<Info> info;
    vector<int> root;
    void init(int n_) {
        idx = 0;
        info.assign(V * n_ * 2, Info{});
        root.assign(n_ + 1, 0);
    }
    Persistent01Trie(int n_) : n(n_) {
        init(n_);
    }
    void pull(int q) {
        info[q] = Info{info[q].ch, info[info[q].ch[0]].val} + Info{.val = info[info[q].ch[1]].val};
    }
    void insert(int k, int p, int &q, int x, const Info &v) {
        q = ++ idx;
        info[q] = info[p];
        if (k < 0) {
            info[q].apply(v);
            return;
        }
        int u = x >> k & 1;
        info[q].ch[u ^ 1] = info[p].ch[u ^ 1];
        insert(k - 1, info[p].ch[u], info[q].ch[u], x, v);
        pull(q);
    }
    void insert(int i, int x, const Info &v = Info{}) {
        insert(V, root[i], root[i + 1], x, v);
    }
    template <class F>
    i64 find(int k, int p, int q, int x, F pred) {
        if (k < 0) {
            return 0ll;
        }
        int u = x >> k & 1;
        if (pred(info[info[p].ch[u ^ 1]], info[info[q].ch[u ^ 1]])) {
            return find(k - 1, info[p].ch[u ^ 1], info[q].ch[u ^ 1], x, pred) + (1ll << k);
        } else {
            return find(k - 1, info[p].ch[u], info[q].ch[u], x, pred);
        }
    }
    template <class F>
    i64 find(int l, int r, int x, F pred) {
        return find(V, root[l + 1], root[r + 1], x, pred);
    }
};

struct Info {
    array<int, 2> ch;
    int val;
    void apply(const Info &v) {

    }
};

Info operator+(const Info &a, const Info &b) {

}