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
    pair<int, int> find_deepest(int now, vector<string> &G, int prev, vector<int> &visited) {
        if(visited[now]) return pii(-1, -1);
        visited[now] = true;
        pii res = pii(0, now);
        rep(i, G.size()) {
            if(i != prev and i != now and G[now][i] == '1') {
                pii tmp = find_deepest(i, G, now, visited);
                if(tmp.first < 0) return tmp;
                if(tmp.first > res.first) res = tmp;
            }
        }
        res.first += 1;
        return res;
    }
    bool solve() {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        vector<int> visited(N);
        auto res = find_deepest(0, S, -1, visited);
        if(res.first < 0) {
            cout << -1 << endl;
        } else {
            rep(i, N) visited[i] = 0;
            pii ans = find_deepest(res.second, S, -1, visited);
            cout << ans.first << endl;
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
