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
        int N, K; cin >> N >> K;
        vector<ll> V(N); cin >> V;
        ll ans = -INFL;
        rep(k, min(K, N) + 1) {
            repeat(x, 1, k + 1) {
                vector<ll> s;
                rep(j, x) s.push_back(V[j]);
                rep(j, k - x) s.push_back(V[N - j - 1]);
                sort(all(s));
                ll sum = accumulate(all(s), 0ll);
                int cnt = K - k;
                rep(i, min<int>(K - k, s.size())) if(s[i] < 0) {
                    sum -= s[i];
                    cnt++;
                }
                // debug(sum);
                set_max(ans, sum);
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
