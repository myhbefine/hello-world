//P4568
#include<stdio.h>
#include<iostream>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<list>
#include<queue>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
const int maxn = 10005;
const int maxm = 50005;
const int maxk = 11;

int t,n,m,s,k;
int cnt,head[maxk*maxn],net[4*maxk*maxm],dis[maxk*maxn];

struct edge{
    int v,d;
    bool operator <(const edge& t) const{return d>t.d;}
};
edge e[4*maxk*maxm];
priority_queue<edge> q;

void add_edge(int u,int v,int d){
    e[++cnt].v=v;
    e[cnt].d=d;
    net[cnt]=head[u];
    head[u]=cnt;
}


void dij(int u){
    for(int i=1;i<=n*(k+1);i++) dis[i]=1e9;
    dis[u]=0;
    q.push(edge{u,0});
    edge tm;
    while(!q.empty()){
        tm=q.top();
        q.pop();
        u=tm.v;
        if(dis[u]!=tm.d) continue;
        for(int i=head[u];i;i=net[i]){
            if(dis[e[i].v]>dis[u]+e[i].d){
                dis[e[i].v]=dis[u]+e[i].d;
                q.push(edge{e[i].v,dis[e[i].v]});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //cout<<"O\n";
    t=1;//cin>>t;
    while(t--){
        cin>>n>>m>>k>>s>>t;
        
        int a,b,c;
        s++;t++;
        for(int i=0;i<m;i++){
            cin>>a>>b>>c;
            a++;b++;
            add_edge(a,b,c);
            add_edge(b,a,c);
            for(int j=1;j<=k;j++){
                add_edge(a+j*n,b+j*n,c);
                add_edge(b+j*n,a+j*n,c);
                add_edge(a+j*n-n,b+j*n,0);
                add_edge(b+j*n-n,a+j*n,0);
            }
        }
        dij(s);
        int an=dis[t];
        for(int i=1;i<=k;i++){
            an=min(an,dis[t+i*n]);
        }
        cout<<an;
        t=0;
    }
    return 0;
}
