template<u32 P, u32 g>
struct NTT {
    using Z = ModInt<P>;
    vector<Z> a, b;
    int n, m, k;
    vector<int> rev;
    Z invg, invm;

    void init(const vector<int> &p, const vector<int> &q) {
        n = p.size() + q.size() - 1;
        invg = Z(1) / g;
        k = 1;
        while ((1 << k) < n) {
            k++;
        }
        m = 1 << k;
        invm = Z(1) / m;
        a.resize(m);
        b.resize(m);
        rev.resize(m);
        rev[0] = 0;
        for (int i = 0; i < m; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k - 1);
        }
        for (int i = 0; i < p.size(); i++) {
            a[i] = Z(p[i]);
        }
        for (int i = 0; i < q.size(); i++) {
            b[i] = Z(q[i]);
        }
    }

    NTT() {}

    NTT(const vector<int> &p, const vector<int> &q) {
        init(p, q);
    }


    void ntt(vector<Z> &a, int inv = 1) {
        for (int i = 0; i < m; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 1; len < m; len <<= 1) {
            Z w1 = power(inv == 1 ? g : invg, (P - 1) / (len << 1));
            for (int i = 0; i < m; i += (len << 1)) {
                Z wk = 1;
                for (int j = 0; j < len; j++, wk = wk * w1) {
                    Z l = a[i + j], r = wk * a[i + j + len];
                    a[i + j] = l + r;
                    a[i + j + len] = l - r;
                }
            }
        }
    }

    void work() {
        ntt(a);
        ntt(b);
        for (int i = 0; i < m; i++) {
            a[i] = a[i] * b[i];
        }
        ntt(a, -1);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * invm;
        }
    }
};