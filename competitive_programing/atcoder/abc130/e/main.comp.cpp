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
const ll MOD = 1000000007;

int main() {
    ll N, M; cin >> N >> M;
    vector<ll> S(N), T(M); cin >> S >> T;
    vector<vector<ll>> dp(N + 1, vector<ll>(M + 1));

    rep(n, N) {
        rep(m, M) {
            dp[n + 1][m + 1] = (dp[n + 1][m] + dp[n][m + 1] - dp[n][m] + MOD) % MOD;

            if(S[n] == T[m])
                dp[n + 1][m + 1] = (dp[n + 1][m + 1] + dp[n][m] + 1) % MOD;
        }
    }
    cout << dp[N][M] + 1 << endl;
    return 0;
}
