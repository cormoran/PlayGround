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
const ll MOD = 1000000000+7;

class Solver {
  public:
    bool solve() {
        int N; cin >> N;
        string S; cin >> S;

        int arr = 0;
        ll num_pair = 1;
        rep(i, N * 2) {
            if(S[i] == 'W') {
                if(arr % 2 == 0) {
                    num_pair *= arr;
                    num_pair %= MOD;
                    arr--;
                } else arr++;
            } else {
                if(arr % 2 == 1) {
                    num_pair *= arr;
                    num_pair %= MOD;
                    arr--;
                } else arr++;
            }
            if(arr < 0) break;
        }
        if(arr != 0) num_pair = 0;
        ll ans = 1;
        rep(i, N) ans = (ans * (i + 1)) % MOD;
        cout << (ans * num_pair) % MOD << endl;
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
