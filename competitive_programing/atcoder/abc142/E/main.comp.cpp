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


int main() {
    int N, M; cin >> N >> M;
    vector<int> A(M), B(M);
    vector<int> C(M);
    rep(i, M) {
        cin >> A[i] >> B[i];
        rep(j, B[i]) {
            int c; cin >> c; c--;
            C[i] = C[i] | (1 << c);
        }
    }
    vector<int> dp(1 << N, INF);
    dp[0] = 0;
    rep(bit, 1 << N) {
        rep(j, M) {
            set_min(dp[bit | C[j]], dp[bit] + A[j]);
        }
    }
    cout << (dp.back() < INF ? dp.back() : -1) << endl;
    return 0;
}
