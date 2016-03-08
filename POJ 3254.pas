{Problem: 3254		User: lzctuhao
Memory: 1552K		Time: 0MS
Language: Pascal		Result: Accepted}

var
  data:array[1..1 shl 16]of longint;
  g:array[1..16]of longint;
  f:array[0..16,0..10001]of longint;
  n,m,num:longint;
procedure init;
var
  i,j,k,x,y:longint;
begin
  readln(n,m);
  fillchar(g,sizeof(g),0);
  for i:=1 to n do begin
    for j:=1 to m do begin
      read(k);
      if k=0 then inc(g[i],1 shl (m-j));
    end;
    readln;
  end;

  num:=0;
  for i:=0 to 1 shl m-1 do
    if i and (i shl 1)=0 then begin
      inc(num);
      data[num]:=i;
    end;
end;
procedure dp;
var
  ans,i,j,k:longint;
begin
  fillchar(f,sizeof(f),0);

  for i:=1 to num do
    if g[1] and data[i]=0 then f[1,i]:=1;

  for i:=2 to n do
    for j:=1 to num do
      if data[j] and g[i]=0 then
        for k:=1 to num do begin
          if g[i-1] and data[k]<>0 then continue;
          if data[j] and data[k]<>0 then continue;
          f[i,j]:=f[i,j]+f[i-1,k];
          f[i,j]:=f[i,j] mod 100000000;
        end;

  ans:=0;
  for i:=1 to num do
    ans:=(ans+f[n,i])mod 100000000;
  writeln(ans);
end;
begin

  init;
  dp;
 
end.
