template <class T>
struct Comb {
    T C(int n, int m) {
        if (n < m || m < 0) return 0;
        if (n == m) return 1;
        T res = 1;
        for (int i = 1, j = n; i <= m; i++, j--) {
            res = res * j / i;
        }
        return res;
    }

    T Lucas(i64 n, i64 m) {
        if (n < P && m < P) return C(n, m);
        return C(n % P, m % P) * Lucas(n / P, m / P);
    }

};