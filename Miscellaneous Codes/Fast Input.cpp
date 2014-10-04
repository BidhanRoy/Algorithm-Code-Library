namespace fastIO{

	#ifdef _WIN64
	    	#define getchar_unlocked() getchar()
	#elif _WIN32
	    	#define getchar_unlocked() getchar()
	#endif

	unsigned getCharArray(char *str){

		/// Takes the pointer of string as argument,
		/// returns the length of the string.

		char c;
		unsigned Len = 0;
		
		while(1) {
			c = getchar_unlocked();
			if( (c<'0' || c>'9') && (c<'a' || c>'z') && (c<'A' || c>'Z') ) continue;
			break;
		}

		str[ Len++ ] = c;
		
		while(1) {
			c = getchar_unlocked();
			if( (c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z') ) str[ Len++ ] = c;
	        else break;
		}

		str[ Len ] = '\0';

		return Len;
	}

	long long getLongLong(){

	    long long res = 0;
		char c;
		bool negative = false;
		
		while(1) {
			c = getchar_unlocked();
			if( (c<'0' || c>'9') && c!='-') continue;
			break;
		}

		if( c=='-' ) negative = true, c = getchar_unlocked();
		
		res = c-'0';
		
		while(1) {
			c = getchar_unlocked();
			if( c>='0' && c<='9' ) res = 10ll*res+c-'0';
	        else break;
		}

		return negative?-res:res;
	}
	 
	int getInt(){

	    int res = 0;
		char c;
		bool negative = false;
		
		while(1) {
			c = getchar_unlocked();
			if( (c<'0' || c>'9') && c!='-') continue;
			break;
		}

		if( c=='-' ) negative = true, c = getchar_unlocked();
		
		res = c-'0';
		
		while(1) {
			c = getchar_unlocked();
			if( c>='0' && c<='9' ) res = 10*res+c-'0';
	        else break;
		}

		return negative?-res:res;
	}

};
