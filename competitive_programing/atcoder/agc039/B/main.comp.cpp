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
    int go(int a, const vector<string> &G) {
        set<int> fronts = {a};
        set<int> prev_fronts = {};
        vector<int> used(G.size(), 0);
        used[a] = true;
        int used_cnt = 1;
        int k = 1;
        while(true) {
            set<int> next_fronts;
            for(int now : fronts) {
                rep(i, G.size()) {
                    if(G[now][i] == '1') {
                        if(used[i]) {
                            if(not prev_fronts.count(i) and not next_fronts.count(i)) {
                                return -1;
                            }
                        } else {
                            next_fronts.insert(i);
                            used[i] = true;
                            used_cnt++;
                        }
                    }
                }
            }
            if(next_fronts.size() == 0) break;
            prev_fronts = fronts;
            fronts = next_fronts;
            k++;
        }
        //cerr << a << ": " << k << endl;
        return k;
    }
    bool solve() {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        int ans = -1;
        rep(i, N) set_max(ans, go(i, S));
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
