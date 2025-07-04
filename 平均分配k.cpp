v<int> distributeK(v<int> &a, int k) {
    sort(all(a));
    int n = a.size();
    if (!n) return {};
    v<pII> tmp;
    int cur_v = a[0];
    int cnt = 1;
    for (int i = 1; i < n; i ++ ) {
        if (a[i] == cur_v) {
            cnt ++ ;
        } else {
            tmp.eb(cur_v, cnt);
            cur_v = a[i];
            cnt = 1;
        }
    }
    tmp.eb(cur_v, cnt);
    int m = tmp.size();
    int idx = 0;
    int cur_l = tmp[idx].x;
    int t_cnt = tmp[idx].y;
    idx ++ ;
    while (idx < m) {
        int n_v = tmp[idx].x;
        int cnt = tmp[idx].y;
        int d = n_v - cur_l;
        int t1 = (int)t_cnt * d;
        if (t1 <= k) {
            k -= t1;
            cur_l = n_v;
            t_cnt += cnt;
            idx ++ ;
        } else {
            int t = k / t_cnt;
            int r = k % t_cnt;
            cur_l += t;
            v<int> res;
            for (int i = 0; i < r; i ++ ) {
                res.pb(cur_l + 1);
            }
            for (int i = r; i < t_cnt; i ++ ) {
                res.pb(cur_l);
            }
            for (int i = idx; i < m; i ++ ) {
                for (int j = 0; j < tmp[i].y; j ++ ) {
                    res.pb(tmp[i].x);
                }
            }
            return sort(all(res)), res;
        }
    }
    int t = k / n;
    int r = k % n;
    cur_l += t;
    v<int> res(n, cur_l);
    for (int i = 0; i < r; i ++ ) {
        res[i] += 1;
    }
    return sort(all(res)), res;
}