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
    void go(int now, int prev, const vector<vector<pii>> &E, vector<int> &c) {
        for(auto &p : E[now]) {
            if(p.first == prev) continue;
            c[p.first] = p.second % 2 == 0 ? c[now] : (c[now] + 1) % 2;
            go(p.first, now, E, c);
        }
    }

    bool solve() {
        int N; cin >> N;
        vector<vector<pii>> E(N);
        rep(i , N - 1) {
            int u, v, w; cin >> u >> v >> w;
            E[u - 1].emplace_back(v - 1, w);
            E[v - 1].emplace_back(u - 1, w);
        }
        vector<int> c(N);
        c[0] = 0;
        go(0, -1, E, c);
        rep(i, N) cout << c[i] << endl;
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
