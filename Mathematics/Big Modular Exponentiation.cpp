long long powmod(long long b,long long p,long long m=0 ){
	// b ^ p mod m
	// 2 parameter means no mod
    long long res = 1;
    for( long long i=(1LL<<62); i; i>>=1){
        res*=res; 
        if(m>0) res%= m;
        if(p&i) { 
			res*=b; 
			if(m>0) res%=m; 
		}
    }
    return res;
}
