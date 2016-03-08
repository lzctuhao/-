#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int n,q1,q2;
int f[10010],a[10010];
bool c[10010],flag[10010];
vector<int> tree[10010];

int find(int k)
{
    if (f[k]==k) return k;
    f[k]=find(f[k]);
    return f[k];
}

int unions(int x,int y)
{
    int xx=find(x),yy=find(y);
    f[yy]=xx;
    return 0;
}

int tarjan(int u)
{
    //f[u]=u;
    for (int i=0;i<tree[u].size();i++)
    {
        tarjan(tree[u][i]);
        unions(u,tree[u][i]);
        a[find(u)]=u;
    }
    c[u]=1;
    if (q1==u && c[q2]) printf("%d\n",a[find(q2)]);
    else if (q2==u && c[q1]) printf("%d\n",a[find(q1)]);
    return 0;
}

int main()
{
    int cases;
    scanf("%d",&cases);
    while (cases--)
    {
          scanf("%d",&n);
          for (int i=1;i<=n;i++)
          {
              tree[i].clear();
              f[i]=i;
              a[i]=0;
              c[i]=0;
              flag[i]=1;
          }
          for (int i=1;i<n;i++)
          {
              int x,y;
              scanf("%d%d",&x,&y);
              flag[y]=0;
              tree[x].push_back(y);
          }
          scanf("%d%d",&q1,&q2);
          int i;
          for (i=1;i<=n;i++)
              if (flag[i]) break;
          tarjan(i);
    }
    system("pause");
    return 0;
}
