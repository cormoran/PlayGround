#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(),v.end()


int main() {
    ll N; cin >> N;

    vector<ll> div;
    for(ll i = 1; i * i <= N; i++) {
        if(N % i == 0) {
            ll m = i - 1;
            ll d = N / i;
            if(m > d) div.push_back(i);
            if(i * i != N) {
                ll m = N / i - 1;
                ll d = i;
                if(m > d) div.push_back(N / i);
            }
        }
    }
    sort(all(div));
    ll ans = 0;
    for(auto d : div) {
        ans += d - 1;
    }
    cout << ans << endl;

    return 0;
}
