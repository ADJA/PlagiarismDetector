s=raw_input()
n=len(s)
strawberry=[0]*n
g=[0]*n
'''
AB->BA
No Other AB
'''
# 0=A
strawberry[0]=1
for i in xrange(0,n-1):
    if (s[i]=='A') and (s[i+1]=='A'):
        strawberry[i+1]+=g[i]
        strawberry[i+1]+=strawberry[i]
    if (s[i]=='A') and (s[i+1]=='B'):
        strawberry[i+1]+=strawberry[i]
        strawberry[i+1]+=g[i]
        g[i+1]+=g[i]
    if (s[i]=='B') and (s[i+1]=='A'):
        g[i+1]+=strawberry[i]
        strawberry[i+1]+=g[i]
    if (s[i]=='B') and (s[i+1]=='B'):
        strawberry[i+1]+=g[i]
        g[i+1]+=g[i]
ans=0
if s[n-1]=='B':
    ans+=g[n-1]
else:
    ans=strawberry[n-1]+g[n-1]
strawberry=[0]*n
g=[0]*n
# 0=B
g[0]=1
for i in xrange(0,n-1):
    if (s[i]=='A') and (s[i+1]=='A'):
        strawberry[i+1]+=g[i]
        strawberry[i+1]+=strawberry[i]
    if (s[i]=='A') and (s[i+1]=='B'):
        strawberry[i+1]+=strawberry[i]
        strawberry[i+1]+=g[i]
        g[i+1]+=g[i]
    if (s[i]=='B') and (s[i+1]=='A'):
        g[i+1]+=strawberry[i]
        strawberry[i+1]+=g[i]
    if (s[i]=='B') and (s[i+1]=='B'):
        strawberry[i+1]+=g[i]
        g[i+1]+=g[i]
if (s[0]=='A') and (s[n-1]=='B'):
    ans+=strawberry[n-1]
elif (s[0]=='B'):
    ans+=g[n-1]
print ans