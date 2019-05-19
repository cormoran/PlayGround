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
    void go(int now, vector<int> &visited, const vector<vector<int>> &E) {
        visited[now] = true;
        for(int nxt : E[now]) if(not visited[nxt]) go(nxt, visited, E);
    }

    bool solve() {
        int N, M; cin >> N >> M;
        vector<int> X(M), Y(M), Z(M);
        vector<vector<int>> E(N);
        rep(i, M) {
            cin >> X[i] >> Y[i] >> Z[i];
            X[i]--;
            Y[i]--;
            E[X[i]].push_back(Y[i]);
            E[Y[i]].push_back(X[i]);
        }

        int ans = 0;
        vector<int> visited(N);
        rep(i, N) {
            if(not visited[i]) {
                go(i, visited, E);
                ans++;
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
