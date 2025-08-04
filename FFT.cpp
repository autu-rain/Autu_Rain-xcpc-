template<class T>
struct FFT {
    vector<complex<T>> a, b;
    int n, m, k;
    vector<int> rev;
    T pi = acos(-1);

    void init(const vector<int> &p, const vector<int> &q) {
        n = p.size() + q.size() - 1;
        k = 1;
        while ((1 << k) < n) {
            k++;
        }
        m = 1 << k;
        a.resize(m);
        b.resize(m);
        rev.resize(m);
        rev[0] = 0;
        for (int i = 0; i < m; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k - 1);
        }
        for (int i = 0; i < p.size(); i++) {
            a[i] = {p[i], T{}};
        }
        for (int i = 0; i < q.size(); i++) {
            b[i] = {q[i], T{}};
        }
    }

    FFT(const vector<int> &p, const vector<int> &q) {
        init(p, q);
    }

    void fft(vector<complex<T>> &a, int inv = 1) {
        for (int i = 0; i < m; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 1; len < m; len <<= 1) {
            complex<T> w1{cos(pi / len), inv * sin(pi / len)};
            for (int i = 0; i < m; i += (len << 1)) {
                complex<T> wk{1, 0};
                for (int j = 0; j < len; j++, wk = wk * w1) {
                    auto l = a[i + j], r = wk * a[i + j + len];
                    a[i + j] = l + r;
                    a[i + j + len] = l - r;
                }
            }
        }
    }

    void work() {
        fft(a);
        fft(b);
        for (int i = 0; i < m; i++) {
            a[i] = a[i] * b[i];
        }
        fft(a, -1);
        for (int i = 0; i < n; i++) {
            a[i] = a[i].real() / m + 0.5;
        }
    }
};
