{Problem: 2411		User: lzctuhao
Memory: 1296K		Time: 375MS
Language: Pascal		Result: Accepted}

var
  h,w:longint;
  f:array[0..12,0..1 shl 12]of int64;

function check(x,y:longint):boolean;
var
  i,j,k:longint;
begin
  if x or y<>1 shl w-1 then exit(false);
  for i:=1 to w do
    if x and (1 shl (i-1))=0 then begin
      if y and (1 shl (i-1))=0 then exit(false)
      else y:=y xor (1 shl (i-1));
  end;
  while y>0 do begin
    k:=y and (-y);
    if y and (k shl 1)=0 then exit(false)
    else dec(y,k+k*2);
  end;

  exit(true);
end;
procedure dp;
var
  k,i,j:longint;
begin
  fillchar(f,sizeof(f),0);
  f[0,1 shl w-1]:=1;
  for i:=1 to h do
    for k:=0 to 1 shl w-1 do
      if f[i-1,k]>0 then
       for j:=0 to 1 shl w-1 do
        if check(k,j)then f[i,j]:=f[i,j]+f[i-1,k];

  writeln(f[h,1 shl w-1]);
end;
begin

  while true do begin
    readln(h,w);
    if (h=0)and(w=0)then break;
    if(h*w) mod 2<>0 then begin
      writeln(0);
      continue;
    end;
    dp;
  end;

end.
