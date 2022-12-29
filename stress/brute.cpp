#include<bits/stdc++.h>
#define ll int64_t
using namespace std;
#define N 200005
ll a[N],add[N];

void go(){
    ll n,st,ed;
    scanf("%lld%lld%lld",&n,&st,&ed);
    for(ll i=1;i<=n;i++) scanf("%lld",a+i);
    sort(a+1,a+n+1);
    a[n+1]=ed;
    for(ll i=0;i<=n;i++) add[i]=2*i-n;
    ll i=0,steps=0;
    while(st<=ed){
        while(i<=n&&a[i+1]<=st+i) i++;
        if(st+i>=ed){
            steps+=ed-st;
            printf("%lld\n",steps);
            return;
        }
        if(add[i]<=0){
            puts("-1");
            return;
        }
        ll k=(min(a[i+1],ed)-st-i)/add[i];
        if(k<1) k=1;
        steps+=k*n;
        st+=k*add[i];
    }
}

main(){
    int T;
    scanf("%d",&T);
    while(T--) go();
}