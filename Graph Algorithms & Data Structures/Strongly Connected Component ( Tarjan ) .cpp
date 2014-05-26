/*
 * Author : Bidhan Roy
 * Required Headers : <vector>,<cstring>
 * Complexity : O(N)
 * If you find any bug report me : mail2bidhan@gmail.com
 */

#define mx 100000 ///Maximum possible number of nodes

vector<int> edge[mx];
int _low[mx], _dtime[mx], _dfstime, _stack[mx], _size, _comp[mx], _comps;
bool _instack[mx];

void tarjan(int u){
	_low[u]=_dtime[u]=++_dfstime;
	_stack[_size++]=u;
	_instack[u]=true;
	int i;
	for(i=0; i< int(edge[u].size()); i++){
		int v=edge[u][i];
		if(_dtime[v]==-1) tarjan(v), _low[u]=min(_low[u],_low[v]);
		else if(_instack[v]) _low[u]=min(_low[u],_dtime[v]);
	}

	if(_dtime[u]==_low[u]){
		_comps++;
		int v=-1;
		do{
			v=_stack[--_size];
			_instack[v]=false;
			_comp[v]=_comps;
		}while(u!=v);
	}
}

void scc(int n){
    _comps=_dfstime=_size=0;
    memset(_dtime,-1,(n+1)*sizeof(int));
    memset(_low,0,(n+1)*sizeof(int));
    memset(_stack,0,(n+1)*sizeof(int));
    memset(_comp,0,(n+1)*sizeof(int));
    memset(_instack,0,(n+1)*sizeof(int));
    int i;
    for(i=0; i<n; i++) if(_dtime[i]==-1)tarjan(i);
}
