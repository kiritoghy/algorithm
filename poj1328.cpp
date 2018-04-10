#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
 
const int maxn = 1001;
 
struct Point
{
    int x, y;
} point[maxn];
 
int n, d, ans;
bool ok;
 
bool operator < (const Point &a, const Point &b)
{
    return a.x < b.x;
}
 
bool operator == (const Point &a, const Point &b)
{
    return ((a.x == b.x) && (a.y == b.y));
}
 
void init()
{
    int i;
 
    ok = true;
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &point[i].x, &point[i].y);
        if (point[i].y > d)
            ok = false;
    }
}
 
double getx(Point &a)
{
    return a.x + sqrt(double(d * d - a.y * a.y));
}
 
void work()
{
    int i;
    double x=getx(point[0]);
 
    ans = 1;
    for (i = 1; i < n; i++)
    {
        double  temp = getx(point[i]);
        if (point[i].x < x && x > temp)
        {
            x = temp;
            continue;
        }
        if (point[i].y * point[i].y + (point[i].x - x) * (point[i].x - x) <= d * d)
            continue;
        x = getx(point[i]);
        ans++;
    }
}
 
int main()
{
    int casenum = 0;
 
    while (scanf("%d%d",&n, &d) && (d || n))
    {
        casenum++;
        init();
        if (!ok)
        {
            printf("Case %d: -1\n", casenum);
            continue;
        }
        sort(point, point + n);
        work();
        printf("Case %d: %d\n", casenum, ans);
    }
    return 0;
}
