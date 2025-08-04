template<u32 P>
struct CRT {
    vector<i64> fac;

    CRT() {
        i64 x = P;
        for (int i = 2; 1U * i * i <= x; i++) {
            if (x % i == 0) {
                i64 res = 1;
                while (x % i == 0) {
                    x /= i;
                    res *= i;
                }
                fac.push_back(res);
            }
        }
        if (x > 1) {
            fac.push_back(x);
        }
    }

    i64 exgcd(i64 a, i64 b) {
        i64 u = 1, v = 0, p = b;
        while (b) {
            i64 t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        return (u + p) % p;
    }

    template<typename T>
    i64 crt(vector<T> &a) {
        for (int i = 0; i < fac.size(); i++) {
            for (int j = i + 1; j < fac.size(); j++) {
                if (gcd(fac[i], fac[j]) > 1) {
                    return 0LL;
                }
            }
        }
        i64 ans = 0;
        for (int i = 0; i < fac.size(); i ++ ) {
            i64 t1 = P / fac[i], t2 = exgcd(t1, fac[i]);
            ans = (ans + 1LL * t1 * t2 % P * a[i] % P) % P;
        }
        return ans % P;
    }
};