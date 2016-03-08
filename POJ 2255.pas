{Problem: 2255		User: lzctuhao
Memory: 884K		Time: 0MS
Language: Pascal		Result: Accepted}

var sx,sz,t:string;
  i,len:longint;
procedure work(sx,sz:string);{sx front    sz middle}
var l,k:integer;
begin
    if sx<>'' then
    begin
        l:=length(sx);
        k:=pos(sx[1],sz);
        work(copy(sx,2,k-1),copy(sz,1,k-1));   //left
        work(copy(sx,k+1,l-k),copy(sz,k+1,l-k));  //right
        write(sx[1]);
    end;
end;

begin
  while not eof do
  begin
    readln(t);
    len:=(length(t)-1) div 2;
    sx:=copy(t,1,len);
    sz:=copy(t,len+2,len*2+1);
    work(sx,sz);
    writeln;
  end;
end.
