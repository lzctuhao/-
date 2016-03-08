{Problem: 2342		User: lzctuhao
Memory: 1600K		Time: 219MS
Language: G++		Result: Accepted}

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> G[10000];
int fa[10000], vis[10000], val[10000];
int dp[10000][2];
int root;
void dfs(int u)
{
  vis[u] = 1;
  dp[u][0] = 0; dp[u][1] = val[u];
  for(int i=0; i<G[u].size(); ++i)
  {
    int v = G[u][i];
    if(!vis[v]) dfs(v);
    dp[u][0] += max(dp[v][0], dp[v][1]);
    dp[u][1] += dp[v][0];
  }
}
int main()
{
  int n, i, u, v;
  cin>>n;
  for(i=1; i<=n; ++i) cin>>val[i];
  while(~scanf("%d%d", &u, &v))
  {
    if(u==0&&v==0) break;
    fa[u] = v;
    G[v].push_back(u);
  }

  for(i=1; fa[i]; ++i);
  dfs(root=i);
  cout<<max(dp[root][0], dp[root][1]);
  return 0;
}
