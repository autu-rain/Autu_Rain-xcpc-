template <class T>
struct Comb {
    int n;
    std::vector<T> _fac;
    std::vector<T> _invfac;
    std::vector<T> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb (int n) : Comb() {
        init (n);
    }

    void init (int m) {
        if (m <= n) return;
        _fac.resize (m + 1);
        _invfac.resize (m + 1);
        _inv.resize (m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    T fac (int m) {
        if (m > n) init (2 * m);
        return _fac[m];
    }
    T invfac (int m) {
        if (m > n) init (2 * m);
        return _invfac[m];
    }
    T inv (int m) {
        if (m > n) init (2 * m);
        return _inv[m];
    }
    T C (int n, int m) {
        if (n < m || m < 0) return 0;
        return fac (n) * invfac (m) * invfac (n - m);
    }
    T A (int n, int m) {
        if (n < m || m < 0) return 0;
        return fac (n) * invfac (n - m);
    }
    // 六十度斜行和公式
    // C(m, m) + C(m + 1, m) + ... + C(m + n, m) = C(m + 1 + n, m + 1)
    T Csum (int n, int m) {
        return C (m + 1 + n, m + 1);
    }

    T Catalan (int n) {
        return C (2 * n, n) - C (2 * n, n - 1);
    }
};