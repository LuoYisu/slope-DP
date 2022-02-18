#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>
#include <cctype>
using namespace std;

const int maxn = 5e5 + 10;
typedef long long ll;

inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();

    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;

    for (; isdigit(ch); ch = getchar())
        x = x * 10 + ch - '0';

    return x * f;
}

int n, m;
ll c0;

struct node {
    ll x, c;
} a[maxn], planet[maxn];

vector<int> e[maxn];
inline void add(int x, int y) {
    e[x].push_back(y);
}
int dfn[maxn], cnt;

int bg[maxn], ed[maxn];

struct M {
    int x, y;
    int id;
    bool operator<(const M &b) const {
        return planet[id].x == planet[b.id].x ? planet[id].c < planet[b.id].c : planet[id].x < planet[b.id].x;
    }
};

vector<int> in[maxn], out[maxn];

void dfs(int x) {
    dfn[x] = ++cnt;

    if (bg[x])
        in[bg[x]].push_back(cnt);

    if (ed[x])
        out[ed[x]].push_back(cnt - 1);

    for (int v : e[x])
        dfs(v);

    if (bg[x])
        out[bg[x]].push_back(cnt);

    if (ed[x])
        in[ed[x]].push_back(cnt + 1);
}

struct Q {
    int u, x, id;
    ll ans;
    bool operator<(const Q &b) const {
        return x < b.x;
    }
} q[maxn];
bool cmp_id(const Q &a, const Q &b) {
    return a.id < b.id;
}

struct point {
    ll x, y;
    int id;
    point operator-(const point &b) const {
        return {x - b.x, y - b.y, id};
    }
    ll operator&(const point &b) const {
        return x * b.y - y * b.x;
    }
};

vector<point> hull[maxn << 2];
int hd[maxn << 2];
inline int ls(int x) {
    return x * 2;
}
inline int rs(int x) {
    return x * 2 + 1;
}

void modify(int l, int r, int x, int y, const node &v, int id, int k) {
    if (l >= x && r <= y) {
        point p = {v.x * 2, v.x *v.x + v.c, id};

        while (hull[k].size() > 1 &&
                ((p - hull[k][hull[k].size() - 2]) & (hull[k].back() - hull[k][hull[k].size() - 2])) >= 0)
            hull[k].pop_back();

        hull[k].push_back(p);
        return;
    }

    int mid = (l + r) / 2;

    if (x <= mid)
        modify(l, mid, x, y, v, id, ls(k));

    if (y > mid)
        modify(mid + 1, r, x, y, v, id, rs(k));
}

inline ll pow_2(ll x) {
    return x * x;
}

ll query(int l, int r, int x, const Q &q, int k) {
    ll ans = 1ll << 60;

    if (hull[k].size()) {
        while (hd[k] < (int)hull[k].size() - 1 &&
                hull[k][hd[k] + 1].y - hull[k][hd[k]].y <= q.x * (hull[k][hd[k] + 1].x - hull[k][hd[k]].x))
            hd[k]++;

        ans = min(ans, planet[hull[k][hd[k]].id].c + pow_2(planet[hull[k][hd[k]].id].x - q.x));
    }

    if (l == r)
        return ans;

    int mid = (l + r) / 2;

    if (x <= mid)
        return min(ans, query(l, mid, x, q, ls(k)));
    else
        return min(ans, query(mid + 1, r, x, q, rs(k)));
}

void input() {
    n = read(), m = read(), c0 = read();

    for (int i = 2; i <= n; i++) {
        int opt = read();

        if (opt == 0) {
            int f = read() + 1;
            add(f, i);
            int id = read(), y, z;
            a[i].x = read(), y = read(), z = read(), a[i].c = read();
            //y++, z++;
            bg[i] = id;
            planet[id] = a[i];
        } else {
            int f = read() + 1;
            add(f, i);
            int id = read();
            ed[i] = id;
        }
    }

    for (int i = 1; i <= m; i++)
        q[i].u = read() + 1, q[i].x = read(), q[i].id = i;
}

void build() {
    vector<M> pool;
    pool.push_back({1, n, 0});
    planet[0].c = c0;
    planet[0].x = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (int)in[i].size(); j++) {
            int x = in[i][j], y = out[i][j];
            pool.push_back({x, y, i});
        }

    for (int i = 1; i <= n; i++)
        vector<int>().swap(in[i]), vector<int>().swap(out[i]);

    sort(pool.begin(), pool.end());

    for (auto k : pool)
        if (k.x <= k.y)
            modify(1, n, k.x, k.y, planet[k.id], k.id, 1);

    vector<M>().swap(pool);
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    input();
    dfs(1);
    build();
    sort(q + 1, q + 1 + m);

    for (int i = 1; i <= m; i++) {
        q[i].ans = query(1, n, dfn[q[i].u], q[i], 1);
    }

    sort(q + 1, q + 1 + m, cmp_id);

    for (int i = 1; i <= m; i++)
        printf("%lld\n", q[i].ans);
}
