#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c; cin >> a >> b >> c;

    cout << (long long)(sqrt(pow(a * a + b * b + c * c, 2) - 2 * (pow(a, 4) + pow(b, 4) + pow(c, 4))) + 1e-9) / 4 << endl;

    return 0;
}
