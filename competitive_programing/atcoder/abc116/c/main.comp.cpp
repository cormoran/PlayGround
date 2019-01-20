#include <bits/stdc++.h>
using namespace std;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }

int main() {
    int N; cin >> N;
    vector<int> H(N); cin >> H;

    int ans = H[0];
    rep(i, N - 1) if(H[i] < H[i + 1]) ans += H[i + 1] - H[i];

    cout << ans << endl;
    return 0;
}
