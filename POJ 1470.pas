{Problem: 1470		User: lzctuhao
Memory: 8764K		Time: 750MS
Language: Pascal		Result: Accepted}

{Tarjan算法
抄解题报告：
Tarjan算法基于深度优先搜索的框架，对于新搜索到的一个结点，首先创建由这个结点构成的集合，再对当前结点的每一个子树进行搜索，每搜索完一棵子树，则可确定子树内的LCA询问都已解决。其他的LCA询问的结果必然在这个子树之外，这时把子树所形成的集合与当前结点的集合合并，并将当前结点设为这个集合的祖先。之后继续搜索下一棵子树，直到当前结点的所有子树搜索完。这时把当前结点也设为已被检查过的，同时可以处理有关当前结点的LCA询问，如果有一个从当前结点到结点v的询问，且v已被检查过，则由于进行的是深度优先搜索，当前结点与v的最近公共祖先一定还没有被检查，而这个最近公共祖先的包涵v的子树一定已经搜索过了，那么这个最近公共祖先一定是v所在集合的祖先。}
 
//Tarjan
const
 num:set of char=['0'..'9'];
var
 m,n,father,l,r:longint;
 tree,q:array[1..1001,0..1001]of longint;
 tot,fa:array[0..1001]of longint;
 mark:array[1..1001]of boolean;
function getnum:longint;
var
 x:longint;
 c:char;
begin
 read(c);
 x:=0;
 while not (c in num) do read(c);
 while c in num do
  begin
  x:=x*10+ord(c)-48;
  read(c);
  end;
 exit(x);
end;
function getfather(x:longint):longint;
begin
 if fa[x]=x then exit(x)
 else
  begin
  fa[x]:=getfather(fa[x]);
  exit(fa[x]);
  end;
end;

procedure lca(x:longint);
var
 i:longint;
begin
 fa[x]:=x;
 for i:=1 to tree[x,0] do
  begin
  lca(tree[x,i]);
  fa[tree[x,i]]:=x;
  end;
 mark[x]:=true;
 for i:=1 to q[x,0] do
  if mark[q[x,i]] then inc(tot[getfather(q[x,i])]);
end;

procedure init;
var
 c:char;
 i,j,x,y,s:longint;
begin
 n:=getnum;
 for i:=1 to n do
  begin
  x:=getnum;
  s:=getnum;
  for j:=1 to s do
   begin
   y:=getnum;
   inc(tree[x,0]);
   tree[x,tree[x,0]]:=y;
   mark[y]:=true;
   end;
  end;
 m:=getnum;
 for i:=1 to m do
  begin
  l:=getnum;
  r:=getnum;
  inc(q[l,0]);
  q[l,q[l,0]]:=r;
  inc(q[r,0]);
  q[r,q[r,0]]:=l;
  end;
 for i:=1 to n do
  if not mark[i] then
  begin
  father:=i;
  break;
  end;
 fillchar(mark,sizeof(mark),0);
 lca(father);
 for i:=1 to n do
  if tot[i]<>0 then writeln(i,':',tot[i]);
end;
begin
 while not seekeof do
  begin
  fillchar(fa,sizeof(fa),0);
  fillchar(tree,sizeof(tree),0);
  fillchar(q,sizeof(q),0);
  fillchar(tot,sizeof(tot),0);
  fillchar(mark,sizeof(mark),0);
  init;
 end;
end.
