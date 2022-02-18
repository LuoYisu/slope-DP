#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
using std::cout;
using std::endl;

const int maxn = 5e4 + 10;
typedef long long ll;

int n;
double L;

struct node {
    double x, y;
    int i;
    node() {}
    node(double x_, double y_, int i_) : x(x_), y(y_), i(i_) {}
};

inline double slope(const node &x, const node &y) {
    return 1.0 * (y.y - x.y) / (y.x - x.x);
}

double c[maxn], f[maxn], s[maxn], sum[maxn];
node q[maxn];

int main() {
    scanf("%d%lf", &n, &L);
    L++;

    for (int i = 1; i <= n; i++)
        scanf("%lf", &c[i]), sum[i] = sum[i - 1] + c[i], s[i] = sum[i] + i;

    int l = 1, r = 1;

    for (int i = 1; i <= n; i++) {
        int k = 2 * (s[i] - L);

        while (l < r && slope(q[l], q[l + 1]) < k)
            l++;

        int id = q[l].i;
        f[i] = f[id] + (s[i] - s[id] - L) * (s[i] - s[id] - L);
        node p(s[i], f[i] + s[i] * s[i], i);

        while (l < r && slope(p, q[r - 1]) < slope(q[r - 1], q[r]))
            r--;

        q[++r] = p;
    }

    printf("%lld\n", ll(f[n]));
    return 0;
}
