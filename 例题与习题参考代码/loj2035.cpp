#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

typedef long long ll;
const int maxn = 3010;
const ll inf = 1ll << 60;

struct node {
    ll x, y, i;
    node() {}
    node(ll x_, ll y_, ll i_) : x(x_), y(y_), i(i_) {}
};

inline double slope(const node &a, const node &b) {
    return 1.0 * (a.y - b.y) / (a.x - b.x);
}

int n, m;
ll s[maxn], f[maxn][maxn], a[maxn];
node q[maxn];

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i];

    memset(f, 1, sizeof(f));

    for (int i = 1; i <= n; i++)
        f[1][i] = s[i] * s[i];

    f[1][0] = 0;

    for (int i = 2; i <= m; i++) {
        int l = 1, r = 1;
        q[l] = node(0, 0, 0);

        for (int j = 1; j <= n; j++) {
            int k = 2 * s[j];

            while (l < r && slope(q[l], q[l + 1]) < k)
                l++;

            int id = q[l].i;
            f[i][j] = f[i - 1][id] + (s[j] - s[id]) * (s[j] - s[id]);
            node p(s[j], f[i - 1][j] + s[j] * s[j], j);

            while (l < r && slope(q[r], q[r - 1]) > slope(q[r - 1], p))
                r--;

            q[++r] = p;
        }
    }

    printf("%lld\n", f[m][n] * m - s[n] * s[n]);
    return 0;
}
