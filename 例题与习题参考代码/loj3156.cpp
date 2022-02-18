#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cctype>
#include <queue>
#include <cassert>
#include <cmath>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

const int maxn = 1e6 + 10;
const int maxm = 1e5 + 10;
const int maxt = 4e4 + 10;
const double eps = 1e-9, inf = 1e18;
const int mod = 1e9 + 7;
typedef long long ll;

std::deque<int> q[maxm];
std::vector<int> bg[maxn];
std::vector<int> upd[maxn];
ll A, B, C;

struct node {
    int u, v, s, t;
    ll ans;
    inline ll X() const {
        return t;
    }
    inline ll Y() const {
        return ans + A * t * t - t * B;
    }
} a[maxn];

double slope(const node &a, const node &b) {
    if (std::abs(b.X() - a.X()) < eps)
        return (b.Y() - a.Y() > 0) ? inf : -inf;

    return 1.0 * (b.Y() - a.Y()) / (b.X() - a.X());
}

ll read() {
    ll x = 0, f = 1;
    char ch = getchar();

    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;

    for (; isdigit(ch); ch = getchar())
        x = x * 10 + ch - '0';

    return x * f;
}

int main() {
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
    int n = read(), m = read();
    A = read(), B = read(), C = read();
    int mxt = 0;

    for (int i = 1; i <= m; i++) {
        a[i].u = read(), a[i].v = read(), a[i].s = read(), a[i].t = read();
        bg[a[i].s].push_back(i), mxt = std::max(mxt, a[i].t);
    }

    ll ans = 1e18;

    for (int i = 0; i <= mxt; i++) {
        for (int j : upd[i]) {
            int nxt = a[j].v;

            while (q[nxt].size() > 1 &&
                    slope(a[q[nxt][q[nxt].size() - 2]], a[q[nxt].back()]) >= slope(a[q[nxt][q[nxt].size() - 2]], a[j]))
                q[nxt].pop_back();

            q[nxt].push_back(j);
        }

        for (int j : bg[i]) {
            double k = 2.0 * i * A;
            int now = a[j].u;

            while (q[now].size() > 1 && slope(a[q[now][0]], a[q[now][1]]) < k)
                q[now].pop_front();

            if (q[now].size() < 1 && a[j].u != 1)
                continue;

            int r = (q[now].size() < 1 && a[j].u == 1) ? 0 : q[now].front();
            a[j].ans = a[r].ans + (a[j].s - a[r].t) * (a[j].s - a[r].t) * A + (a[j].s - a[r].t) * B + C;
            upd[a[j].t].push_back(j);

            if (a[j].v == n)
                ans = std::min(ans, a[j].ans + a[j].t);
        }
    }

    cout << ans << endl;
}
