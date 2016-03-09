/*Source Code

Problem: 1325		User: lzctuhao
Memory: 1652K		Time: 47MS
Language: C++		Result: Accepted*/

#include<iostream>
#include<string.h>
using namespace std;
int n,m,y[600],g[600][600],lk[600],ans=0,k,hh,a,b;
 
bool find(int v)
{
    for(int i=1; i<=m; i++)
        if(g[v][i] && !y[i])
        {
            y[i]=1;
            if(lk[i]==0 || find(lk[i]))
            {
                lk[i]=v;
                return true;
            }
        }
    return false;
}
 
int main()
{
    ios::sync_with_stdio(0);
    while(cin>>n, n)
    {
    	memset(y,0,sizeof(y));
    	memset(g,0,sizeof(g));
    	memset(lk,0,sizeof(lk));
    	ans=0;
    	cin>>m>>k;
    	for(int i=1; i<=k; i++)
    	{
        	cin>>hh>>a>>b;
        	g[a][b]=1;
    	} 
    	for(int i=1; i<=n; i++)
    	{
        	memset(y,0,sizeof(y));
        	if(find(i)) ans++;
    	}
    	cout<<ans<<endl;
	}
    	return 0;
}
/*lzctuhao提示你:
n,m分别为2部图两边节点的个数，两边的节点分别用1..n,1..m编号
g[x][y]表示x,y两个点之间有边相连
y[i]记录的是y中的i节点是否被访问过.
lk[y]记录的是当前与y节点相连的x节点*/
