namespace dinic{

    #define MAXN 100000 ///total nodes
    #define MAXE 400000 ///4*total edges
    #define INF 1000000000 ///1LL<<55 incase of i64
    #define wint i64 ///int or i64?

    struct edge {
        int a, b;
        int cap;
        wint flow;
    };

    int n, s, t, ptr[MAXN], q[MAXN];
    int d[MAXN],esize;
    edge e[MAXE];
    vector<int> g[MAXN];

    void init(int _n,int _s,int _t){
        n=_n, s=_s, t=_t;
        esize=0;
        //for(int i=0; i<n; i++) g[i].clear();
    }

    void add_edge(int a, int b, int cap) {
        edge e1 = { a, b, cap, 0 };
        edge e2 = { b, a, 0, 0 };
        g[a].push_back (esize);
        e[esize++]=e1;
        g[b].push_back (esize);
        e[esize++]=e2;
    }

    bool bfs() {
        int qh=0, qt=0;
        q[qt++] = s;
        memset (d, -1, n * sizeof d[0]);
        d[s] = 0;
        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            for (size_t i=0; i<g[v].size(); ++i) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    wint dfs (int v, wint flow) {
        if (!flow)  return 0;
        if (v == t)  return flow;
        for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1)  continue;
            wint pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    wint dinic() {
        wint flow = 0;
        while(true){
            if (!bfs())  break;
            memset (ptr, 0, n * sizeof ptr[0]);
            while (wint pushed = dfs (s, INF))
                flow += pushed;
        }
        return flow;
    }
}
