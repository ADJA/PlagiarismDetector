n,k=map(int,raw_input().split())
lis=raw_input().split()
flag=False
for ii in range(k):
    if flag:
        break
    pro=[]
    for j in range(ii,n,k):
        if lis[j]=='?':
            pro.append('?')
        else:
            pro.append(int(lis[j]))
    l=len(pro)
    can=[]
    for i in range(l):
        if pro[i]!='?':
            can.append(i)
    if len(can)==0:
        cur=0
        for i in range(l):
            pro[i]=cur
            if cur>=0:
                cur=-1-cur
            else:
                cur=-cur
    else:
        if(pro[can[0]]>0):
            cur=0
            for i in range(can[0]):
                pro[i]=cur
                if(cur>=0):
                    cur=-1-cur
                else:
                    cur=-cur
                    if(cur>=pro[can[0]]):
                        cur=-1-cur
        else:
            for i in range(can[0]):
                pro[i]=pro[can[0]]-1-i
        if pro[can[-1]]>=0:
            for i in range(can[-1]+1,l):
                pro[i]=pro[can[-1]]+i-can[-1]
        else:
            cur=0
            for i in range(can[-1]+1,l):
                pro[i]=cur
                if(cur<=0):
                    cur=1-cur
                else:
                    cur=-cur
                    if cur<=pro[can[-1]]:
                        cur=1-cur
        for j in range(len(can)-1):
            x=can[j]
            y=can[j+1]
            if pro[y]-pro[x]<y-x:
                flag=True
                break
            if pro[x]>=0:
                for i in range(x+1,y):
                    pro[i]=pro[x]+i-x
            elif pro[y]<=0:
                for i in range(x+1,y):
                    pro[i]=pro[y]-(i-x)
                    #print pro[i],y,pro[y]-1-i
            else:
                cur=0
                for i in range(x+1,y):
                    pro[i]=cur
                    if cur>=0:
                        cur=-1-cur
                        if cur<=pro[x]:
                            cur=-cur
                    else:
                        cur=-cur
                        if cur>=pro[y]:
                            cur=-1-cur
    pro.sort()
    for i in range(ii,n,k):
        lis[i]=pro[i/k]
        #print lis[ii]
if flag:
    print "Incorrect sequence"
else:
    for i in lis:
        print i,