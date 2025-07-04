template <class T, class Info, size_t V = 1>
struct Trie {
    int n, idx;
    vector<Info> info;
    void init(int n_) {
        idx = 0;
        info.assign(2 * V * n_, Info {});
    }
    Trie(int n_) : n(n_) {
        init(n_);
    }
    string unified(const T &v) {
        string nv;
        if constexpr (V != 1) {
            for (int i = V; i >= 0; --i) {
                nv += char((v >> i & 1) + 'a');
            }
        } else {
            nv = v;
        }
        return nv;
    }
    void insert(const T &v, const Info &x = Info{}) {
        string nv = unified(v);
        int p = 0;
        for (auto x : nv) {
            int u = x - 'a';
            if (!info[p].ch[u]) {
                info[p].ch[u] = ++ idx;
            }
            p = info[p].ch[u];
        }
        info[p].apply(x);
    }
    Info query(const T &v) {
        string nv = unified(v);
        int p = 0;
        for (auto x : nv) {
            int u = x - 'a';
            if (!info[p].ch[u]) {
                return Info{};
            }
            p = info[p].ch[u];
        }
        return info[p];
    }
    i64 find(const T &v) {
        if constexpr (V != 1) {
            int p = 0;
            i64 ans = 0;
            for (int i = V; i >= 0; --i) {
                int u = v >> i & 1;
                if (info[p].ch[u ^ 1]) {
                    ans |= (1LL << i);
                    p = info[p].ch[u ^ 1];
                } else {
                    p = info[p].ch[u];
                }
            }
            return ans;
        }
    }
};

template <size_t N>
struct Info {
    array<int, N> ch;
    void apply(const Info &x) {

    }
};