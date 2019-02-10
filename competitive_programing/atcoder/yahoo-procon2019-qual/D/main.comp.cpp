#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define repeat(i, j, k) for(int i = (j); i < (int)(k); i++)
#define all(v) v.begin(),v.end()
#define debug(x) cerr << #x << " : " << x << endl

template<class T> bool set_min(T &a, const T &b) { return a > b  ? a = b, true : false; }
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }
template<class T> ostream& operator << (ostream &os , const vector<T> &v) { for(const T &t : v) os << "\t" << t; return os << endl; }
const ll INFL = 1LL << 60;

class Solver {
  public:
    bool solve() {
        int L; cin >> L;
        vector<ll> A(L); cin >> A;
        vector<vector<ll>> dp(L + 1, vector<ll>(6, INFL));
        rep(i, 6) dp[0][i] = 0;
        rep(i, L) {
            auto f = [&] (int j) -> ll {
                switch(abs(2 - j)) {
                    case 2: return A[i];
                    case 1: return (A[i] == 0 ? 2 : A[i] % 2);
                    case 0: return A[i] % 2 == 0;
                }
                assert(false);
            };
            rep(j, 5) {
                set_min(dp[i + 1][j + 1], dp[i + 1][j]);
                set_min(dp[i + 1][j + 1], min(dp[i][j + 1], dp[i][j]) + f(j));
            }
        }

        cout << dp[L][5] << endl;

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
