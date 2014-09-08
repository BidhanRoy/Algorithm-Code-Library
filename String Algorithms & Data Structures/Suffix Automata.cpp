class SuffixAutomata {

	#define charToInt(ch) (ch-'a')

	struct state {
		int len, link;
		int next[26];
		int firstPos;
		bool isClone;
		vector<int> backLink;
		
		bool has ( char ch ) {
			return next[ charToInt(ch) ] != -1;
		}
	};

	int sz, last;
	vector< state > Pool; 

	void getAllOccurrence ( int v , int P_length , vector<int> &ret ) {
		if ( !Pool[v].isClone ) ret.pb( Pool[v].firstPos - P_length + 1 );
		for ( size_t i = 0; i < Pool[v].backLink.size(); i++ )
			getAllOccurrence ( Pool[v].backLink[i] , P_length , ret);
	}

	public :

	SuffixAutomata( int maxlength ) {
		Pool = vector<state> ( maxlength * 2 );
	}

	void initialize() {
		rep( i , sz ) Pool[i].backLink.clr, Pool[i].isClone = false, Pool[i].link = -1, Pool[i].len = 0;
		sz = last = 0;
		Pool[0].len = 0;
		Pool[0].link = -1;
		mem( Pool[sz].next , -1 );
		++sz;
	}

	void addChar (char c) {
		int cur = sz++;
		mem( Pool[cur].next , -1 );
		Pool[cur].len = Pool[last].len + 1;
		Pool[cur].firstPos = Pool[cur].len - 1;
		Pool[cur].isClone = false;
		int p;
		for ( p = last; p != -1 && !Pool[p].has(c) ; p = Pool[p].link ) Pool[p].next[ charToInt(c) ] = cur;
		if ( p == -1 ) Pool[cur].link = 0;
		else {
			int q = Pool[p].next[ charToInt(c) ];
			if ( Pool[p].len + 1 == Pool[q].len ) Pool[cur].link = q;
			else {
				int clone = sz++;
				mem( Pool[clone].next , -1 );
				Pool[clone].len = Pool[p].len + 1;
				Pool[clone].firstPos = Pool[p].firstPos;
				Pool[clone].isClone = true;
				memcpy( Pool[clone].next , Pool[q].next , sizeof (Pool[q].next) );
				Pool[clone].link = Pool[q].link;
				for ( ; p != -1 && Pool[p].next[charToInt(c)] == q; p = Pool[p].link )
					Pool[p].next[ charToInt(c) ] = clone;
				Pool[q].link = Pool[cur].link = clone;
			}
		}
		last = cur;
	}

	void construct ( string &str ) {
		rep( i , sz(str) ) addChar(str[i]);
		for( int v=1; v<sz; v++ ) {
			if( Pool[v].link != -1 )
			Pool[ Pool[v].link ].backLink.pb( v );
		}
	}

	int findState ( string &pattern ) {
		int now = 0, length = 0;
		rep( i , sz( pattern ) ) {
			char ch = pattern[i];
			while( now && !Pool[now].has( ch ) ) {
				now = Pool[now].link;
				length = Pool[now].len;
			}
			if( Pool[now].has(ch) ){
				now = Pool[now].next[ch-'a'];
				length++;
			}
		}
		return ( length == sz(pattern) ? now : -1 );
	}

	vector<int> getAllOccurrence ( string &pattern ) {
		vector<int> ret;
		int v = findState( pattern );
		if( v == -1 ) return ret;
		getAllOccurrence( v , sz(pattern) , ret );
		sort ( all ( ret ) );
		return ret;
	}

	#undef charToInt
};
