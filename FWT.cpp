class Or {
public:
    void operator()(auto &a, auto inv) {
        int m = a.size();
        for (int len = 1; len < m; len <<= 1) {
            for (int i = 0; i < m; i += (len << 1)) {
                for (int j = 0; j < len; j++) {
                    a[i + j + len] += a[i + j] * inv;
                }
            }
        }
    }
};

class And {
public:
    void operator()(auto &a, auto inv) {
        int m = a.size();
        for (int len = 1; len < m; len <<= 1) {
            for (int i = 0; i < m; i += (len << 1)) {
                for (int j = 0; j < len; j++) {
                    a[i + j] += a[i + j + len] * inv;
                }
            }
        }
    }
};

class Xor {
public:
    void operator()(auto &a, auto inv) {
        int m = a.size();
        for (int len = 1; len < m; len <<= 1) {
            for (int i = 0; i < m; i += (len << 1)) {
                for (int j = 0; j < len; j++) {
                    a[i + j] += a[i + j + len];
                    a[i + j + len] = a[i + j] - 2 * a[i + j + len];
                    a[i + j] *= inv;
                    a[i + j + len] *= inv;
                }
            }
        }
    }
};

template<u32 P, class FWT_>
struct FWT {
    using Z = ModInt<P>;
    vector<Z> a, b;
    int n, m, k;
    Z inv2;

    void init(const vector<int> &p, const vector<int> &q) {
        n = max(p.size(), q.size());
        k = 1;
        inv2 = Z(1) / 2;
        while ((1 << k) < n) {
            k++;
        }
        m = 1 << k;
        a.resize(m);
        b.resize(m);
        for (int i = 0; i < p.size(); i++) {
            a[i] = Z(p[i]);
        }
        for (int i = 0; i < q.size(); i++) {
            b[i] = Z(q[i]);
        }
    }

    FWT() {}

    FWT(const vector<int> &p, const vector<int> &q) {
        init(p, q);
    }

    void work() {
        FWT_ fwt;
        fwt(a, Z(1));
        fwt(b, Z(1));
        for (int i = 0; i < m; i++) {
            a[i] = a[i] * b[i];
        }
        if (std::is_same<FWT_, Xor>::value) {
            fwt(a, inv2);
        } else {
            fwt(a, Z(-1));
        }
    }
};