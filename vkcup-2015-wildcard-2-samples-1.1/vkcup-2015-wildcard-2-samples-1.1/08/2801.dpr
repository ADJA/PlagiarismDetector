{$A8,B-,C+,D+,E-,F-,G+,H+,I+,J-,K-,L+,M-,N+,O-,P+,Q-,R+,S+,T-,U-,V+,W-,X+,Y+,Z1}
{$MINSTACKSIZE $00004000}
{$MAXSTACKSIZE $00100000}
{$IMAGEBASE $00400000}
{$APPTYPE CONSOLE}

const filename='e';
      oo=maxlongint div 2;
      eps=1e-6;
      eee=1e-21;

var qq,cc,a,aa:array[0..1000000]of int64;
    qc,he:array[0..2014,0..2014]of longint;
    s,ss,sss,s0,s1,s2,s3:string;
    res:int64;
    x,y,z,xx,yy,zz,x0,y0,z0,x1,x2,x3,y1,y2,y3,z1,z2,z3:extended;
    nt,ii,jj,n,m,q,c,q0,c0,q1,c1,q2,c2,q3,c3:longint;
    nn,mm,kk,u,v,cur,max,min:longint;
    test,ll,t,tt:longint;
    b,bb,bbb,b0,b1,b2,b3:boolean;





function mx(q,c:longint):longint;
  begin
  if q>c then mx:=q else mx:=c;
  end;


function mn(q,c:longint):longint;
  begin
  if q<c then mn:=q else mn:=c;
  end;


procedure init;
  begin
  assign(input,filename+'.in');
  assign(output,filename+'.out');
  reset(input);
  rewrite(output);
  end;


procedure fin;
  begin
  close(input);
  close(output);
  end;


procedure clear;
var i,j,k:longint;
  begin
  fillchar(qc,sizeof(qc),0);
  end;


procedure load;
var i,j,k:longint;
  begin
  end;


procedure save;
var i,j,k:longint;
  begin
  end;


procedure run;
var i,j,k:longint;
  begin
  //init;
  fillchar(qq,sizeof(qq),0);
  fillchar(cc,sizeof(cc),0);
  read(n);
  for i:=1 to n do read(qq[i-1]);
  for i:=1 to n-1 do dec(qq[i],qq[0]);
  qq[0]:=0;
  read(m);
  for i:=1 to m do
    begin
    read(k);
    inc(cc[k]);
    end;
  k:=m div (2*n-2);

  if n=2 then
    begin
    res:=qq[1]*(m-1);
    writeln(res);
    exit;
    end;

  res:=2*k*qq[n-1];
  for i:=1 to n do
    if ((i=1)or(i=n)) then dec(cc[i],k) else dec(cc[i],2*k);
  if (m mod (2*n-2)=0) then
    begin
    b:=false;
    for i:=1 to n-1 do
      if qq[i]-qq[i-1]<>qq[1]-qq[0] then b:=true;
    if b then
      begin
      writeln('-1'); exit;
      end
    else
      begin
      dec(res,qq[1]);
      writeln(res);
      exit;
      end;
    end;

  if ((cc[1]=1)and(cc[n]=1)) then
    begin
    q0:=1;
    c0:=n;
    while cc[q0+1]=2 do inc(q0);
    while cc[c0-1]=2 do dec(c0);
    inc(res,2*qq[n-1]);
    dec(res,qq[c0-1]-qq[q0-1]);
    writeln(res);
    exit;
    end;

  if ((cc[1]=1)and(cc[n]=0)) then
    begin
    q0:=1;
    c0:=1;
    while cc[q0+1]=2 do inc(q0);
    while cc[c0+1]>0 do inc(c0);
    inc(res,qq[q0-1]+qq[c0-1]);
    writeln(res);
    exit;
    end;

  if ((cc[1]=0)and(cc[n]=1)) then
    begin
    q0:=n;
    c0:=n;
    while cc[q0-1]=2 do dec(q0);
    while cc[c0-1]>0 do dec(c0);
    inc(res,2*qq[n-1]-qq[q0-1]-qq[c0-1]);
    writeln(res);
    exit;
    end;

  if ((cc[1]=0)and(cc[n]=0)) then
    begin
    q0:=1;
    c0:=n;
    while cc[q0+1]=0 do inc(q0);
    while cc[c0-1]=0 do dec(c0);
    inc(q0); dec(c0);
    inc(res,qq[c0-1]-qq[q0-1]);
    writeln(res);
    exit;
    end;


  //fin;
  end;


begin
nt:=1;
//readln(nt);
for test:=1 to nt do
  begin
  clear;
  load;
  run;
  save;
  end;
end.
