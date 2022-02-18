#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

const int maxn = 1e5 + 10;
const double eps = 1e-8;

struct node {
    int id;
    double k, r, x, a, b, ans;
    inline double X() const {
        return ans / (a * r + b);
    }
    inline double Y() const {
        return r * ans / (a * r + b);
    }
} a[maxn], q[maxn];
inline bool cmpx(const node &a, const node &b) {
    return a.X() < b.X();
}
inline bool cmpk(const node &a, const node &b) {
    return a.k < b.k;
}
inline bool cmpid(const node &a, const node &b) {
    return a.id < b.id;
}
inline double slope(const node &a, const node &b) {
    if (b.X() - a.X() < eps)
        return 1e18;

    return (b.Y() - a.Y()) / (b.X() - a.X());
}

void cdq(int l, int r) {
    if (l == r) {
        a[l].ans = std::max(a[l - 1].ans, a[l].ans);
        return;
    }

    int mid = (l + r) / 2;
    cdq(l, mid);
    std::sort(a + l, a + mid + 1, cmpx);
    int top = 0;

    for (int i = l; i <= mid; i++) {
        while (top > 1 && slope(q[top - 1], q[top]) < slope(q[top], a[i]))
            top--;

        q[++top] = a[i];
    }

    std::sort(a + mid + 1, a + r + 1, cmpk);

    for (int i = mid + 1; i <= r; i++) {
        while (top > 1 && slope(q[top - 1], q[top]) < a[i].k)
            top--;

        a[i].ans = std::max(a[i].ans, (q[top].Y() - q[top].X() * a[i].k) * a[i].a);
    }

    std::sort(a + l, a + r + 1, cmpid);
    cdq(mid + 1, r);
}

int n;

int main() {
    scanf("%d", &n);
    scanf("%lf", &a[1].ans);

    for (int i = 1; i <= n; i++) {
        double x, y, r;
        scanf("%lf%lf%lf", &x, &y, &r);
        a[i].a = x, a[i].b = y, a[i].r = r, a[i].k = -y / x;
        a[i].id = i;
    }

    cdq(1, n);

    for (int i = 1; i <= n; i++)
        if (a[i].id == n)
            printf("%.8lf\n", a[i].ans);
}
