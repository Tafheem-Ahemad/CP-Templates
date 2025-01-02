
#define ll long long int

struct Node {
    ll val00, val01, val10, val11;
    ll max_val;
    Node(int val = 0) {
        val00 = val01 = val10 = 0;
        val11 = val;
        max_val = max(0, val);
    }
};

Node merge(Node a, Node b) {
    Node res;
    res.val00 = max({a.val00 + b.val00, a.val00 + b.val10, a.val01 + b.val00});
    res.val01 = max({a.val00 + b.val01, a.val01 + b.val01, a.val00 + b.val11});
    res.val10 = max({a.val10 + b.val00, a.val10 + b.val10, a.val11 + b.val00});
    res.val11 = max(a.val10 + b.val11, a.val11 + b.val01);
    res.max_val = max({res.val00, res.val01, res.val10, res.val11});
    return res;
}

class SegmentTree {
    vector<Node> t;
    int n;

    public:
    SegmentTree(vector<ll> &arr) {
        n = arr.size();
        t.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void build(vector<ll> &arr, int id, int l, int r) {
        if(l == r) {
            t[id] = Node(arr[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(arr, id << 1, l, mid);
        build(arr, id << 1 | 1, mid + 1, r);
        t[id] = merge(t[id << 1], t[id << 1 | 1]);
    }

    void update(int id, int l, int r, int pos, ll x) {
        if(pos < l || pos > r) {
            return;
        }
        if(l == r) {
            t[id]=Node(x);
            return;
        }
        int mid = (l + r) >> 1;
        update(id << 1, l, mid, pos, x);
        update(id << 1 | 1, mid + 1, r, pos, x);
        t[id] = merge(t[id << 1], t[id << 1 | 1]);
    }

    Node query(int id, int l, int r, int lq, int rq) {
        if(lq > r || l > rq) {
            return Node();
        }
        if(lq <= l && r <= rq) {
            return t[id];
        }
        int mid = (l + r) >> 1;
        return merge(query(id << 1, l, mid, lq, rq), query(id << 1 | 1, mid + 1, r, lq, rq));
    }
};