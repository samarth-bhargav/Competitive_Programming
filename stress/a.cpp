#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb emplace_back
#define mk make_pair
const int mod=998244353;

inline int add(int x,int y)
{
    int res=x+y;
    if(res<0)return res+mod;
    return res<mod?res:res-mod;
}
inline int mul(int x,int y)
{
    return (ll)x*y%mod;
}
inline int qpow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)res=mul(res,a);
        a=mul(a,a),b>>=1;
    }
    return res;
}
int f[1<<17][18];
inline int lb(int x)
{
    return x&-x;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    string s;
    cin>>s;
    s=" "+s;
    int tot=0;
    for(int i=1;i<=n;i++)if(s[i]=='?')tot++;
    for(int i=1;i<=n;i++)
    {
        for(int o=0;o<=1;o++)
        {
            int cnt=tot,S=0;
            for(int l=i,r=i+o;l&&r<=n;l--,r++)
            {
                if(s[l]=='?'&&s[r]=='?')cnt-=(l!=r);
                else
                {
                    if(s[l]=='?')S|=1<<s[r]-'a',cnt--;
                    if(s[r]=='?')S|=1<<s[l]-'a',cnt--;
                    if(s[l]!='?'&&s[r]!='?')if(s[l]!=s[r])break;
                }
                for(int i=1;i<=17;i++)f[S][i]=add(f[S][i],qpow(i,cnt));
            }
        }
    }
    int stot=1<<17;
    for(int k=1,b=1;k<=17;k++,b<<=1)
        for(int S=1;S<stot;S++)
            if(S&b)for(int i=1;i<=17;i++)f[S][i]=add(f[S][i],f[S^b][i]);
    int m;
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        string t;
        cin>>t;
        int S=0;
        for(int j=0;j<t.size();j++)S|=1<<t[j]-'a';
        cout<<f[S][t.size()]<<"\n";
    }
    return 0;
}