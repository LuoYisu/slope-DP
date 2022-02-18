#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;

const int maxn = 2e5 + 10;
typedef long long ll;

int a[maxn], n;
ll sum[maxn];

struct node {
    ll x, y;
    node() {
        x = y = 0;
    }
    node(ll x_, ll y_) {
        x = x_, y = y_;
    }
} p[maxn];
int top = 0;

inline double slope(const node &x, const node &y) {
    return (double)(double(y.y - x.y)) / (double(y.x - x.x));
}

node solve(ll x) {
    int l = 2, r = top, ans = 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        //cout << slope(p[mid - 1], p[mid]) << endl;
        if (slope(p[mid - 1], p[mid]) <= double(x))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }

    return p[ans];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;
    ll res = 0;

    for (int i = 1; i <= n; i++)
        cin >> a[i], sum[i] = sum[i - 1] + a[i], res += 1ll * a[i] * i;

    top = 1;

    for (int i = 1; i <= n; i++) {
        node now(i, sum[i]);

        while (top > 1 && slope(p[top - 1], p[top]) >= slope(p[top], now))
            top--;

        p[++top] = now;
    }

    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        auto now = solve(a[i]);
        ans = std::max(ans, -now.y + now.x * a[i] - 1ll * i * a[i] + sum[i]);
    }

    cout << res + ans << endl;
}
