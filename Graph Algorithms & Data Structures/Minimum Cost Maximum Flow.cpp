namespace MCF {
    #define MAXN 1020 /// Nodes
    #define MAXM 50504 /// 2*Edges
    #define wint int /// Datatype
    #define cint int /// Datatype 
    const wint wEPS=0;
    const wint wINF=1001001001; /// Should be greater than maximum possible 'flow'
    const cint cEPS=0; /// Needed when flow can be floating
    const cint cINF=1001001001; /// Should be greater than maximum possible 'cost'
    int n,m,ptr[MAXN],next[MAXM],zu[MAXM];
    wint capa[MAXM],tof;
    cint cost[MAXM],toc,d[MAXN],pot[MAXN];
    int vis[MAXN],pree[MAXN];
    void init(int _n){
		/// initialization
        n=_n; m=0; memset(ptr,~0,n<<2);
    }
    void ae(int u,int v,wint w,cint c) {
		/// function to add edges
		/// edge from 'u' to 'v'
		/// 'w' is capacity of edge
		/// 'c' is cost of edge
        next[m]=ptr[u];ptr[u]=m;zu[m]=v;capa[m]=w;cost[m]=+c;++m;
        next[m]=ptr[v];ptr[v]=m;zu[m]=u;capa[m]=0;cost[m]=-c;++m;
    }

    ///total flow will not be greater than flo
    bool run(int src,int ink,wint flo= wINF){
		/// 'src' is the souce
		/// 'ink' is the sink
        wint f;
        cint c,cc;
        int i,u,v;
        memset(pot,0,n*sizeof(cint));

        for (bool cont=1;cont;){
            cont=0;
            for(u=0;u<n;++u) for(i=ptr[u];~i;i=next[i]) if(capa[i]>wEPS){
                if(pot[zu[i]]>pot[u]+cost[i]+cEPS){
                    pot[zu[i]]=pot[u]+cost[i]; cont=1;
                }
            }
        }

        for(toc=0,tof=0;tof+wEPS<flo;){
            typedef pair<cint,int>node;
            priority_queue<node,vector<node>,greater<node> > q;
            for(u=0;u<n;++u) {d[u]=cINF;vis[u]=0;}
            for(q.push(mp(d[src]=0,src));!q.empty();){
                c=q.top().first;u=q.top().second;q.pop();
                if(vis[u]++)continue;
                for(i=ptr[u];~i;i=next[i])if(capa[i]>wEPS){
                    cc=c+cost[i]+pot[u]-pot[v=zu[i]];
                    if(d[v]>cc){q.push(mp(d[v]=cc,v));pree[v]=i;}
                }
            }
            if(!vis[ink])return 0;
            f=flo-tof;
            for(v=ink;v!=src;v=zu[i^1]) {i=pree[v];f=min(f,capa[i]);}
            for(v=ink;v!=src;v=zu[i^1]) {i=pree[v];capa[i]-=f;capa[i^1]+=f;}
            tof+=f;
            toc+=f*(d[ink]-pot[src]+pot[ink]);
            for(u=0;u<n;++u)pot[u]+=d[u];
        }
        return 1;
    }
};
