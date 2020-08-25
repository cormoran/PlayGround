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
        string S; cin >> S;
        ll K; cin >> K;
        vector<ll> seq = {0};
        repeat(i, 1, S.size()) {
            seq.back()++;
            if(S[i] != S[i - 1]) seq.push_back(0);
        }
        seq.back()++;
        //debug(seq);
        if(seq.size() == 1) {
            cout << (ll)S.size() * K / 2 << endl;
            return 0;
        }
        if(S.front() == S.back()) {
            ll f = seq.front();
            ll b = seq.back();
            ll ans_a = 0;
            repeat(i, 1, seq.size() - 1) ans_a += seq[i] / 2;
            ll ans = ans_a * K + f / 2 + b / 2 + (f + b) / 2 * (K - 1);
            cout << ans << endl;
        } else {
            ll ans_a = 0;
            rep(i, seq.size()) ans_a += seq[i] / 2;
            ll ans = ans_a * K;
            cout << ans << endl;
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
