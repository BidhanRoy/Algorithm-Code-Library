namespace matrix{
    #define size 105 ///Maximum size of the matrix
    #define wint int ///datatype to use (int,long long etc)
    wint mat[size][size],tmp[size][size],res[size][size];
    wint MOD;
    int n;
    void init(int _n,wint _MOD){ ///initialization, _n=size of the square matrix , _MOD=mod value
        n=_n;
        MOD=_MOD;
        memset(mat,0,sizeof (mat));
        memset(tmp,0,sizeof (tmp));
        memset(res,0,sizeof (res));
    }
    void mul(wint r[][size],wint a[][size],wint b[][size]) {
        int i,j,t;
        for(i=0; i<n; i++) for(j=0; j<n; j++) {
            long long val=0;
            for(t=0; t<n; t++) val+=1LL*a[i][t]*b[t][j];
            tmp[i][j]=val%MOD;
        }
        memcpy(r,tmp,n*size*sizeof(tmp[0][0]));
    }
    void mPow(wint r[][size],wint a[][size],wint p) {
        int i;
        if (p<0) return;
        memset(r,0,sizeof(r));
        for(i=0; i<n; i++) r[i][i]=1;
        while(p>0) {
            if(p&1) mul(r,r,a);
            mul(a,a,a); p>>=1;
        }
    }
    void pow(wint p){
        mPow(res,mat,p);
        memcpy(mat,res,n*size*sizeof(tmp[0][0]));
    }
    void print(wint pp[][size]){
        int i,j;
        for(i=0; i<n; i++){
            for(j=0; j<n; j++) printf(" %09d",pp[i][j]);
            printf("\n");
        }
    }
}
