program ZAD_B;

{$APPTYPE CONSOLE}

uses
  SysUtils;
const
   md = 1000000007;
var
   s,t,s1:string;
   dp,dd:array [1..4001000] of integer;
   bol:array [1..4001000] of boolean;
   n1,i1,j1,sss,n,m,i,j,p,lt, qq:integer;
   kss:int64;
begin
   readln(m,n);
   readln(t);
   qq := 1;
   lt:=length(t);
   for i:=1 to n do read(dd[i]);
   readln;
   s:='';
   for i:=1 to m do s:=s+'.';
   for i:=1 to n do
      if (dd[i]+lt-1<=m) then
         begin
            p:=lt;
            for j:=dd[i]+lt-1 downto dd[i] do
               begin
                  if (s[j]<>'.') then break;
                  s[j]:=t[p];
                  dec(p);
               end;
         end;
   for i1:=1 to 1001000 do bol[i1]:=true;
   n1:=length(t);
   s1:=s;
   s:=t+'$'+s;
   dp[1]:=0;
   for i1:=2 to length(s) do
      begin
         j1:=dp[i1-1];
         while (j1>0) and (s[j1+1]<>s[i1]) do j1:=dp[j1];
         if (s[j1+1]=s[i1]) then inc(j1);
         dp[i1]:=j1;
         if (dp[i1]=n1) then bol[i1-n1-n1]:=false;
      end;
   s:=s1;
   for i1:=1 to n do
      if (bol[dd[i1]]) then
         begin
            writeln(0);
            readln;
            halt;
         end;
   sss:=0;
   for i1:=1 to length(s) do
      if (s[i1]='.') then inc(sss);
   kss:=1;
   for i1:=1 to sss do kss:=trunc(1.0*kss*26) mod md;
   writeln(kss);
   readln;
end.
