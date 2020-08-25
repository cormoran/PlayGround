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

map<char, int> DIR_TO_INT = { {'R', 0}, {'L', 1}, {'U', 2}, {'D', 3} };
const int DX[] = {1, -1, 0, 0};
const int DY[] = {0, 0, 1, -1};

int main() {

    int N; cin >> N;
    vector<int> X(N), Y(N);
    vector<char> Dir(N);
    rep(i, N) cin >> X[i] >> Y[i] >> Dir[i];

    rep(i, N) X[i] *= 2;
    rep(i, N) Y[i] *= 2;

    vector<int> R, L, U, D, RL, UD;
    rep(i, N) {
        if(Dir[i] == 'R') R.push_back(i), RL.push_back(i);
        if(Dir[i] == 'L') L.push_back(i), RL.push_back(i);
        if(Dir[i] == 'U') U.push_back(i), UD.push_back(i);
        if(Dir[i] == 'D') D.push_back(i), UD.push_back(i);
    }

    sort(all(RL), [&](int i, int j) { return Y[i] < Y[j]; });
    sort(all(UD), [&](int i, int j) { return X[i] < X[j]; });

    sort(all(R), [&](int i, int j) { return X[i] < X[j]; });
    sort(all(L), [&](int i, int j) { return X[i] < X[j]; });
    sort(all(U), [&](int i, int j) { return Y[i] < Y[j]; });
    sort(all(D), [&](int i, int j) { return Y[i] < Y[j]; });

    ll x_max_fix = X[(UD.size() ? UD : RL).back()], x_min_fix = X[(UD.size() ? UD : RL).front()];
    ll y_max_fix = Y[(RL.size() ? RL : UD).back()], y_min_fix = Y[(RL.size() ? RL : UD).front()];
    ll x_max_fix_d = UD.size() ? 0 : -1, x_min_fix_d = UD.size() ? 0 : 1;
    ll y_max_fix_d = RL.size() ? 0 : -1, y_min_fix_d = RL.size() ? 0 : 1;

    ll x_max_ini = X[L.size() ? L.back() : 0], x_min_ini = X[R.size() ? R.front() : 0];
    ll y_max_ini = Y[D.size() ? D.back() : 0], y_min_ini = Y[U.size() ? U.front() : 0];

    ll x_go_max = X[R.size() ? R.back() : 0], x_go_min = X[L.size() ? L.front() : 0];
    ll y_go_max = Y[U.size() ? U.back() : 0], y_go_min = Y[D.size() ? D.front() : 0];
    ll x_go_max_d = R.size() ? 1 : -1, x_go_min_d = L.size() ? -1 : 1;
    ll y_go_max_d = U.size() ? 1 : -1, y_go_min_d = D.size()? -1 : 1;


    ll ans = 1e16;
    ll pdx = 1e16, pdy = 1e16;
    for(ll t = 0; ; t++) {
        ll x_max = max({x_max_fix + x_max_fix_d * t, x_max_ini - t, x_go_max + x_go_max_d * t});
        ll x_min = min({x_min_fix + x_min_fix_d * t, x_min_ini + t, x_go_min + x_go_min_d * t});

        ll y_max = max({y_max_fix + y_max_fix_d * t, y_max_ini - t, y_go_max + y_go_max_d * t});
        ll y_min = min({y_min_fix + y_min_fix_d * t, y_min_ini + t, y_go_min + y_go_min_d * t});

        ll dx = x_max - x_min;
        ll dy = y_max - y_min;
        if(dx >= pdx and dy >= pdy) break;
        pdx = dx; pdy = dy;
        ans = min(ans, dx * dy);
    }
    cout << ans / 4.0 << endl;
    return 0;
}
