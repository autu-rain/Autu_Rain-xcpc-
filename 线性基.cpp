constexpr i64 N = 63, inf = 1ll << N;
struct Basis {
    bitset<N> a[N];
    vector<int> t;

    Basis() {
        t.assign(N, -1);
    }

    bool insert(bitset<N> x, int tm = 1E9) {
        for (int k = N - 1; k >= 0; k--) {
            if (x[k] == 1) {
                if (tm > t[k]) {
                    swap(x, a[k]);
                    swap(tm, t[k]);
                }
                x ^= a[k];
            }
        }
        return x.to_ullong() == 0;
    }

    i64 query(bitset<N> x, int tm = 0) {
        for (int k = N - 1; k >= 0; k--) {
            if (t[k] >= tm) {
                // if (x[k] == 1) {
                //     x ^= a[k];
                // }
                if (x[k] == 0) {
                    x ^= a[k];
                }
            }
        }
        return x.to_ullong();
    }

    i64 queryK(bitset<N> x, int n, i64 id = inf, int tm = 0) {
        int cnt = 0;
        for (int k = N - 1; k >= 0; k--) {
            if (t[k] >= tm) {
                cnt += (a[k] != 0);
            }
        }

        if (cnt < n) {
            id--;
        }
        if (id >= (1ll << cnt)) {
            return -1;
        }

        for (int k = N - 1, i = cnt; k >= 0; k--) {
            if (t[k] >= tm && a[k] != 0) {
                i--;
                if (id >> i & 1) {
                    if (x[k] == 0) {
                        x ^= a[k];
                    }
                } else {
                    if (x[k] == 1) {
                        x ^= a[k];
                    }
                }
            }
        }
        return x.to_ullong();
    }
};