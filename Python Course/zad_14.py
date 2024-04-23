def L(T,V,A,B):
    return (T*(B-1)+V*2*A)/(A*B*(B-1))
def P(T,V,A,B):
    return (2*2*(T+V))/(B*(2*A+B-1))
def check(T,V,A,B):
    return T/A/B > 2 * (T+V)/(B*(2*A+B-1)) and L(T,V,A,B) > P(T,V,A,B) and A>=B
for i in range(1,40):
    for j in range(1,40):
        for k in range(1,40):
            for l in range(1,40):
                if check(i,j,k,l):
                    print(i,j,k,l)
                    print(L(i,j,k,l),P(i,j,k,l))
                    print()