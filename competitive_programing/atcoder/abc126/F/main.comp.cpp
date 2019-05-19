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

void test(int M, int K, vector<int> z) {
    vector<int> visited(z.size() / 2);
    rep(i, z.size()) {
        if(visited[z[i]]) continue;
        int s = 0;
        bool found = false;
        repeat(j, i + 1, z.size()) {
            if(z[i] == z[j]) {
                found = true;
                break;
            }
            s ^= z[j];
        }
        if(found and s != K) {
            // debug(z);
            // cerr << i << " " << s << endl;
            assert(0);
        }
    }
}

class Solver {
  public:
    bool solve() {
        int M, K; cin >> M >> K;

        int a = pow(2, M);
        if(K == 0) {
            rep(i, a) cout << i << " " << i << (i == a - 1 ? "\n" : " ");
            return false;
        }
        vector<pii> p;
        set<int> used;
        rep(i, a) {
            int j = K ^ i;
            if(used.count(j)) continue;
            used.insert(i);
            used.insert(j);
            if(j >= a) {
                cout << -1 << endl;
                return false;
            }
            p.emplace_back(i, j);
        }
        if(p.size() % 2 != 0) {
            cout << -1 << endl;
            return false;
        }
        //debug(p);
        int cnt = 0;
        vector<int> res;
        rep(i, p.size() / 2) {
            pii x = p[i * 2];
            pii y = p[i * 2 + 1];
            vector<int> z = {
                x.first, y.first, y.second, x.first, x.second, y.second, y.first, x.second
            };
            rep(i, z.size()) {
                res.push_back(z[i]);
            }
        }
        // test(M, K, res);
        rep(i, res.size()) {
            cout << res[i] << (i == res.size() - 1 ? "\n" : " ");
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
