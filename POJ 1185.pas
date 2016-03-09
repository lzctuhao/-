{Source Code

Problem: 1185		User: lzctuhao
Memory: 2932K		Time: 938MS
Language: Pascal		Result: Accepted}

var
  tot,n,m:longint;
  data,sum:array[1..71]of longint;
  f:array[0..100,0..71,0..71]of longint;
  g:Array[0..101]of longint;
function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;
procedure dfs(x,step,now:longint);
var
  t1,t2,t3:longint;
begin
  if step>m then begin
  t1:=x;
  t2:=t1 shl 1;
  t3:=t2 shl 1;
  if (t1 and t2<>0)or(t1 and t3<>0)or(t2 and t3<>0)then exit;
  inc(tot);
  data[tot]:=t1;
  sum[tot]:=now;
  exit;
  end;

  t1:=1 shl (step-1);
  dfs(x,step+1,now);
  dfs(x or t1,step+2,now+1);
end;
procedure init;
var
  x:char;
  i,j,k,t1,t2,t3:longint;
begin
  readln(n,m);
  fillchar(g,sizeof(g),0);
  for i:=1 to n do begin
    for j:=1 to m do begin
      read(x);
      if x='H'then g[i]:=g[i] or (1 shl (j-1));
    end;
    readln;
  end;
  tot:=0;
  dfs(0,1,0);
end;
procedure dp;
var
  ans,i,j,k,p,inf:longint;
begin

  fillchar(f,sizeof(f),200);
  for i:=1 to tot do
    if (data[i] and g[1]=0) then f[1,1,i]:=sum[i];


  for i:=2 to n do
    for j:=1 to tot do
      for k:=1 to tot do
        for p:=1 to tot do
        if (data[j] and g[i-2]=0)and
           (data[k] and g[i-1]=0)and
           (data[p] and g[i]=0)and
           (data[j] and data[k]=0)and
           (data[j] and data[p]=0)and
           (data[k] and data[p]=0)then
             f[i,k,p]:=max(f[i-1,j,k]+sum[p],f[i,k,p]);

  ans:=-2147483647;
  for i:=1 to tot do
    for j:=1 to tot do
      ans:=max(ans,f[n,i,j]);
  writeln(ans);
end;
begin
 
  init;
  dp;
end.
