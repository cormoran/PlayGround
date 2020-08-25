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


class Solver {
  public:
    bool solve() {
        int N; cin >> N;
        vector<ll> P(N); cin >> P;
        ll ans = 0;
        {
            vector<vector<int>> nxt_large_index_r(N, vector<int>(2, N));
            {
                vector<int> to_index(N + 1, -1); rep(i, N) to_index[P[i]] = i;
                vector<int> cnt(N+1, 0);
                set<int> pool;
                rep(i, N) {
                    set<int> remove_set;
                    for(auto p : pool) {
                        if(p > P[i]) break;
                        nxt_large_index_r[to_index[p]][cnt[p]] = i;
                        if(++cnt[p] >= 2) remove_set.insert(p);
                    }
                    for(auto p : remove_set) pool.erase(p);
                    pool.insert(P[i]);
                }
            }
            vector<vector<int>> nxt_large_index_l(N, vector<int>(2, -1));
            {
                vector<int> to_index(N + 1, -1); rep(i, N) to_index[P[i]] = i;
                vector<int> cnt(N+1, 0);
                set<int> pool;
                for(int i = N - 1; i >= 0; i--) {
                    set<int> remove_set;
                    for(auto p : pool) {
                        if(p > P[i]) break;
                        nxt_large_index_l[to_index[p]][cnt[p]] = i;
                        if(++cnt[p] >= 2) remove_set.insert(p);
                    }
                    for(auto p : remove_set) pool.erase(p);
                    pool.insert(P[i]);
                }
            }
            // rep(i, N) cerr << P[i] << " "; cerr << endl;
            // rep(i, N) cerr << nxt_large_index_r[i][0] << " "; cerr << endl;
            // rep(i, N) cerr << nxt_large_index_r[i][1] << " "; cerr << endl;
            // cerr << endl;
            // rep(i, N) cerr << P[i] << " "; cerr << endl;
            // rep(i, N) cerr << nxt_large_index_l[i][0] << " "; cerr << endl;
            // rep(i, N) cerr << nxt_large_index_l[i][1] << " "; cerr << endl;
            rep(l, N) {
                int r1 = nxt_large_index_r[l][0]; // P[r1] > P[l]
                int r2 = nxt_large_index_r[l][1]; // P[r2] > P[l]

                int l1 = nxt_large_index_l[l][0]; // P[r1] > P[l]
                int l2 = nxt_large_index_l[l][1]; // P[r2] > P[l]

                int a = l1 - l2 - 1;
                int b = l - l1- 1;
                int c = r1 - l - 1;
                int d = r2 - r1 - 1;
                ll cnt = (l1 >= 0) * (a + 1) * (c + 1) + (r1 < N) * (b + 1) * (d + 1);
                // ll cnt = (r2 - r1) + (l1 - l2);
                // if(r1 < N) cnt += max(0, l - l1 - 1);
                // if(l1 >= 0) cnt += max(0, r1 - l - 1);
                //cerr << l << " " << P[l] << " : " << cnt << endl;
                ans += cnt * P[l];
            }
        }

        cout << ans << endl;

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
