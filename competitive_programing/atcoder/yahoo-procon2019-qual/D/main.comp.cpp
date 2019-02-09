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
        int L; cin >> L;
        vector<ll> A(L); cin >> A;
        vector<ll> even(L + 1), zero(L + 1), sum(L + 1); // [i, L)
        rep(i, L) {
            even[L - i - 1] = even[L - i] + (A[L - i - 1] > 0 and A[L - i - 1] % 2 == 0);
            zero[L - i - 1] = zero[L - i] + (A[L - i - 1] == 0);
            sum[L - i - 1] = sum[L - i] + A[L - i - 1];
        }

        auto f = [&] (int i) {
            return max(0ll, even[0] - even[i + 1] - 2) + zero[0] - zero[i + 1] + sum[i + 1];
        };
        vector<int> indices(L); rep(i, L) indices[i] = i;
        sort(all(indices), [&] (int i, int j) {
                return f(i) < f(j);
            });
        debug(indices);
        ll ans = INFL;
        int ii = 0;
        rep(i, L) {
            while(ii < L and indices[ii] < i) ii++;
            if(ii >= L) break;
            ll score = (sum[0] - sum[i]) + f(indices[ii]) - (even[0] - even[i] + zero[0] - zero[i]);
            set_min(ans, score);
            cerr << i << " " << indices[ii] << " " << score << endl;
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
