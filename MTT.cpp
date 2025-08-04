constexpr u32 P1 = 469762049;
constexpr u32 P2 = 998244353;
constexpr u32 P3 = 1004535809;
struct MTT {
    NTT<P1, 3> g1;
    NTT<P2, 3> g2;
    NTT<P3, 3> g3;
    vector<vector<i64>> a;
    int n;
    u32 P;

    void init(const vector<int> &p, const vector<int> &q, u32 P_) {
        n = p.size() + q.size() - 1;
        P = P_;
        g1.init(p, q);
        g2.init(p, q);
        g3.init(p, q);
        g1.work();
        g2.work();
        g3.work();
        a.resize(3);
        a[0].resize(n);
        a[1].resize(n);
        a[2].resize(n);
        for (int j = 0; j < n; j++) {
            a[0][j] = g1.a[j].val();
            a[1][j] = g2.a[j].val();
            a[2][j] = g3.a[j].val();
        }
    }

    MTT(const vector<int> &p, const vector<int> &q, u32 P_) {
        init(p, q, P_);
    }

    i64 power(i64 a, i64 b, u32 P) {
        i64 res = 1;
        for (; b; b >>= 1, a = a * a % P) {
            if (b & 1) {
                res = res * a % P;
            }
        }
        return res;
    }

    i64 inv(i64 a, u32 P) {
        return power(a, P - 2, P);
    }

    void work() {
        for (int i = 0; i < n; i++) {
            i64 t = a[0][i] + (a[1][i] - a[0][i] + P2) % P2 * inv(P1, P2) % P2 * P1;
            i64 ans = (t + (a[2][i] - t % P3 + P3) % P3 * inv(1ll * P1 * P2 % P3, P3) % P3 * P1 % P * P2 % P) % P;
            a[0][i] = ans;
        }
    }
};