#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using ll = long long;
using ull = unsigned long long;
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
const ull MOD = 1000000007;

class Solver {
  public:
    bool solve() {
        ull N, K; cin >> N >> K;
        vector<ull> A(N); cin >> A;

        vector<ull> cnt(2010);
        rep(i, N) cnt[A[i]]++;
        rep(i, 2001) cnt[i + 1] += cnt[i];

        ull ans = 0;
        rep(i, N) repeat(j, i + 1, N) {
            if(A[i] > A[j]) ans = (ans + K) % MOD;
        }
        ull a = (K * (K - 1) / 2) % MOD;
        rep(i, N) {
            ans = ans + (cnt[A[i] - 1] * a) % MOD;
            ans %= MOD;
        }
        cout << ans % MOD << endl;

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
