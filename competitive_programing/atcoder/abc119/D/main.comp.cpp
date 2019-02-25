#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define all(v) v.begin(),v.end()
template<class T> bool set_min(T &a, const T &b) { return a > b  ? a = b, true : false; }
const ll INFL = 1LL << 60;

int main() {
    int A, B, Q; cin >> A >> B >> Q;
    vector<ll> S(A + 2), T(B + 2);

    rep(i, A) cin >> S[i + 1];
    rep(i, B) cin >> T[i + 1];
    S[0] = T[0] = -INFL;
    S[A + 1] = T[B + 1] =  INFL;

    rep(q, Q) {
        ll x; cin >> x;
        auto sr = lower_bound(all(S), x);
        auto tr = lower_bound(all(T), x);
        auto sl = sr; sl--;
        auto tl = tr; tl--;
        assert(*sl < x and x <= *sr);
        assert(*tl < x and x <= *tr);
        ll d = INFL;
        set_min(d, max(*sr, *tr) - x);
        set_min(d, x - min(*sl, *tl));
        set_min(d, *sr - *tl + min(*sr - x, x - *tl));
        set_min(d, *tr - *sl + min(*tr - x, x - *sl));
        cout << d << endl;
    }

    return 0;
}
