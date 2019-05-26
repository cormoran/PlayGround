#pragma GCC optimize ("-O3")
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define repeat(i, j, k) for(int i = (j); i < (int)(k); i++)
#define all(v) v.begin(),v.end()
#define debug(x) cerr << #x << " : " << x << endl

template<class T> bool set_min(T &a, const T &b) { return a > b  ? a = b, true : false; }
template<class T> bool set_max(T &a, const T &b) { return a < b  ? a = b, true : false; }
// vector
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }
template<class T> ostream& operator << (ostream &os , const vector<T> &v) { for(const T &t : v) os << "\t" << t; return os << endl; }
// pair
template<class T, class U> ostream& operator << (ostream &os , const pair<T, U> &v) { return os << "<" << v.first << ", " << v.second << ">"; }

const int INF = 1 << 30;
const ll INFL = 1LL << 60;

template<class T, class UpdateFunc, T update_unit>
class SegmentTree {
  public:
    int n;
    vector<T> data;
    UpdateFunc uf;
    SegmentTree(int nn) : n(1) {
        while(n < nn) n *= 2;
        data.resize( 2 * n - 1, update_unit);
    }
    SegmentTree(vector<T> init) : n(1) {
        int nn= init.size();
        while(n < nn) n *= 2;
        data.resize( 2 * n - 1, update_unit);
        copy(begin(init), end(init), begin(data) + n - 1);
    }
    T query(int i) {
        assert(0 <= i and i < n);
        return query(i, 0, 0, n);
    }
    void update(int a, int b, T v) {
        assert(0 <= a and a < b and b <= n);
        update(a, b, 0, 0, n, v);
    }
  private:
    void update(int a, int b, int i, int l, int r, T v) {
        if(out_of_range(a, b, l, r)) return;
        if(within_range(a, b, l, r)) data[i] = uf(data[i], v);
        else {
            int m = (l + r) / 2;
            if(l < a) { // l .. a .(r). b ..(r)
                update(l, a, left_child(i), l, m, data[i]);
                update(l, a, right_child(i), m, r, data[i]);
            }
            if(b < r) { // (l).. a .(l). b .. r
                update(b, r, left_child(i), l, m, data[i]);
                update(b, r, right_child(i), m, r, data[i]);
            }
            update(a, b, left_child(i), l, m, uf(data[i], v));
            update(a, b, right_child(i), m, r, uf(data[i], v));
            data[i] = update_unit; // 子に全て流したから
        }
    }
    T query(int a, int i, int l, int r) {
        if(data.size() <= i) return update_unit;
        assert(l <= a and a < r);
        int m = (l + r) / 2;
        T v = a < m ? query(a, left_child(i), l, m) : query(a, right_child(i), m, r);
        return uf(v, data[i]); // 先に流しているのでvの方が古い値
    }
    static bool out_of_range(int a, int b, int l, int r) { return r <= a or b <= l; }
    static bool within_range(int a, int b, int l, int r) { return a <= l and r <= b; }
    static int left_child(int i) { return i * 2 + 1; }
    static int right_child(int i) { return i * 2 + 2; }
    static int parent(int i) { return (i - 1) / 2; }
};

template <class T> struct Max {
    T operator() (const T& x, const T& y) const { return max(x, y); }
};

template<class T, T INIT>
using RangeMaxQuery = SegmentTree<T, Max<T>, INIT>;


class Solver {
  public:
    bool solve() {
        int N, Q; cin >> N >> Q;
        vector<tuple<int, int, int>> XST(N);
        rep(i, N) cin >> get<1>(XST[i]) >> get<2>(XST[i]) >> get<0>(XST[i]);
        sort(all(XST));
        reverse(all(XST));

        vector<int> D(Q); cin >> D;
        //RangeMaxQuery<int, -1> rmq(Q + 1);
        vector<queue<int>> begins(Q + 1);
        vector<queue<int>> ends(Q + 1);
        rep(i, N) {
            int sx = get<1>(XST[i]) - get<0>(XST[i]);
            int ex = get<2>(XST[i]) - get<0>(XST[i]);
            auto l = lower_bound(all(D), sx) - begin(D);
            auto r = lower_bound(all(D), ex) - begin(D);
            if(l == r) continue;
            begins[l].push(i);
            ends[r].push(i);
        }
        vector<int> ans(Q);
        set<int> s;
        int now = -1;
        rep(i, Q) {
            while(begins[i].size()) {
                set_max(now, begins[i].front());
                s.insert(begins[i].front());
                begins[i].pop();
            }
            while(ends[i].size()) {
                // set_max(now, begins[i].front());
                s.erase(ends[i].front());
                if(now == ends[i].front()) {
                    auto p = end(s);
                    if(s.size() > 0) p--;
                    now = s.size() > 0 ? *p : -1;
                }
                ends[i].pop();
            }
            ans[i] = now;
        }
        rep(i, Q) {
            int a = ans[i]; // rmq.query(i);
            cout << (a < 0 ? a : get<0>(XST[a])) << endl;
        }
        return 0;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    Solver s;
    s.solve();
    return 0;
}
