/*
Author: QAQAutoMaton
Lang: C++
Code: E.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define int long long
#define debug(qaq...) fprintf(stderr,qaq)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
#define unq(a) sort(all(a)),a.erase(unique(all(a)),a.end())
using namespace std;
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> cp;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T,class T2>int chkmin(T &a,T2 b){return a>b?a=b,1:0;}
template<class T,class T2>int chkmax(T &a,T2 b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T,class T2>T mmin(T a,T2 b){return a<b?a:b;}
template<class T,class T2>T mmax(T a,T2 b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
template<class T>bool sort2(T &a,T &b){return a>b?swap(a,b),1:0;}
template<class T,class ...T2>T mmin(T a,T2 ...b){return mmin(a,mmin(b...));}
template<class T,class ...T2>T mmax(T a,T2 ...b){return mmax(a,mmax(b...));}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
    __INIT__(){
        fill((unsigned char*)&inf,(unsigned char*)&inf+sizeof(inf),0x3f);
    }
}__INIT___;
namespace io {
    const int SIZE = (1 << 21) + 1;
    char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
    // getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
    // print the remaining part
    inline void flush () {
        fwrite (obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }
    // putchar
    inline void putc (char x) {
        *oS ++ = x;
        if (oS == oT) flush ();
    }
    template<typename A>
    inline bool read (A &x) {
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
        for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
        return 1;
    }
    inline bool read (char &x) {
        while((x=gc())==' '||x=='\n' || x=='\r');
        return x!=EOF;
    }
    inline bool read(char *x){
        while((*x=gc())=='\n' || *x==' '||*x=='\r');
        if(*x==EOF)return 0;
        while(!(*x=='\n'||*x==' '||*x=='\r'||*x==EOF))*(++x)=gc();
        *x=0;
        return 1;
    }
    template<typename A,typename ...B>
    inline bool read(A &x,B &...y){
        return read(x)&&read(y...);
    }
    template<typename A>
    inline bool write (A x) {
        if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
        while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
        while (qr) putc (qu[qr --]);
        return 0;
    }
    inline bool write (char x) {
        putc(x);
        return 0;
    }
    inline bool write(const char *x){
        while(*x){putc(*x);++x;}
        return 0;
    }
    inline bool write(char *x){
        while(*x){putc(*x);++x;}
        return 0;
    }
    template<typename A,typename ...B>
    inline bool write(A x,B ...y){
        return write(x)||write(y...);
    }
    //no need to call flush at the end manually!
    struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: write;

pii operator +(pii a,pii b){
    return {a.x+b.x,min(a.y+b.x,b.y)};
}
namespace run{
    int a[100005],b[100005];
    int id[100005];
    struct smt{
        int ls,rs;
        pii s;
        smt *l,*r;
        smt(){}
        smt(int,int);
        void query(int la,int ra,int &w){
            if(la<=ls && rs<=ra){
                w=min(w+s.x,s.y);
                return;
            }
            if(la<=l->rs)l->query(la,ra,w);
            if(r->ls<=ra)r->query(la,ra,w);
        }
    };
    smt *rt,node[200005],*at=node;
    smt *newsmt(int la,int ra){
        smt *rt=at;++at;
        *rt=smt(la,ra);
        return rt;
    }
    smt::smt(int la,int ra){
        ls=la;rs=ra;
        if(ls==rs){
            s={b[id[ls]],a[id[ls]]+b[id[ls]]};
            l=r=0;return;
        }
        int mid=(ls+rs)>>1;
        l=newsmt(ls,mid);r=newsmt(mid+1,rs);
        s=l->s+r->s;
    }
    int h[100005];
    bool main(){
        at=node;
        int n,k;
        read(n,k);
        for(int i=1;i<=n;++i){
            read(a[i],b[i]);
        }
        if(k>a[1]+b[1])return write("NO\n");
        if(k<=a[1])return write("YES\n");
        for(int i=2;i<=n;++i){
            id[i-1]=i;
        }
        sort(id+1,id+n,[](int u,int v){return a[u]+b[u]<a[v]+b[v];});
        if(n==1){
            return write("NO\n");
        }
        for(int i=1;i<n;++i)h[i]=a[id[i]]+b[id[i]];
        rt=newsmt(1,n-1);
        for(int i=1;i<n;++i){
            int w=a[id[i]];
            int u=lower_bound(h+1,h+n,w)-h;
            if(u<i)rt->query(u,i-1,w);
            if(i+1<n){
                if(u<=i)rt->query(i+1,n-1,w);
                else if(u<n)rt->query(u,n-1,w);
            }
            if(w>=k-b[1])return write("YES\n");
        }
        return write("NO\n");
    }
}
signed main(){
#ifdef QAQAutoMaton
    freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
#endif
    int t;
    read(t);
    for(;t;--t)run::main();
    return 0;
}