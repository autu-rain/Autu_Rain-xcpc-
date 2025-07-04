template <class T>
struct Comb {
  int n, flg = 1;
  T mod;
  vector<T> fac;

  Comb(T _mod, int n = 0) : n{n}, mod{_mod} { 
    div_mod();
    for (int i = 0; i < fac.size(); i ++ )
      for (int j = i + 1; j < fac.size(); j ++ )
        if (gcd(fac[i], fac[j]) > 1) {
            flg = 0;
            break;
        }
  }

  T C(int n, int m, int p) {
    if (n < m || m < 0) return 0;
    if (n == m) return 1;
    T res = 1;
    for (int i = 1, j = n; i <= m; i ++, j -- ) {
      res = res * j / i;
    }
    return res;
  }

  T Lucas(int n, int m, int p) {
    if (n < p && m < p) return C(n, m, p);
    return C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
  }

  T exgcd(T a, T b) {
    T u = 1, v = 0, p = b;
    while (b) {
      T t = a / b;
      a -= t * b; swap(a, b);
      u -= t * v; swap(u, v);
    }
    return (u + p) % p;
  }

  void div_mod() {
    int tmp = mod;
    for (int i = 2; i <= mod; i ++ )
      if (tmp % i == 0) {
        while (tmp % i == 0) tmp /= i, fac.push_back(i);
      }
    if (tmp > 1) fac.push_back(tmp);
  }


  T CRT(int n, int m) {
    if (!flg) return 0;
    T ans = 0;
    for (int i = 0; i < fac.size(); i ++ ) {
      T t1 = mod / fac[i], t2 = exgcd(t1, fac[i]);
      ans = (ans + t1 * t2 % mod * Lucas(n, m, fac[i])) % mod;
    }
    return ans;
  }

};
