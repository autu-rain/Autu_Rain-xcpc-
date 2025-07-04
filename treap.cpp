struct Treap {
	struct Node {
	    int l, r;
	    int key, val;
	    int cnt, size;
	};
	vector<Node> tr;
	int root, idx;

	Treap(int n) {
		tr.resize(n + 10 + q);
		root = 0, idx = 0;
	}

	void pushup(int p) {
	    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
	}

	int get_node(int key) {
	    tr[ ++ idx ].key = key;
	    tr[idx].val = rand();
	    tr[idx].cnt = 1;
	    tr[idx].size = 1;
	    return idx;
	}

	void zig(int &p) {
	    int q = tr[p].l;
	    tr[p].l = tr[q].r;
	    tr[q].r = p;
	    p = q;
	    pushup(p); pushup(tr[p].r);
	}

	void zag(int &p) {
	    int q = tr[p].r;
	    tr[p].r = tr[q].l;
	    tr[q].l = p;
	    p = q;
	    pushup(p); pushup(tr[p].l);
	}

	void build() {
	    get_node(-inf); get_node(inf);
	    root = 1; tr[1].r = 2;
	    pushup(root);
	    if (tr[2].val > tr[1].val) zag(root);
	}

	void insert(int &p, int key) {
	    if (!p) p = get_node(key);
	    else if (tr[p].key == key) tr[p].cnt ++;
	    else if (tr[p].key > key) {
	        insert(tr[p].l, key);
	        if (tr[p].val < tr[tr[p].l].val) zig(p);
	    }
	    else if (tr[p].key < key) {
	        insert(tr[p].r, key);
	        if (tr[p].val < tr[tr[p].r].val) zag(p);
	    }
	    pushup(p);
	}

	void pop(int &p, int key) {
	    if (!p) return;
	    if (tr[p].key == key) {
	        if (tr[p].cnt > 1) tr[p].cnt --;
	        else {
	            if (tr[p].l || tr[p].r) {
	                if (!tr[p].r || tr[p].val < tr[tr[p].l].val) {
	                    zig(p);
	                    pop(tr[p].r, key);
	                } else {
	                    zag(p);
	                    pop(tr[p].l, key);
	                }
	            } else p = 0;
	        }
	    } else if (tr[p].key > key) pop(tr[p].l, key);
	    else pop(tr[p].r, key);
	    pushup(p);
	}

	int get_rank(int p, int key) {
	    if (!p) return 0;
	    if (tr[p].key == key) return tr[tr[p].l].size + 1;
	    if (tr[p].key > key) return get_rank(tr[p].l, key);
	    if (tr[p].key < key) return tr[tr[p].l].size + tr[p].cnt + get_rank(tr[p].r, key);
	}

	int get_key(int p, int rank) {
	    if (!p) return inf;
	    if (tr[tr[p].l].size >= rank) return get_key(tr[p].l, rank);
	    else if (tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;
	    else return get_key(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
	}

	int get_pre(int p, int key) {
	    if (!p) return -inf;
	    if (tr[p].key >= key) return get_pre(tr[p].l, key);
	    else return max(tr[p].key, get_pre(tr[p].r, key));
	}

	int get_next(int p, int key) {
	    if (!p) return inf;
	    if (tr[p].key <= key) return get_next(tr[p].r, key);
	    else return min(tr[p].key, get_next(tr[p].l, key));
	}
};