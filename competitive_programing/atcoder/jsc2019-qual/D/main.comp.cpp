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
    void solve(vector<vector<int>> &G, int N, int offset, int level) {
        if(N <= 1) return;
        // cerr << N << " " << offset << " " << level << endl;
        solve(G, N / 2, offset, level+1);
        solve(G, N / 2 + (N % 2 > 0), offset + N / 2, level+1);
        rep(i, N / 2) {
            repeat(j, N / 2, N) {
                if(G[i+offset][j+offset] > 0) cerr << i << " " << j << endl;
                assert(G[i+offset][j+offset] < 0);
                G[i + offset][j + offset] = level;
            }
        }
    }
    bool solve() {
        int N; cin >> N;
        vector<vector<int>> G(N, vector<int>(N, -1));
        solve(G, N, 0, 1);
        rep(i, N) {
            repeat(j, i + 1, N) cout << G[i][j] << (j + 1 == N ? "\n" : " ");
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
