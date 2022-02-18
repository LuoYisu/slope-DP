#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

const int maxn = 1e6 + 10;
typedef long long ll;

int a[maxn];
ll sum[maxn];
int n;
int A, B, C;

struct node {
    ll x, y;
} q[maxn];
int l = 1, r = 1;

ll f[maxn];

inline double slope(const node &a, const node &b) {
    return 1.0 * (b.y - a.y) / (b.x - a.x);
}

int main() {
    scanf("%d", &n);
    scanf("%d%d%d", &A, &B, &C);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), sum[i] = a[i] + sum[i - 1];

    for (int i = 1; i <= n; i++) {
        ll k = 2 * A * sum[i];

        while (l < r && slope(q[l], q[l + 1]) > k)
            l++;

        f[i] = -q[l].x * k + q[l].y + sum[i] * sum[i] * A + sum[i] * B + C;
        node now = {sum[i], f[i] + sum[i] *sum[i] *A - sum[i] *B};

        while (l < r && slope(q[r - 1], q[r]) < slope(q[r], now))
            r--;

        q[++r] = now;
    }

    cout << f[n] << endl;

}
