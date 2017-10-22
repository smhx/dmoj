K = int(input())
s = []
for _ in range(0, K):
        x = int(input())
        if (x==0):
            s.pop()
        else:
            s.append(x)
ans = 0
while s.size() > 0:
    ans = ans + s[s.size()-1]
    s.pop()
print(ans)
    